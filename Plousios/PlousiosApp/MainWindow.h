#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

// класс главного окна приложения
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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

private:
    void MakeAuxBar();          // создание верхней вспомогательной панели
    void MakeNavigationBar();   // создание навигационной панели

    Ui::MainWindowClass ui;
};
