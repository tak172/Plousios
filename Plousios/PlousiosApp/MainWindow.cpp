#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    MakeNavigationBar();
}

MainWindow::~MainWindow()
{}


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

void MainWindow::MakeNavigationBar()
{
    QToolBar * navigationTB = new QToolBar( "Боковая панель" );
    navigationTB->setStyleSheet(
        "QToolBar QToolButton {"
            "padding-left: 10px;"
            "padding-right: 10px;"
            "min-width: 90px;"
            "max-width: 90px;"
            "min-height: 90px;"
            "max-height: 90px;"
        "}"
        "QToolBar QWidget {"
            "margin-top: 5px;"
            "margin-bottom: 5px;"
            "font: 75 8pt \"Comic Sans MS\";"
        "}"
    );
    navigationTB->setOrientation( Qt::Vertical );
    navigationTB->setMovable( false );
    navigationTB->setIconSize( QSize( 45, 45 ) );
    navigationTB->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

    QAction * tradingAN = new QAction( QIcon( ":/Plousios/trading" ),
        QString::fromStdWString( L"Трейдинг" ), this );
    QAction * historyAN = new QAction( QIcon( ":/Plousios/history" ),
        QString::fromStdWString( L"История сделок" ), this );
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
