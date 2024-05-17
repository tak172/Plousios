#include "stdafx.h"
#include "TradingPageWidget.h"
#include <qlayout.h>

/*
    Plousios source code. Tak172. 2024.

    @Name:			TradingPageWidget.cpp
    @Created:		15.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

TradingPageWidget::TradingPageWidget( QWidget * parent )
    : QSplitter( Qt::Vertical, parent )
{
    _plotWT = new QCustomPlot( this );
    InitPlot();

    _tradingTW = new QTableWidget( this );
    _findWT = new TradingFindWidget( this );
    InitTop();

    QHBoxLayout * topHL = new QHBoxLayout( this );
    topHL->addWidget( _findWT );
    topHL->addWidget( _tradingTW );
    QWidget * topWT = new QWidget( this );
    topWT->setLayout( topHL );

    addWidget( topWT );
    addWidget( _plotWT );
}

TradingPageWidget::~TradingPageWidget()
{}

void TradingPageWidget::UpdatePlot( const QVector<PlotPoint> & plot_points )
{
    _plotWT->clearGraphs();
    if ( plot_points.isEmpty() )
        return;

    double start_price = plot_points.first()._price;
    double start_date_time = plot_points.first()._date_time.toSecsSinceEpoch() / 60;

    QVector<double> price_points;
    QVector<double> date_time_points;
    for ( const PlotPoint & point : plot_points )
    {
        price_points.append( point._price - start_price );
        date_time_points.append( ( point._date_time.toSecsSinceEpoch() / 60 ) - start_date_time );
    }

    for ( int i = 1; i < plot_points.size(); ++i )
    {
        QCPGraph * graph = _plotWT->addGraph();
        graph->addData( date_time_points[ i - 1 ], price_points[ i - 1 ] );
        graph->addData( date_time_points[ i ], price_points[ i ] );
        graph->setPen( QPen( QColor( ( price_points[ i - 1 ] > price_points[ i ] ?
            QColor( 180, 90, 90 ) : QColor( 100, 180, 110 ) ) ), 2 ) );
        graph->setScatterStyle( QCPScatterStyle( QCPScatterStyle::ssCircle,
            QPen( Qt::black, 1.5 ), QBrush( QColor( "#d3dae3" ) ), 9 ) );
    }

    QCPAxisRect * volume_axis_rect = qobject_cast<QCPAxisRect *>( _plotWT->plotLayout()->element( 1, 0 ) );
    QCPBars * volume_pos = new QCPBars( volume_axis_rect->axis( QCPAxis::atBottom ), volume_axis_rect->axis( QCPAxis::atLeft ) );
    QCPBars * volume_neg = new QCPBars( volume_axis_rect->axis( QCPAxis::atBottom ), volume_axis_rect->axis( QCPAxis::atLeft ) );
    for ( int i = 1; i < plot_points.size(); ++i )
        ( price_points[ i - 1 ] > price_points[ i ] ? volume_neg : volume_pos )->addData(
            date_time_points[ i ], qAbs( price_points[ i ] ) );

    volume_pos->setWidth( ( date_time_points.back() - date_time_points.first() ) / ( plot_points.size() * 1.5 ) );
    volume_pos->setPen( Qt::NoPen );
    volume_pos->setBrush( QColor( 100, 180, 110 ) );

    volume_neg->setWidth( ( date_time_points.back() - date_time_points.first() ) / ( plot_points.size() * 1.5 ) );
    volume_neg->setPen( Qt::NoPen );
    volume_neg->setBrush( QColor( 180, 90, 90 ) );

    _plotWT->rescaleAxes();
}

void TradingPageWidget::ClearPlot()
{
    _plotWT->clearGraphs();
    _plotWT->clearPlottables();
    _plotWT->replot();
}

void TradingPageWidget::InitTop()
{
    _tradingTW->setColumnCount( 5 );
    QStringList horizontal_headers;
    horizontal_headers << WToQ( L"Название" ) << WToQ( L"Изменение" )
        << WToQ( L"Цена" ) << WToQ( L"Цена покупки" ) << WToQ( L"Купить" );
    _tradingTW->setHorizontalHeaderLabels( horizontal_headers );

    _tradingTW->setColumnWidth( 1, 300 );
    for ( int i = 2; i < _tradingTW->columnCount(); ++i )
        _tradingTW->setColumnWidth( i, 200 );

    _tradingTW->setEditTriggers( QAbstractItemView::NoEditTriggers );
    _tradingTW->horizontalHeader()->setSectionResizeMode( QHeaderView::Fixed );
    _tradingTW->horizontalHeader()->setSectionResizeMode( 0, QHeaderView::Stretch );

    _findWT->setMinimumSize( 300, 300 );
}

void TradingPageWidget::InitPlot()
{
    _plotWT->setMinimumSize( 900, 300 );
    _plotWT->xAxis->setBasePen( QPen( QColor( "#d3dae3" ), 1 ) );
    _plotWT->yAxis->setBasePen( QPen( QColor( "#d3dae3" ), 1 ) );
    _plotWT->xAxis->setTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    _plotWT->yAxis->setTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    _plotWT->xAxis->setSubTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    _plotWT->yAxis->setSubTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    _plotWT->xAxis->setTickLabelColor( QColor( "#d3dae3" ) );
    _plotWT->yAxis->setTickLabelColor( QColor( "#d3dae3" ) );

    _plotWT->xAxis->grid()->setZeroLinePen( Qt::NoPen );
    _plotWT->yAxis->grid()->setZeroLinePen( Qt::NoPen );
    _plotWT->xAxis->setUpperEnding( QCPLineEnding::esSpikeArrow );
    _plotWT->yAxis->setUpperEnding( QCPLineEnding::esNone );
    _plotWT->yAxis->setTicks( false );

    QLinearGradient plot_gradient;
    plot_gradient.setStart( 0, 0 );
    plot_gradient.setFinalStop( 0, 350 );
    plot_gradient.setColorAt( 0, QColor( "#100E19" ) );
    plot_gradient.setColorAt( 1, QColor( "#211D33" ) );
    _plotWT->setBackground( plot_gradient );

    QLinearGradient axis_rect_gradient;
    axis_rect_gradient.setStart( 0, 0 );
    axis_rect_gradient.setFinalStop( 0, 350 );
    axis_rect_gradient.setColorAt( 0, QColor( "#100E19" ) );
    axis_rect_gradient.setColorAt( 1, QColor( "#423966" ) );
    _plotWT->axisRect()->setBackground( axis_rect_gradient );

    _plotWT->xAxis->setTickLabels( false );
    _plotWT->yAxis->setTickLabels( false );
    _plotWT->xAxis->grid()->setVisible( false );
    _plotWT->rescaleAxes();

    QCPAxisRect * volume_axis_rect = new QCPAxisRect( _plotWT );
    _plotWT->plotLayout()->addElement( 1, 0, volume_axis_rect );
    _plotWT->plotLayout()->setRowSpacing( 10 );
    volume_axis_rect->setAutoMargins( QCP::msLeft | QCP::msRight | QCP::msBottom );
    volume_axis_rect->setMargins( QMargins( 0, 0, 0, 0 ) );
    volume_axis_rect->axis( QCPAxis::atBottom )->setTickLabels( false );
    volume_axis_rect->axis( QCPAxis::atLeft )->setTickLabels( false );
    volume_axis_rect->axis( QCPAxis::atBottom )->grid()->setVisible( false );

    volume_axis_rect->axis( QCPAxis::atLeft )->setBasePen( QPen( QColor( "#d3dae3" ), 1 ) );
    volume_axis_rect->axis( QCPAxis::atBottom )->setBasePen( QPen( QColor( "#d3dae3" ), 1 ) );
    volume_axis_rect->axis( QCPAxis::atLeft )->setTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    volume_axis_rect->axis( QCPAxis::atBottom )->setTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    volume_axis_rect->axis( QCPAxis::atLeft )->setSubTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    volume_axis_rect->axis( QCPAxis::atBottom )->setSubTickPen( QPen( QColor( "#d3dae3" ), 1 ) );
    volume_axis_rect->axis( QCPAxis::atLeft )->setTickLabelColor( QColor( "#d3dae3" ) );
    volume_axis_rect->axis( QCPAxis::atBottom )->setTickLabelColor( QColor( "#d3dae3" ) );

    volume_axis_rect->axis( QCPAxis::atLeft )->grid()->setZeroLinePen( Qt::NoPen );
    volume_axis_rect->axis( QCPAxis::atBottom )->grid()->setZeroLinePen( Qt::NoPen );
    volume_axis_rect->axis( QCPAxis::atLeft )->setUpperEnding( QCPLineEnding::esNone );
    volume_axis_rect->axis( QCPAxis::atLeft )->setTicks( false );
}