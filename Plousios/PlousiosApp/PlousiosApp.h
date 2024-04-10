#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PlousiosApp.h"

class PlousiosApp : public QMainWindow
{
    Q_OBJECT

public:
    PlousiosApp(QWidget *parent = nullptr);
    ~PlousiosApp();

private:
    Ui::PlousiosAppClass ui;
};
