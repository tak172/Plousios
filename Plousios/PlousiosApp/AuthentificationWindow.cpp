#include "stdafx.h"
#include "AuthentificationWindow.h"
#include "DatabaseManager.h"
#include "AddUserWindow.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QEvent>
#include <QMouseEvent>

AuthentificationWindow::AuthentificationWindow( QWidget * parent )
    : _user_data( nullptr ), QDialog( parent )
{
    setWindowTitle( WToQ( L"Авторизация" ) );
    setFixedSize( 360, 140 );

    QLabel * nicknameTL = new QLabel( WToQ( L"Имя пользователя:" ), this );
    QLabel * passwordTL = new QLabel( WToQ( L"Пароль:" ), this );

    _nicknameLE = new QLineEdit( this );
    _passwordLE = new QLineEdit( this );
    _passwordLE->setEchoMode( QLineEdit::Password );

    _new_userTL = new QLabel( this );
    _new_userTL->setAlignment( Qt::AlignRight );
    _new_userTL->setText( WToQ( L"<html><head/><body><p><span style =\"text-decoration: underline; color:#253bff;\">Зарегистрироваться...</span></p></body></html>" ) );

    _okBN = new QPushButton( this );
    _okBN->setFixedWidth( 110 );
    _okBN->setText( WToQ( L"OK" ) );

    _exitBN = new QPushButton( this );
    _exitBN->setMinimumWidth( 110 );
    _exitBN->setText( WToQ( L"Выход" ) );

    _warningTL = new QLabel( this );

    QGridLayout * centralGL = new QGridLayout;
    centralGL->addWidget( nicknameTL, 0, 0, 1, 1 );
    centralGL->addWidget( passwordTL, 1, 0, 1, 1 );
    centralGL->addWidget( _nicknameLE, 0, 1, 1, 3 );
    centralGL->addWidget( _passwordLE, 1, 1, 1, 3 );
    centralGL->addWidget( _new_userTL, 2, 3, 1, 1 );
    centralGL->addWidget( _okBN, 4, 0, 1, 1 );
    QSpacerItem * tempSI = new QSpacerItem( 40, 20, QSizePolicy::Expanding );
    centralGL->addItem( tempSI, 4, 2, 1, 1 );
    centralGL->addWidget( _exitBN, 4, 3, 1, 1 );
    centralGL->addWidget( _warningTL, 3, 0, 1, 4 );
    setLayout( centralGL );

    _new_userTL->installEventFilter( this );
    connect( _okBN, &QPushButton::clicked, this, &AuthentificationWindow::OnOK );
    connect( _exitBN, &QPushButton::clicked, this, &AuthentificationWindow::OnExit );
}

AuthentificationWindow::~AuthentificationWindow()
{ }

bool AuthentificationWindow::eventFilter( QObject * obj, QEvent * event )
{
    if ( qobject_cast<QLabel *>( obj ) == _new_userTL && event->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent * mouseEvent = static_cast<QMouseEvent *>( event );
        if ( mouseEvent->button() == Qt::LeftButton )
        {
            emit OnNewUser();
            return true;
        }
    }

    return QObject::eventFilter( obj, event );
}

void AuthentificationWindow::OnOK()
{
    if ( _nicknameLE->text().size() < 3 || _nicknameLE->text().size() > 12 )
    {
        _warningTL->setText( WToQ( L"Имя пользователя содержит от 3 до 12 символов." ) );
        return;
    }

    if ( _passwordLE->text().size() < 3 || _passwordLE->text().size() > 12 )
    {
        _warningTL->setText( WToQ( L"Пароль пользователя содержит от 3 до 12 символов." ) );
        return;
    }

    auto db_manager = DatabaseProcessing::DatabaseManager::Instance();
    DatabaseProcessing::UserData * temp = new DatabaseProcessing::UserData;
    temp = db_manager->GetUserData( _nicknameLE->text() );
    if ( temp == nullptr )
    {
        _warningTL->setText( WToQ( L"Пользователя \'%1\' не существует." ).arg(_nicknameLE->text() ) );
        return;
    }

    if ( temp->_password != _passwordLE->text() )
    {
        delete temp;
        _warningTL->setText( WToQ( L"Неверный пароль для пользователя \'%1\'." ).arg( _nicknameLE->text() ) );
        return;
    }

    delete _user_data;
    _user_data = temp;
    done( QDialog::Accepted );
}

void AuthentificationWindow::OnExit()
{
    done( QDialog::Rejected );
}

void AuthentificationWindow::OnNewUser()
{
    AddUserWindow add_userWD;
    add_userWD.exec();
}
