#include "stdafx.h"
#include "MainWindow.h"
#include "PriceUpdater.h"
#include "DatabaseManager.h"
#include "AuthentificationWindow.h"

#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QFile>
#include <QAbstractButton>
#include <QThread>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QIcon appIcon( ":/Plousios/logo" );
    QApplication::setWindowIcon( appIcon );

    QFile styleFile( ":/Plousios/Obit" );
    styleFile.open( QFile::ReadOnly );
    QString styleSheet = QLatin1String( styleFile.readAll() );
    qApp->setStyleSheet( styleSheet );

    DatabaseProcessing::DatabaseManager * db_manager = DatabaseProcessing::DatabaseManager::Instance();
    if ( !db_manager->IsOpen() )
    {
        QString message = WToQ( L"Нет соединения с базой данных! Проверьте подключение и повторите попытку." );
        QMessageBox message_box;
        message_box.setWindowTitle( WToQ( L"Ошибка подключения" ) );
        message_box.setText( message );
        message_box.setIcon( QMessageBox::Warning );
        message_box.setStandardButtons( QMessageBox::Ok );
        if ( QAbstractButton * ok_button = message_box.button( QMessageBox::Ok ) )
            ok_button->setMinimumWidth( 100 );

        message_box.exec();
        app.quit();
        exit( 1 );
    }

    PriceUpdater * updater = new PriceUpdater;
    QThread * updater_thread = new QThread;
    updater->moveToThread( updater_thread );

    QObject::connect( updater_thread, &QThread::started, updater, &PriceUpdater::StartWork );
    QObject::connect( &app, &QCoreApplication::aboutToQuit, updater_thread, &QThread::quit );
    QObject::connect( updater, &PriceUpdater::ConnectionLoss, updater_thread, &QThread::quit );
    QObject::connect( updater_thread, &QThread::finished, updater, &QObject::deleteLater );
    QObject::connect( updater_thread, &QThread::finished, updater_thread, &QObject::deleteLater );

    updater_thread->start();

    AuthentificationWindow authentification;
    if ( authentification.exec() == QDialog::Rejected )
    {
        app.quit();
        exit( 1 );
    }

    MainWindow w( authentification.GetUserData() );
    w.show();
    return app.exec();
}