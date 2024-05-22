#pragma once
#include <QDialog>

/*
    Plousios source code. Tak172. 2024.

    @Name:			AddUserWindow.h
    @Created:		23.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

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
