#pragma once
#include <QTableWidget>

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

signals:
    void ClickBuy( unsigned );
    void ClickAsset( unsigned );

private slots:
    void OnClickBuy( unsigned );
    void OnClickAsset( int );

private:
    unsigned _user_id;
};