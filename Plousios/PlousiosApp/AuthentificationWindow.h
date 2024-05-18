#pragma once
#include <QDialog>

#include "DatabaseHelper.h"

class QPushButton;
class QLineEdit;
class QLabel;
class AuthentificationWindow : public QDialog
{ 
public:
    AuthentificationWindow( QWidget * parent = nullptr );
    ~AuthentificationWindow();

    DatabaseProcessing::UserData * GetUserData() const { return _user_data; }

protected:
    bool eventFilter( QObject * obj, QEvent * event ) override;

private slots:
    void OnOK();
    void OnExit();
    void OnNewUser();

private:
    QPushButton * _okBN;
    QPushButton * _exitBN;
    QLineEdit * _nicknameLE;
    QLineEdit * _passwordLE;
    QLabel * _new_userTL;
    QLabel * _warningTL;

    DatabaseProcessing::UserData * _user_data;
};