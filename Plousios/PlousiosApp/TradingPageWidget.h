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

// ������ �������� ���������
class TradingPageWidget : public QSplitter
{
    Q_OBJECT

public:
    // ����� �������( ���� : ����� )
    struct PlotPoint
    {
        double _price;
        QDateTime _date_time;
    };

    TradingPageWidget( QWidget * = nullptr );
    ~TradingPageWidget();

    // �������� ������ �� ������� ������
    void UpdatePlot( const QVector<PlotPoint> & );
    // �������� ������
    void ClearPlot();

private:
    void InitTop();     // �������� � ��������� ������� �����
    void InitPlot();    // �������� � ��������� �������

    QTableWidget * _tradingTW;      // ������� � ������� ��� �������
    TradingFindWidget * _findWT;    // ������ ������
    QCustomPlot * _plotWT;          // ������ �������
};
