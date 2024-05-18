#pragma once

#include <QSplitter>
#include "DatabaseHelper.h"
/*
    Plousios source code. Tak172. 2024.

    @Name:			BasicPageWidget.h
    @Created:		15.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

class QCustomPlot;
class FilterWidget;
class AssetsWidget;
class TradingWidget;
class HistoryWidget;
// виджет страницы трейдинга
class BasicPageWidget : public QSplitter
{
    Q_OBJECT

public:
    enum class PageType
    {
        Assets,
        Trading,
        History
    };

    BasicPageWidget( unsigned user_id, QWidget * = nullptr );
    ~BasicPageWidget();

    void UpdatePages();

    // обновить график по заданым точкам
    void UpdatePlot( const QVector<DatabaseProcessing::AssetPriceData> & );
    // очистить график
    void ClearPlot();

    void SetActivePage( PageType );

signals:
    void BuyAsset( unsigned id );

private slots:
    void OnClickAsset( unsigned id );
    void OnBuyAsset( unsigned id );

private:
    void InitPlot();    // создание и настройка графика

    AssetsWidget * _assetsWT;
    TradingWidget * _tradingWT;
    HistoryWidget * _historyWT;

    FilterWidget * _findWT;     // виджет поиска
    QCustomPlot * _plotWT;      // виджет графика
};
