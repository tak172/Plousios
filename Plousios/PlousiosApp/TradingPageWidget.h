#pragma once

#include <QWidget>
#include <QTableWidget>
#include <chrono>
#include "qcustomplot.h"
#include "TradingFindWidget.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			TradingPageWidget.h
    @Created:		15.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

// виджет страницы трейдинга
class TradingPageWidget : public QSplitter
{
    Q_OBJECT

public:
    // точка графика( цена : время )
    struct PlotPoint
    {
        double _price;
        QDateTime _date_time;
    };

    TradingPageWidget( QWidget * = nullptr );
    ~TradingPageWidget();

    // обновить график по заданым точкам
    void UpdatePlot( const QVector<PlotPoint> & );
    // очистить график
    void ClearPlot();

private:
    void InitTop();     // создание и настройка верхней части
    void InitPlot();    // создание и настройка графика

    QTableWidget * _tradingTW;      // таблица с акциями для покупки
    TradingFindWidget * _findWT;    // виджет поиска
    QCustomPlot * _plotWT;          // виджет графика
};
