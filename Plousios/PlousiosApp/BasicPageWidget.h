#pragma once

#include <QSplitter>

#include "DatabaseHelper.h"
#include "FilterHelper.h"
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
// ������ �������� ���������
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

    // �������� ������ �� ������� ������
    void UpdatePlot( const QVector<DatabaseProcessing::AssetPriceData> & );
    // �������� ������
    void ClearPlot();

    void SetActivePage( PageType );

signals:
    void UpdateBalance();

private slots:
    void OnClickAsset( unsigned id );
    void OnBuyAsset();
    void OnFilterChanged( const Filter & );

private:
    void InitPlot();    // �������� � ��������� �������

    AssetsWidget * _assetsWT;
    TradingWidget * _tradingWT;
    HistoryWidget * _historyWT;

    FilterWidget * _findWT;     // ������ ������
    QCustomPlot * _plotWT;      // ������ �������
};
