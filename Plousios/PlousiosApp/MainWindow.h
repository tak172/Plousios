#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    
    // слоты действий боковой панели
    void OnClickPortfolio();
    void OnClickHistory();
    void OnClickTrading();
    void OnClickSettings();
    void OnClickExit();

private:
    void MakeNavigationBar();

    Ui::MainWindowClass ui;
};
