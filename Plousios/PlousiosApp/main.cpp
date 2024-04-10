#include "stdafx.h"
#include "PlousiosApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlousiosApp w;
    w.show();
    return a.exec();
}
