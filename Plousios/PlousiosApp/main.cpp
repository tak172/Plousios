#include "stdafx.h"
#include "MainWindow.h"
#include "DatabaseManager.h"
#include "AuthentificationWindow.h"

#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QFile>
#include <QAbstractButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
        a.quit();
        exit( 1 );
    }

    AuthentificationWindow authentification;
    if ( authentification.exec() == QDialog::Rejected )
    {
        a.quit();
        exit( 1 );
    }

    MainWindow w( authentification.GetUserData() );
    w.show();
    return a.exec();
}