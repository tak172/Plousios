#include "stdafx.h"
#include "TradingWidget.h"
#include "DatabaseManager.h"

#include <QHeaderView>
#include <QPushButton>

/*
    Plousios source code. Tak172. 2024.

    @Name:			TradingWidget.cpp
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

TradingWidget::TradingWidget( unsigned user_id, QWidget * parent )
    : _user_id( user_id ), QTableWidget( parent )
{ 
    setColumnCount( 4 );
    QStringList horizontal_headers;
    horizontal_headers << WToQ( L"Название" ) << WToQ( L"Страна" ) << WToQ( L"Цена" ) << WToQ( L"Купить" );
    setHorizontalHeaderLabels( horizontal_headers );
    
    setColumnWidth( 1, 300 );
    for ( int i = 2; i < columnCount(); ++i )
        setColumnWidth( i, 200 );
    
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    verticalHeader()->hide();
    UpdateAssets();

    connect( this, &QTableWidget::cellClicked, this, &TradingWidget::OnClickAsset );
}

TradingWidget::~TradingWidget()
{ }

void TradingWidget::OnClickBuy( unsigned id )
{
    emit ClickBuy( id );
}

void TradingWidget::OnClickAsset( int row )
{
    if ( QTableWidgetItem * table_item = item( row, 0 ) )
        emit ClickAsset( table_item->data( Qt::UserRole ).toUInt() );
}

void TradingWidget::UpdateAssets()
{
    clearContents();
    setRowCount( 0 );

    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    auto assets = db_manager->GetAssetsList();
    for ( auto & asset : assets )
    {
        QString country_name = db_manager->GetCountryName( 
            static_cast<DatabaseProcessing::Countries>( asset._country_id ) );
        insertRow( rowCount() );
        auto nameTI = new QTableWidgetItem( asset._name );
        nameTI->setData( Qt::UserRole, asset._id );
        setItem( rowCount() - 1, 0, nameTI );
        setItem( rowCount() - 1, 1, new QTableWidgetItem( country_name ) );
        setItem( rowCount() - 1, 2, new QTableWidgetItem( QString::number( asset._price, 'f', 2 ) ) );

        if ( asset._owner_id == _user_id )
            continue;

        QPushButton * buy_button = new QPushButton;
        buy_button->setText( WToQ( L"Приобрести" ) );
        connect( buy_button, &QPushButton::clicked, [ id = asset._id, this ] ()
        {
            emit OnClickBuy( id );
        } );

        setCellWidget( rowCount() - 1, 3, buy_button );
    }
}
