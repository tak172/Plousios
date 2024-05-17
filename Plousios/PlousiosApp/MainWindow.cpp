#include "stdafx.h"
#include "MainWindow.h"
#include "MainWindowDefines.h"
#include <QToolBar>
#include <Qlabel>
#include <QPushButton>
#include <QToolButton>

// -------------------------------------------
#include "TradingPageWidget.h"
#include <QtSql> 
#include <QtCore>
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
    

    QSqlDatabase db = QSqlDatabase::addDatabase( "QPSQL" );
    db.setHostName( "localhost" );      // Хост PostgreSQL
    db.setDatabaseName( "plousios" );   // Имя вашей базы данных
    db.setUserName( "Timofey" );        // Имя пользователя PostgreSQL
    db.setPassword( "Maksem2005" );     // Пароль PostgreSQL
    bool ok = db.open();


}

MainWindow::~MainWindow()
{}

void MainWindow::OnClickUser()
{
}

void MainWindow::OnClickNotification()
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

void MainWindow::OnClickSettings()
{
}

void MainWindow::OnClickExit()
{
    this->close();
}

void MainWindow::OnChangeCurrency( Currency cur )
{
    QPushButton * usdBN = this->findChild<QPushButton *>( USD_NAME );
    QPushButton * btcBN = this->findChild<QPushButton *>( BTC_NAME );
    QPushButton * rubBN = this->findChild<QPushButton *>( RUB_NAME );
    Q_ASSERT( usdBN && btcBN && rubBN );

    usdBN->setStyleSheet( "background-color: #100E19" );
    btcBN->setStyleSheet( "background-color: #100E19" );
    rubBN->setStyleSheet( "background-color: #100E19" );

    switch ( cur )
    {
        case Currency::USD:
        usdBN->setStyleSheet( "background-color: #7d7d7d" );
        break;
        case Currency::BTC:
        btcBN->setStyleSheet( "background-color: #7d7d7d" );
        break;
        case Currency::RUB:
        rubBN->setStyleSheet( "background-color: #7d7d7d" );
        break;
    }
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

    QPushButton * usdBN = new QPushButton( "USD", this );
    usdBN->setObjectName( USD_NAME );
    usdBN->setFixedWidth( 80 );
    QPushButton * btcBN = new QPushButton( "BTC", this );
    btcBN->setObjectName( BTC_NAME );
    btcBN->setFixedWidth( 80 );
    QPushButton * rubBN = new QPushButton( "RUB", this );
    rubBN->setObjectName( RUB_NAME );
    rubBN->setFixedWidth( 80 );

    connect( usdBN, &QPushButton::clicked, this, [ this ] ()
    {
        OnChangeCurrency( Currency::USD );
    } );

    connect( btcBN, &QPushButton::clicked, this, [ this ] ()
    {
        OnChangeCurrency( Currency::BTC );
    } );

    connect( rubBN, &QPushButton::clicked, this, [ this ] ()
    {
        OnChangeCurrency( Currency::RUB );
    } );

    auxTB->addWidget( usdBN );
    auxTB->addWidget( btcBN );
    auxTB->addWidget( rubBN );

    QWidget * spacer2WT = new QWidget( this );
    spacer2WT->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    auxTB->addWidget( spacer2WT );

    QLabel * balanceTL = new QLabel( "BALANCE:\n$0.00", this);
    balanceTL->setAlignment( Qt::AlignCenter );
    balanceTL->setStyleSheet(
        "margin-left: 30px;"
        "margin-right: 30px;"
    );
    auxTB->addWidget( balanceTL );

    QToolButton * notificationTB = new QToolButton( this );
    notificationTB->setIcon( QIcon( ":/Plousios/notification_l" ) );
    notificationTB->setFixedSize( 60, 60 );
    auxTB->addWidget( notificationTB );

    QAction * userAN = new QAction( QIcon( ":/Plousios/user_l" ),
        QString::fromStdWString( L"Профиль" ), this );
    auxTB->addAction( userAN );

    connect( userAN, &QAction::triggered, this, &MainWindow::OnClickUser );
    connect( notificationTB, &QToolButton::clicked, this, &MainWindow::OnClickNotification );
    
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
    QAction * settingsAN = new QAction( QIcon( ":/Plousios/settings_l" ),
        QString::fromStdWString( L"Настройки" ), this );
    QAction * exitAN = new QAction( QIcon( ":/Plousios/exit_l" ),
        QString::fromStdWString( L"Выход" ), this );

    connect( tradingAN, &QAction::triggered, this, &MainWindow::OnClickTrading );
    connect( historyAN, &QAction::triggered, this, &MainWindow::OnClickHistory );
    connect( portfolioAN, &QAction::triggered, this, &MainWindow::OnClickPortfolio );
    connect( settingsAN, &QAction::triggered, this, &MainWindow::OnClickSettings );
    connect( exitAN, &QAction::triggered, this, &MainWindow::OnClickExit );

    navigationTB->addAction( tradingAN );
    navigationTB->addAction( historyAN );
    navigationTB->addAction( portfolioAN );
    QWidget * spacerWT = new QWidget( this );
    spacerWT->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    navigationTB->addWidget( spacerWT );
    navigationTB->addAction( settingsAN );
    navigationTB->addAction( exitAN );
    addToolBar( Qt::LeftToolBarArea, navigationTB );
}
