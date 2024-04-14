#include "stdafx.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile styleFile( ":/Plousios/Obit" );
    styleFile.open( QFile::ReadOnly );
    QString styleSheet = QLatin1String( styleFile.readAll() );
    qApp->setStyleSheet( styleSheet );


    MainWindow w;
    w.show();
    return a.exec();
}
