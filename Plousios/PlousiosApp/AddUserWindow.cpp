#include "stdafx.h"
#include "AddUserWindow.h"
#include "DatabaseManager.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

/*
    Plousios source code. Tak172. 2024.

    @Name:			AddUserWindow.cpp
    @Created:		23.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

AddUserWindow::AddUserWindow( QWidget * parent )
    : QDialog( parent )
{
    setWindowTitle( WToQ( L"����� ������������" ) );
    setFixedSize( 400, 140 );

    QLabel * nicknameTL = new QLabel( WToQ( L"��� ������������:" ), this );
    QLabel * passwordTL = new QLabel( WToQ( L"������:" ), this );

    _nicknameLE = new QLineEdit( this );
    _passwordLE = new QLineEdit( this );

    _okBN = new QPushButton( this );
    _okBN->setMinimumWidth( 110 );
    _okBN->setText( WToQ( L"OK" ) );

    _exitBN = new QPushButton( this );
    _exitBN->setMinimumWidth( 110 );
    _exitBN->setText( WToQ( L"������" ) );

    _warningTL = new QLabel( this );

    QGridLayout * centralGL = new QGridLayout;
    centralGL->addWidget( nicknameTL, 0, 0, 1, 1 );
    centralGL->addWidget( passwordTL, 1, 0, 1, 1 );
    centralGL->addWidget( _nicknameLE, 0, 1, 1, 3 );
    centralGL->addWidget( _passwordLE, 1, 1, 1, 3 );
    centralGL->addWidget( _okBN, 3, 0, 1, 1 );
    QSpacerItem * tempSI = new QSpacerItem( 40, 20, QSizePolicy::Expanding );
    centralGL->addItem( tempSI, 3, 2, 1, 1 );
    centralGL->addWidget( _exitBN, 3, 3, 1, 1 );
    centralGL->addWidget( _warningTL, 2, 0, 1, 4 );
    setLayout( centralGL );

    connect( _okBN, &QPushButton::clicked, this, &AddUserWindow::OnOK );
    connect( _exitBN, &QPushButton::clicked, this, &AddUserWindow::OnExit );
}

AddUserWindow::~AddUserWindow()
{ }

void AddUserWindow::OnOK()
{
    if ( _nicknameLE->text().size() < 3 || _nicknameLE->text().size() > 12 )
    {
        _warningTL->setText( WToQ( L"��� ������������ �������� �� 3 �� 12 ��������." ) );
        return;
    }

    if ( _passwordLE->text().size() < 3 || _passwordLE->text().size() > 12 )
    {
        _warningTL->setText( WToQ( L"������ ������������ �������� �� 3 �� 12 ��������." ) );
        return;
    }

    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    if ( db_manager->GetUserData( _nicknameLE->text() ) != nullptr )
    {
        _warningTL->setText( WToQ( L"������������ � ����� ������ ��� ����������." ) );
        return;
    }

    DatabaseProcessing::UserData user_data;
    user_data._nickname = _nicknameLE->text();
    user_data._password = _passwordLE->text();
    if ( !db_manager->AddUser( &user_data ) )
    {
        _warningTL->setText( WToQ( L"�� ������� �������� ������������. ��������� �����������." ) );
        return;
    }

    done( QDialog::Accepted );
}

void AddUserWindow::OnExit()
{
    done( QDialog::Rejected );
}
