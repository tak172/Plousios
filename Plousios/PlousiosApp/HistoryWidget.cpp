#include "stdafx.h"
#include "HistoryWidget.h"
#include "DatabaseManager.h"

#include <QHeaderView>
#include <QColor>
/*
    Plousios source code. Tak172. 2024.

    @Name:			HistoryWidget.cpp
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

HistoryWidget::HistoryWidget( unsigned user_id, QWidget * parent )
    : _user_id( user_id ), QTableWidget( parent )
{ 
    setColumnCount( 6 );
    QStringList horizontal_headers;
    horizontal_headers << WToQ( L"Название" ) << WToQ( L"Страна" ) << WToQ( L"Цена" )
        << WToQ( L"Цена покупки" ) << WToQ( L"Партнер" ) << WToQ( L"Тип сделки" );
    setHorizontalHeaderLabels( horizontal_headers );

    setColumnWidth( 1, 300 );
    for ( int i = 2; i < columnCount(); ++i )
        setColumnWidth( i, 150 );

    setEditTriggers( QAbstractItemView::NoEditTriggers );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    verticalHeader()->hide();
    UpdateHistory();

    connect( this, &QTableWidget::cellClicked, this, &HistoryWidget::OnClickAsset );
}

HistoryWidget::~HistoryWidget()
{ }

void HistoryWidget::UpdateHistory()
{
    clearContents();
    setRowCount( 0 );

    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    auto trades = db_manager->GetUserTradesHistory( _user_id );
    for ( const auto & trade : trades )
    {
        DatabaseProcessing::AssetData asset_data;
        asset_data._id = trade._asset_id;
        if ( !db_manager->GetAsset( asset_data ) )
            continue;

        QString country_name = db_manager->GetCountryName(
            static_cast<DatabaseProcessing::Countries>( asset_data._country_id ) );

        unsigned partner_id = trade._buyer_id == _user_id ? trade._seller_id : trade._buyer_id;
        DatabaseProcessing::UserData * partner_data = db_manager->GetUserData( partner_id );
        if ( partner_data == nullptr )
            continue;

        insertRow( rowCount() );
        auto nameTI = new QTableWidgetItem( asset_data._name );
        nameTI->setData( Qt::UserRole, asset_data._id );
        setItem( rowCount() - 1, 0, nameTI );
        setItem( rowCount() - 1, 1, new QTableWidgetItem( country_name ) );
        setItem( rowCount() - 1, 2, new QTableWidgetItem( QString::number( asset_data._price, 'f', 2 ) ) );
        setItem( rowCount() - 1, 3, new QTableWidgetItem( QString::number( trade._price, 'f', 2 ) ) );
        setItem( rowCount() - 1, 4, new QTableWidgetItem( partner_data->_nickname ) );
        setItem( rowCount() - 1, 5, new QTableWidgetItem(
            trade._buyer_id == _user_id ? WToQ( L"Покупка" ) : WToQ( L"Продажа" ) ) );
    }
}

void HistoryWidget::OnClickAsset( int row )
{
    if ( QTableWidgetItem * table_item = item( row, 0 ) )
        emit ClickAsset( table_item->data( Qt::UserRole ).toUInt() );
}