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

// класс главного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget * parent = nullptr );
    ~MainWindow();

private slots:

    // слоты действий верхней панели
    void OnClickUser();
    void OnClickNotification();

    // слоты действий боковой панели
    void OnClickPortfolio();
    void OnClickHistory();
    void OnClickTrading();
    void OnClickSettings();
    void OnClickExit();

    // слоты изменения валюты
    void OnChangeCurrency( Currency );

private:
    void MakeAuxBar();          // создание верхней вспомогательной панели
    void MakeNavigationBar();   // создание навигационной панели

    Ui::MainWindowClass ui;
};
