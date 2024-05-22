#pragma once
#include <QTableWidget>

#include "FilterHelper.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			TradingWidget.h
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

class TradingWidget : public QTableWidget
{
    Q_OBJECT

public:
    TradingWidget( unsigned user_id, QWidget * = nullptr );
    ~TradingWidget();

    void UpdateAssets();
    void FilterAssets( const Filter & );

signals:
    void ClickAsset( unsigned );
    void UpdateBalance();

private slots:
    void OnClickAsset( int );

private:
    void BuyAsset( unsigned, double );

    unsigned _user_id;
};