#pragma once

/*
    Plousios source code. Tak172. 2024.

    @Name:			MainWindow.h
    @Created:		14.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

#include <QMainWindow>
#include "ui_MainWindow.h"

enum class Currency;

// ����� �������� ���� ����������
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget * parent = nullptr );
    ~MainWindow();

private slots:

    // ����� �������� ������� ������
    void OnClickUser();
    void OnClickNotification();

    // ����� �������� ������� ������
    void OnClickPortfolio();
    void OnClickHistory();
    void OnClickTrading();
    void OnClickSettings();
    void OnClickExit();

    // ����� ��������� ������
    void OnChangeCurrency( Currency );

private:
    void MakeAuxBar();          // �������� ������� ��������������� ������
    void MakeNavigationBar();   // �������� ������������� ������

    Ui::MainWindowClass ui;
};
