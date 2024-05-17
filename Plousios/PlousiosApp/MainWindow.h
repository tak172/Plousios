#pragma once

/*
    Plousios source code. Tak172. 2024.

    @Name:			MainWindow.h
    @Created:		14.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

#include <QMainWindow>

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

    // ����� �������� ������� ������
    void OnClickPortfolio();
    void OnClickHistory();
    void OnClickTrading();
    void OnClickExit();

private:
    void MakeAuxBar();          // �������� ������� ��������������� ������
    void MakeNavigationBar();   // �������� ������������� ������
};
