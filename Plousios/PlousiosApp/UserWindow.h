#pragma once
#include <QDialog>

namespace DatabaseProcessing
{
    struct UserData;
}

class QLabel;
class QLineEdit;
class QPushButton;
class UserWindow : public QDialog
{ 
public:
    UserWindow( DatabaseProcessing::UserData *, QWidget * parent = nullptr );
    ~UserWindow();

protected:
    bool eventFilter( QObject * obj, QEvent * event ) override;

private slots:
    void OnOK();
    void OnExit();
    void ChangeNickname();
    void ChangePassword();
    void ChangeBalance();

private:
    QPushButton * _okBN;
    QPushButton * _exitBN;
    QLineEdit * _nicknameLE;
    QLineEdit * _passwordLE;
    QLineEdit * _balanceLE;
    QLabel * _change_nicknameTL;
    QLabel * _change_passwordTL;
    QLabel * _change_balanceTL;
    QLabel * _warningTL;

    DatabaseProcessing::UserData * _user_data;
};

