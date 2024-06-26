#include "stdafx.h"
#include "MainWindow.h"
#include "BasicPageWidget.h"
#include "UserWindow.h"
#include "DatabaseManager.h"

#include <QToolBar>
#include <Qlabel>
#include <QPushButton>
#include <QToolButton>
#include <QMessageBox>

/*
    Plousios source code. Tak172. 2024.

    @Name:			MainWindow.cpp
    @Created:		14.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

MainWindow::MainWindow( DatabaseProcessing::UserData * user_data, QWidget * parent )
    : _user_data( user_data ), QMainWindow( parent )
{
    setWindowTitle( "Plousios" );
    resize( 1500, 800 );
    MakeAuxBar();
    MakeNavigationBar();
    _basic_pageWT = new BasicPageWidget( _user_data->_id, this );
    _basic_pageWT->SetActivePage( BasicPageWidget::PageType::Trading );
    setCentralWidget( _basic_pageWT );

    connect( _basic_pageWT, &BasicPageWidget::UpdateBalance, this, &MainWindow::OnBuyAsset );
}

MainWindow::~MainWindow()
{}

void MainWindow::OnClickUser()
{
    UserWindow userWD( _user_data, this );
    if ( userWD.exec() == QDialog::Accepted )
        balanceTL->setText( WToQ( L"BALANCE:\n$%1" ).arg( QString::number( _user_data->_balance, 'f', 2 ) ) );
}

void MainWindow::OnClickPortfolio()
{
    _basic_pageWT->SetActivePage( BasicPageWidget::PageType::Assets );
}

void MainWindow::OnClickHistory()
{
    _basic_pageWT->SetActivePage( BasicPageWidget::PageType::History );
}

void MainWindow::OnClickTrading()
{
    _basic_pageWT->SetActivePage( BasicPageWidget::PageType::Trading );
}

void MainWindow::OnClickExit()
{
    this->close();
}

void MainWindow::OnBuyAsset()
{
    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    DatabaseProcessing::UserData * user_data = db_manager->GetUserData( _user_data->_id );
    _user_data->_balance = user_data->_balance;
    delete user_data;
    balanceTL->setText( WToQ( L"BALANCE:\n$%1" ).arg( QString::number( _user_data->_balance, 'f', 2 ) ) );
    _basic_pageWT->UpdatePages();
    return;
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

    QString balance_str = WToQ( L"BALANCE:\n$%1" ).arg( QString::number( _user_data->_balance, 'f', 2 ) );
    balanceTL = new QLabel( balance_str, this);
    balanceTL->setAlignment( Qt::AlignCenter );
    balanceTL->setStyleSheet(
        "margin-left: 30px;"
        "margin-right: 30px;"
    );
    auxTB->addWidget( balanceTL );

    QAction * userAN = new QAction( QIcon( ":/Plousios/user_l" ),
        QString::fromStdWString( L"�������" ), this );
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
        QString::fromStdWString( L"��������" ), this );
    QAction * historyAN = new QAction( QIcon( ":/Plousios/history_l" ),
        QString::fromStdWString( L"�������" ), this );
    QAction * portfolioAN = new QAction( QIcon( ":/Plousios/portfolio_l" ),
        QString::fromStdWString( L"������" ), this );
    QAction * exitAN = new QAction( QIcon( ":/Plousios/exit_l" ),
        QString::fromStdWString( L"�����" ), this );

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
