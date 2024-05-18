#include "stdafx.h"
#include "UserWindow.h"
#include "DatabaseHelper.h"
#include "DatabaseManager.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QDoubleValidator>

UserWindow::UserWindow( DatabaseProcessing::UserData * user_data, QWidget * parent )
    : _user_data( user_data ), QDialog( parent )
{
    setWindowTitle( WToQ( L"Пользователь %1" ).arg( user_data->_nickname ) );
    setFixedSize( 600, 170 );

    _okBN = new QPushButton( this );
    _okBN->setText( WToQ( L"OK" ) );
    _okBN->setMinimumWidth( 100 );
    _exitBN = new QPushButton( this );
    _exitBN->setText( WToQ( L"Отмена" ) );
    _exitBN->setMinimumWidth( 100 );

    _nicknameLE = new QLineEdit( this );
    _nicknameLE->setMinimumWidth( 300 );
    _nicknameLE->setText( user_data->_nickname );
    _nicknameLE->setEnabled( false );

    _passwordLE = new QLineEdit( this );
    _passwordLE->setEchoMode( QLineEdit::Password );
    _passwordLE->setText( user_data->_password );
    _passwordLE->setEnabled( false );

    _balanceLE = new QLineEdit( this );
    _balanceLE->setEnabled( false );
    QDoubleValidator * validator = new QDoubleValidator( 0, 1000000, 2, _balanceLE );
    validator->setNotation( QDoubleValidator::StandardNotation );
    _balanceLE->setValidator( validator );
    _balanceLE->setText( QString::number( _user_data->_balance ) );

    QString change_text = WToQ( L"<html><head/><body><p><span style=\" \
        color:#0000ff; \">Изменить...</span></p></body></html>" );

    _change_nicknameTL = new QLabel( change_text, this );
    _change_passwordTL = new QLabel( change_text, this );
    _change_balanceTL = new QLabel( change_text, this );

    _warningTL = new QLabel( this );

    QLabel * nicknameTL = new QLabel( WToQ( L"Имя пользователя:" ) );
    QLabel * passwordTL = new QLabel( WToQ( L"Пароль:" ) );
    QLabel * balanceTL = new QLabel( WToQ( L"Баланс:" ) );

    QGridLayout * centralGL = new QGridLayout;
    centralGL->addWidget( nicknameTL, 0, 0, 1, 1 );
    centralGL->addWidget( passwordTL, 1, 0, 1, 1 );
    centralGL->addWidget( balanceTL, 2, 0, 1, 1 );
    centralGL->addWidget( _nicknameLE, 0, 2, 1, 1 );
    centralGL->addWidget( _passwordLE, 1, 2, 1, 1 );
    centralGL->addWidget( _balanceLE, 2, 2, 1, 1 );
    centralGL->addWidget( _change_nicknameTL, 0, 3, 1, 1 );
    centralGL->addWidget( _change_passwordTL, 1, 3, 1, 1 );
    centralGL->addWidget( _change_balanceTL, 2, 3, 1, 1 );
    centralGL->addWidget( _warningTL, 3, 0, 1, 4 );
    centralGL->addWidget( _okBN, 4, 0, 1, 1 );
    QSpacerItem * tempSI = new QSpacerItem( 40, 20, QSizePolicy::Expanding );
    centralGL->addItem( tempSI, 4, 1, 1, 2 );
    centralGL->addWidget( _exitBN, 4, 3, 1, 1 );
    setLayout( centralGL );

    _change_nicknameTL->installEventFilter( this );
    _change_passwordTL->installEventFilter( this );
    _change_balanceTL->installEventFilter( this );
    connect( _okBN, &QPushButton::clicked, this, &UserWindow::OnOK );
    connect( _exitBN, &QPushButton::clicked, this, &UserWindow::OnExit );
}

UserWindow::~UserWindow()
{ }

bool UserWindow::eventFilter( QObject * obj, QEvent * event )
{
    if ( event->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent * mouseEvent = static_cast<QMouseEvent *>( event );
        if ( mouseEvent->button() == Qt::LeftButton )
        {
            QLabel * sender = qobject_cast<QLabel *>( obj );
            if ( sender == _change_nicknameTL )
            {
                emit ChangeNickname();
                return true;
            }
            else if ( sender == _change_passwordTL )
            {
                emit ChangePassword();
                return true;
            }
            else if ( sender == _change_balanceTL )
            {
                emit ChangeBalance();
                return true;
            }
        }
    }

    return QObject::eventFilter( obj, event );
}

void UserWindow::OnOK()
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
    if ( _user_data->_nickname != _nicknameLE->text() )
    {
        if ( DatabaseProcessing::UserData * temp = db_manager->GetUserData( _nicknameLE->text() ); temp != nullptr )
        {
            delete temp;
            _warningTL->setText( WToQ( L"Пользователь \'%1\' уже существует." ).arg( _nicknameLE->text() ) );
            return;
        }
    }

    auto * temp_data = new DatabaseProcessing::UserData { 0, _nicknameLE->text(), _passwordLE->text(), _balanceLE->text().replace( ',', '.' ).toDouble() };
    bool result = db_manager->SetUserData( _user_data, temp_data );
    delete temp_data;

    if ( !result )
    {
        _warningTL->setText( WToQ( L"Не удалось изменить данные. Проверьте подключение." ) );
        return;
    }

    done( QDialog::Accepted );
}

void UserWindow::OnExit()
{
    done( QDialog::Rejected );
}

void UserWindow::ChangeNickname()
{
    _nicknameLE->setEnabled( true );
}

void UserWindow::ChangePassword()
{
    _passwordLE->setEnabled( true );
    _passwordLE->setEchoMode( QLineEdit::Normal );
}

void UserWindow::ChangeBalance()
{
    _balanceLE->setEnabled( true );
}