#pragma once
#include <QtSql> 
#include <QtCore>
#include "DatabaseHelper.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			DatabaseManager.h
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

namespace DatabaseProcessing
{
    class DatabaseManager
    {
    public:
        static DatabaseManager * Instance();
        ~DatabaseManager();

        bool IsOpen() { return db.isOpen(); }

        UserData * GetUserData( const QString & nickname );
        UserData * GetUserData( unsigned id );
        bool SetUserData( UserData * user_data, const UserData * new_data );
        bool AddUser( UserData * user_data );
        QVector<AssetData> GetUserAssets( unsigned id );

        QVector<AssetData> GetAssetsList();
        QVector<AssetPriceData> GetAssetPrices( unsigned id );
        bool GetAsset( AssetData & asset_data );
        bool BuyAsset( AssetData & asset_data, UserData * buyer );
        bool PutForSale( unsigned id );

        QString GetCountryName( Countries country );
        
        QVector<TradeData> GetUserTradesHistory( unsigned id );

    private:
        DatabaseManager();

        QSqlDatabase db;
        static DatabaseManager * instance;
    };
}