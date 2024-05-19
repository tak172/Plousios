#pragma once
#include <QMainWindow>

/*
    Plousios source code. Tak172. 2024.

    @Name:			MainWindow.h
    @Created:		14.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

namespace DatabaseProcessing
{
    struct UserData;
}

class QLabel;
class BasicPageWidget;
// ����� �������� ���� ����������
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( DatabaseProcessing::UserData *, QWidget * parent = nullptr );
    ~MainWindow();

private slots:

    // ����� �������� ������� ������
    void OnClickUser();

    // ����� �������� ������� ������
    void OnClickPortfolio();
    void OnClickHistory();
    void OnClickTrading();
    void OnClickExit();

private slots:
    void OnBuyAsset( unsigned id );

private:
    void MakeAuxBar();          // �������� ������� ��������������� ������
    void MakeNavigationBar();   // �������� ������������� ������

    QLabel * balanceTL;

    BasicPageWidget * _basic_pageWT;
    DatabaseProcessing::UserData * _user_data;
};
