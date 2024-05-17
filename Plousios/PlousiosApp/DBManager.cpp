#include "stdafx.h"
//#include "DBManager.h"
//
//DBManager * DBManager::Instance()
//{
//    if ( instance == nullptr )
//        instance = new DBManager();
//
//    return instance;
//}
//
//DBManager::~DBManager()
//{
//    if ( db.isOpen() )
//        db.close();
//}
//
//DBManager::DBManager()
//{
//    db = QSqlDatabase::addDatabase( "QPSQL" );
//    db.setHostName( "localhost" );
//    db.setDatabaseName( "my_database" );
//    db.setUserName( "my_user" );
//    db.setPassword( "my_password" );
//}