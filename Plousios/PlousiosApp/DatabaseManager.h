#pragma once
#include "DatabaseHelper.h"

#include <QtSql> 
#include <QtCore>
#include <mutex>

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

        bool IsOpen() { return _db.isOpen(); }

        UserData * GetUserData( const QString & nickname );
        UserData * GetUserData( unsigned id );
        bool SetUserData( UserData * user_data, const UserData * new_data );
        bool AddUser( UserData * user_data );
        QVector<AssetData> GetUserAssets( unsigned id );

        QVector<AssetData> GetAssetsList();
        QVector<AssetPriceData> GetAssetPrices( unsigned id );
        bool GetAsset( AssetData & asset_data );
        bool BuyAsset( unsigned asset_id, unsigned buyer_id, double price );
        bool PutForSale( unsigned id, double price );

        QString GetCountryName( Countries country );
        
        QVector<TradeData> GetUserTradesHistory( unsigned id );

        bool UpdatePrices();

    private:
        DatabaseManager();
        DatabaseManager( const DatabaseManager & ) = delete;
        DatabaseManager & operator=( const DatabaseManager & ) = delete;

        QSqlDatabase _db; // <-- protected by _mutex
        std::mutex _mutex;

        static DatabaseManager * _instance; // <-- protected by _instance_mutex
        static std::mutex _instance_mutex;
    };
}