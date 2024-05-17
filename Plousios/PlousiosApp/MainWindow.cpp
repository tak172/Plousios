#include "stdafx.h"
#include "MainWindow.h"
#include "MainWindowDefines.h"
#include <QToolBar>
#include <Qlabel>
#include <QPushButton>
#include <QToolButton>

// -------------------------------------------
#include "TradingPageWidget.h"
// -------------------------------------------

/*
    Plousios source code. Tak172. 2024.

    @Name:			MainWindow.cpp
    @Created:		14.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MakeAuxBar();
    MakeNavigationBar();
    TradingPageWidget * _trading_pageWT = new TradingPageWidget( this );
    setCentralWidget( _trading_pageWT );
}

MainWindow::~MainWindow()
{}

void MainWindow::OnClickUser()
{
}

void MainWindow::OnClickPortfolio()
{
}

void MainWindow::OnClickHistory()
{
}

void MainWindow::OnClickTrading()
{
}

void MainWindow::OnClickExit()
{
    this->close();
}

void MainWindow::MakeAuxBar()
{
    QToolBar * auxTB = new QToolBar;
    auxTB->setStyleSheet(
        "QToolBar {"
            "border: 1px solid #d3dae3;"
            "border-right: none;"
            "border-left: none;"
            "border-top: none;"
        "}"
        "QToolBar::separator {"
            "background-color: #d3dae3;"
            "width: 1px;"
            "margin: 0px;"
        "}"
        "QToolBar QToolButton {"
            "min-height: 60px;"
            "min-width: 60px;"
            "max-height: 60px;"
            "spacing: 50px;"
            "margin-left: 3px;"
        "}"
    );
    auxTB->setOrientation( Qt::Horizontal );
    auxTB->setMovable( false );
    auxTB->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );

    QLabel * iconTL = new QLabel( this );
    QPixmap pixmap( ":/Plousios/logo" );
    iconTL->setPixmap( pixmap );
    iconTL->setScaledContents( true );
    iconTL->setStyleSheet(
        "margin-top: 10px;"
        "margin-bottom: 10px;"
        "margin-left: 20px;"
        "margin-right: 20px;"
        "min-width: 40px;"
        "max-width: 40px;"
        "min-height: 40px;"
        "max-height: 40px;"
    );
    auxTB->addWidget( iconTL );
    auxTB->addSeparator();
    QWidget * spacer1WT = new QWidget( this );
    spacer1WT->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    auxTB->addWidget( spacer1WT );

    QLabel * balanceTL = new QLabel( "BALANCE:\n$0.00", this);
    balanceTL->setAlignment( Qt::AlignCenter );
    balanceTL->setStyleSheet(
        "margin-left: 30px;"
        "margin-right: 30px;"
    );
    auxTB->addWidget( balanceTL );

    QAction * userAN = new QAction( QIcon( ":/Plousios/user_l" ),
        QString::fromStdWString( L"Профиль" ), this );
    auxTB->addAction( userAN );

    connect( userAN, &QAction::triggered, this, &MainWindow::OnClickUser );
    addToolBar( Qt::TopToolBarArea, auxTB );
}

void MainWindow::MakeNavigationBar()
{
    QToolBar * navigationTB = new QToolBar;
    navigationTB->setStyleSheet(
        "QToolBar {"
        "border: 1px solid #d3dae3;"
        "border-bottom: none;"
        "border-left: none;"
        "border-top: none;"
        "}"
        "QToolBar QToolButton {"
            "margin-left: 2px;"
            "margin-right: 2px;"
            "margin-top: 1px;"
            "margin-bottom: 1px;"
            "min-width: 70px;"
            "max-width: 70px;"
            "min-height: 70px;"
            "max-height: 70px;"
        "}"
        "QToolBar QWidget {"
            "margin-bottom: 3px;"
        "}"
    );
    navigationTB->setOrientation( Qt::Vertical );
    navigationTB->setMovable( false );
    navigationTB->setIconSize( QSize( 40, 40 ) );
    navigationTB->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

    QAction * tradingAN = new QAction( QIcon( ":/Plousios/trading_l" ),
        QString::fromStdWString( L"Трейдинг" ), this );
    QAction * historyAN = new QAction( QIcon( ":/Plousios/history_l" ),
        QString::fromStdWString( L"История" ), this );
    QAction * portfolioAN = new QAction( QIcon( ":/Plousios/portfolio_l" ),
        QString::fromStdWString( L"Активы" ), this );
    QAction * exitAN = new QAction( QIcon( ":/Plousios/exit_l" ),
        QString::fromStdWString( L"Выход" ), this );

    connect( tradingAN, &QAction::triggered, this, &MainWindow::OnClickTrading );
    connect( historyAN, &QAction::triggered, this, &MainWindow::OnClickHistory );
    connect( portfolioAN, &QAction::triggered, this, &MainWindow::OnClickPortfolio );
    connect( exitAN, &QAction::triggered, this, &MainWindow::OnClickExit );

    navigationTB->addAction( tradingAN );
    navigationTB->addAction( historyAN );
    navigationTB->addAction( portfolioAN );
    QWidget * spacerWT = new QWidget( this );
    spacerWT->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    navigationTB->addWidget( spacerWT );
    navigationTB->addAction( exitAN );
    addToolBar( Qt::LeftToolBarArea, navigationTB );
}
