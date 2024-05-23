#pragma once
#include <QTableWidget>

#include "FilterHelper.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			AssetsWidget.h
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

class AssetsWidget : public QTableWidget
{
    Q_OBJECT

public:
    AssetsWidget( unsigned user_id, QWidget * = nullptr );
    ~AssetsWidget();

    void UpdateAssets();
    void FilterAssets( const Filter & );

signals:
    void ClickAsset( unsigned );

private slots:
    void OnClickAsset( int );
    void OnClickPutForSale( unsigned, double );

private:
    unsigned _user_id;
};