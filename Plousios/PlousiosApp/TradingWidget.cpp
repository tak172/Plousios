#include "stdafx.h"
#include "TradingWidget.h"
#include "DatabaseManager.h"

#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

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
        connect( buy_button, &QPushButton::clicked, [ id = asset._id, this ]()
        {
            for ( int row_idx = 0; row_idx < columnCount(); ++row_idx )
            {
                QTableWidgetItem * nameTI = item( row_idx, 0 );
                if ( nameTI->data( Qt::UserRole ).toUInt() == id )
                {
                    QTableWidgetItem * price_item = item( row_idx, 2 );
                    BuyAsset( id, price_item->text().toDouble() );
                    break;
                }
            }
        } );

        setCellWidget( rowCount() - 1, 3, buy_button );
    }
}

void TradingWidget::FilterAssets( const Filter & filter )
{
    DatabaseProcessing::DatabaseManager * db_manager = DatabaseProcessing::DatabaseManager::Instance();
    QString country_name = db_manager->GetCountryName( filter._country );
    for ( int row_idx = 0; row_idx < rowCount(); ++row_idx )
    {
        bool is_visiable = item( row_idx, 0 )->text().contains( filter._pattern );
        is_visiable = ( is_visiable && item( row_idx, 1 )->text().contains( country_name ) );
        setRowHidden( row_idx, !is_visiable );
    }
}

void TradingWidget::BuyAsset( unsigned asset_id, double price )
{
    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    if ( db_manager->BuyAsset( asset_id, _user_id, price ) == true )
    {
        UpdateAssets();
        emit UpdateBalance();
        return;
    }

    QMessageBox message_box;
    message_box.setWindowTitle( WToQ( L"Ошибка стоимости" ) );
    message_box.setText( WToQ( L"Ошибка проведения транзакции. Цена актива изменилась." ) );
    message_box.setIcon( QMessageBox::Warning );
    message_box.setStandardButtons( QMessageBox::Ok );
    if ( QAbstractButton * ok_button = message_box.button( QMessageBox::Ok ) )
        ok_button->setMinimumWidth( 100 );

    message_box.exec();
    UpdateAssets();
}
