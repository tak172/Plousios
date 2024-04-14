#include "stdafx.h"
#include "MainWindow.h"
#include <QToolBar>
#include <Qlabel>
#include <QPushButton>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    MakeAuxBar();
    MakeNavigationBar();
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
}

void MainWindow::MakeAuxBar()
{
    QToolBar * auxTB = new QToolBar;
    auxTB->setStyleSheet(
        "QToolBar QToolButton {"
            "min-height: 60px;"
            "max-height: 60px;"
            "font: 75 8pt \"Comic Sans MS\";"
        "}"
        "QToolBar QLabel {"
            "font: 75 8pt \"Comic Sans MS\";"
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
        "margin-left: 32px;"
        "margin-right: 28px;"
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
    QPushButton * btcBN = new QPushButton( "BTC", this );
    QPushButton * rubBN = new QPushButton( "RUB", this );
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
    notificationTB->setIcon( QIcon( ":/Plousios/notification" ) );
    notificationTB->setFixedSize( 60, 60 );
    auxTB->addWidget( notificationTB );

    auxTB->addSeparator();

    QAction * userAN = new QAction( QIcon( ":/Plousios/user" ),
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
        "QToolBar QToolButton {"
            "padding-left: 10px;"
            "padding-right: 10px;"
            "min-width: 80px;"
            "max-width: 80px;"
            "min-height: 80px;"
            "max-height: 80px;"
        "}"
        "QToolBar QWidget {"
            "margin-top: 5px;"
            "margin-bottom: 5px;"
            "font: 75 8pt \"Comic Sans MS\";"
        "}"
    );
    navigationTB->setOrientation( Qt::Vertical );
    navigationTB->setMovable( false );
    navigationTB->setIconSize( QSize( 40, 40 ) );
    navigationTB->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

    QAction * tradingAN = new QAction( QIcon( ":/Plousios/trading" ),
        QString::fromStdWString( L"Трейдинг" ), this );
    QAction * historyAN = new QAction( QIcon( ":/Plousios/history" ),
        QString::fromStdWString( L"История" ), this );
    QAction * portfolioAN = new QAction( QIcon( ":/Plousios/portfolio" ),
        QString::fromStdWString( L"Мои активы" ), this );
    QAction * settingsAN = new QAction( QIcon( ":/Plousios/settings" ),
        QString::fromStdWString( L"Настройки" ), this );
    QAction * exitAN = new QAction( QIcon( ":/Plousios/exit" ),
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
