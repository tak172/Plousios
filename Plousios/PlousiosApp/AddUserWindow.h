#pragma once
#include <QDialog>

class QPushButton;
class QLineEdit;
class QLabel;
class AddUserWindow : public QDialog
{ 
public:
    AddUserWindow( QWidget * parent = nullptr );
    ~AddUserWindow();

private slots:
    void OnOK();
    void OnExit();

private:
    QPushButton * _okBN;
    QPushButton * _exitBN;
    QLineEdit * _nicknameLE;
    QLineEdit * _passwordLE;
    QLabel * _warningTL;
};
