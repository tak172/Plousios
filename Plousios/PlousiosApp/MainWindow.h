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
// класс главного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( DatabaseProcessing::UserData *, QWidget * parent = nullptr );
    ~MainWindow();

private slots:

    // слоты действий верхней панели
    void OnClickUser();

    // слоты действий боковой панели
    void OnClickPortfolio();
    void OnClickHistory();
    void OnClickTrading();
    void OnClickExit();

private slots:
    void OnBuyAsset( unsigned id );

private:
    void MakeAuxBar();          // создание верхней вспомогательной панели
    void MakeNavigationBar();   // создание навигационной панели

    QLabel * balanceTL;

    BasicPageWidget * _basic_pageWT;
    DatabaseProcessing::UserData * _user_data;
};
