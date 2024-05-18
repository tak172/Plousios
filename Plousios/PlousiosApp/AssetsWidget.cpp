#include "stdafx.h"
#include "AssetsWidget.h"
#include "DatabaseManager.h"

#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

/*
    Plousios source code. Tak172. 2024.

    @Name:			AssetsWidget.cpp
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

AssetsWidget::AssetsWidget( unsigned user_id, QWidget * parent )
    : _user_id( user_id ), QTableWidget( parent )
{
    setColumnCount( 4 );
    QStringList horizontal_headers;
    horizontal_headers << WToQ( L"Название" ) << WToQ( L"Страна" ) << WToQ( L"Цена" ) << WToQ( L"Выставить" );
    setHorizontalHeaderLabels( horizontal_headers );

    setColumnWidth( 1, 300 );
    for ( int i = 2; i < columnCount(); ++i )
        setColumnWidth( i, 200 );

    setEditTriggers( QAbstractItemView::NoEditTriggers );
    horizontalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );
    verticalHeader()->hide();
    UpdateAssets();

    connect( this, &QTableWidget::cellClicked, this, &AssetsWidget::OnClickAsset );
}

AssetsWidget::~AssetsWidget()
{ }

void AssetsWidget::UpdateAssets()
{
    clearContents();
    setRowCount( 0 );

    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    auto assets = db_manager->GetUserAssets( _user_id );
    for ( auto & asset : assets )
    {
        QString country_name = db_manager->GetCountryName(
            static_cast< DatabaseProcessing::Countries >( asset._country_id ) );
        insertRow( rowCount() );
        auto nameTI = new QTableWidgetItem( asset._name );
        nameTI->setData( Qt::UserRole, asset._id );
        setItem( rowCount() - 1, 0, nameTI );
        setItem( rowCount() - 1, 1, new QTableWidgetItem( country_name ) );
        setItem( rowCount() - 1, 2, new QTableWidgetItem( QString::number( asset._price, 'f', 2 ) ) );

        if ( asset._is_for_sale == true )
            continue;

        QPushButton * put_for_sale = new QPushButton;
        put_for_sale->setText( WToQ( L"Выставить" ) );
        connect( put_for_sale, &QPushButton::clicked, [ id = asset._id, this ]()
        {
            OnClickPutForSale( id );
        } );

        setCellWidget( rowCount() - 1, 3, put_for_sale );
    }
}

void AssetsWidget::OnClickAsset( int row )
{
    if ( QTableWidgetItem * table_item = item( row, 0 ) )
        emit ClickAsset( table_item->data( Qt::UserRole ).toUInt() );
}

void AssetsWidget::OnClickPutForSale( unsigned id )
{
    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    if ( db_manager->PutForSale( id ) == true )
    {
        UpdateAssets();
        return;
    }

    QMessageBox message_box;
    message_box.setWindowTitle( WToQ( L"Ошибка подключения." ) );
    message_box.setText( WToQ( L"Ошибка проведения транзакции. Проверьте подключение." ) );
    message_box.setIcon( QMessageBox::Warning );
    message_box.setStandardButtons( QMessageBox::Ok );
    if ( QAbstractButton * ok_button = message_box.button( QMessageBox::Ok ) )
        ok_button->setMinimumWidth( 100 );

    message_box.exec();
}