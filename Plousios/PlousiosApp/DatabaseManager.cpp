#include "stdafx.h"
#include "DatabaseManager.h"
#include <exception>

/*
    Plousios source code. Tak172. 2024.

    @Name:			DatabaseManager.cpp
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

namespace DBP = DatabaseProcessing;
DBP::DatabaseManager * DBP::DatabaseManager::instance = nullptr;

DBP::DatabaseManager * DBP::DatabaseManager::Instance()
{
    if ( instance == nullptr )
        instance = new DatabaseManager();

    return instance;
}

DBP::DatabaseManager::~DatabaseManager()
{
    if ( db.isOpen() )
        db.close();
}

DBP::DatabaseManager::DatabaseManager()
{
    QFile file( "pass.txt" );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        return;

    QTextStream in( &file );
    QString password;
    in >> password;
    file.close();

    db = QSqlDatabase::addDatabase( "QPSQL" );
    db.setHostName( "localhost" );
    db.setDatabaseName( "plousios" );
    db.setUserName( "tak172" );
    db.setPassword( password );
    db.open();
}

DBP::UserData * DBP::DatabaseManager::GetUserData( const QString & nickname )
{
    if ( !db.isOpen() )
        return nullptr;

    QSqlQuery query;
    query.prepare( "SELECT * FROM Users WHERE nickname = :nickname" );
    query.bindValue( ":nickname", nickname );

    UserData * result = nullptr;
    if ( query.exec() && query.next() )
    {
        unsigned id = query.value( "id" ).toUInt();
        QString nickname = query.value( "nickname" ).toString();
        QString password = query.value( "password" ).toString();
        double balance = query.value( "balance" ).toDouble();
        result = new UserData{ id, nickname, password, balance };
    }

    return result;
}

DBP::UserData * DBP::DatabaseManager::GetUserData( unsigned id )
{
    if ( !db.isOpen() )
        return nullptr;

    QSqlQuery query;
    query.prepare( "SELECT * FROM Users WHERE id = :id" );
    query.bindValue( ":id", id );

    UserData * result = nullptr;
    if ( query.exec() && query.next() )
    {
        unsigned id = query.value( "id" ).toUInt();
        QString nickname = query.value( "nickname" ).toString();
        QString password = query.value( "password" ).toString();
        double balance = query.value( "balance" ).toDouble();
        result = new UserData { id, nickname, password, balance };
    }

    return result;
}

bool DBP::DatabaseManager::SetUserData( UserData * user_data, const UserData * new_data )
{
    if ( !db.isOpen() || user_data == nullptr || new_data == nullptr )
        return false;

    if ( !db.transaction() )
        return false;

    QSqlQuery query;
    query.prepare( "UPDATE Users SET password = :newPassword WHERE id = :id" );
    query.bindValue( ":newPassword", new_data->_password );
    query.bindValue( ":id", user_data->_id );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    query.prepare( "UPDATE Users SET nickname = :newNickname WHERE id = :id" );
    query.bindValue( ":newNickname", new_data->_nickname );
    query.bindValue( ":id", user_data->_id );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    query.prepare( "UPDATE Users SET balance = :balance WHERE id = :id" );
    query.bindValue( ":balance", new_data->_balance );
    query.bindValue( ":id", user_data->_id );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    if ( !db.commit() )
        throw std::runtime_error( "Failed to commit transaction!" );

    user_data->_nickname = new_data->_nickname;
    user_data->_password = new_data->_password;
    user_data->_balance = new_data->_balance;

    return true;
}

bool DBP::DatabaseManager::AddUser( UserData * user_data )
{
    if ( !db.isOpen() || user_data == nullptr )
        return false;

    QSqlQuery query;
    query.prepare( "INSERT INTO Users (nickname, password, balance) VALUES (:nickname, :password, :balance);" );
    query.bindValue( ":nickname", user_data->_nickname );
    query.bindValue( ":password", user_data->_password );
    query.bindValue( ":balance", 0 );

    if ( query.exec() )
    {
        UserData * temp = GetUserData( user_data->_nickname );
        if ( temp != nullptr )
        {
            user_data->_id = temp->_id;
            user_data->_nickname = temp->_nickname;
            user_data->_password = temp->_password;
            user_data->_balance = temp->_balance;
            delete temp;
            return true;
        }
    }
    
    return false;
}

QVector<DBP::AssetData> DatabaseProcessing::DatabaseManager::GetUserAssets( unsigned id )
{
    if ( !db.isOpen() )
        return { };

    QSqlQuery query;
    query.prepare( "SELECT * FROM Assets WHERE owner_id = :id" );
    query.bindValue( ":id", id );

    QVector<AssetData> result;
    if ( query.exec() )
    {
        while ( query.next() )
        {
            AssetData asset;
            asset._id = query.value( "id" ).toUInt();
            asset._name = query.value( "name" ).toString();
            asset._country_id = query.value( "country_id" ).toUInt();
            asset._price = query.value( "price" ).toDouble();
            asset._is_for_sale = query.value( "is_for_sale" ).toBool();
            asset._owner_id = query.value( "owner_id" ).toUInt();
            result.append( asset );
        }
    }

    return result;
}

QVector<DBP::AssetData> DBP::DatabaseManager::GetAssetsList()
{
    if ( !db.isOpen() )
        return { };

    QSqlQuery query;
    query.prepare( "SELECT * FROM Assets WHERE is_for_sale = TRUE" );

    QVector<AssetData> result;
    if ( query.exec() )
    {
        while ( query.next() )
        {
            AssetData asset;
            asset._id = query.value( "id" ).toUInt();
            asset._name = query.value( "name" ).toString();
            asset._country_id = query.value( "country_id" ).toUInt();
            asset._price = query.value( "price" ).toDouble();
            asset._is_for_sale = query.value( "is_for_sale" ).toBool();
            asset._owner_id = query.value( "owner_id" ).toUInt();
            result.append( asset );
        }
    }

    return result;
}

QVector<DBP::AssetPriceData> DBP::DatabaseManager::GetAssetPrices( unsigned id )
{
    if ( !db.isOpen() )
        return { };

    QSqlQuery query;
    query.prepare( "SELECT * FROM AssetPrices " 
        "WHERE asset_id = :assetId "
        "ORDER BY timestamp ASC" );
    query.bindValue( ":assetId", id );

    QVector<AssetPriceData> trades;
    if ( query.exec() )
    {
        while ( query.next() )
        {
            AssetPriceData trade;
            trade._id = query.value( "id" ).toUInt();
            trade._asset_id = query.value( "asset_id" ).toUInt();
            trade._price = query.value( "price" ).toDouble();
            trade._timestamp = query.value( "timestamp" ).toDateTime();
            trades.append( trade );
        }
    }

    return trades;
}

bool DBP::DatabaseManager::GetAsset( AssetData & asset_data )
{
    if ( !db.isOpen() )
        return { };

    QSqlQuery query;
    query.prepare( "SELECT * FROM Assets WHERE id = :id" );
    query.bindValue( ":id", asset_data._id );

    if ( query.exec() && query.next() )
    {
        asset_data._id = query.value( "id" ).toUInt();
        asset_data._name = query.value( "name" ).toString();
        asset_data._country_id = query.value( "country_id" ).toUInt();
        asset_data._price = query.value( "price" ).toDouble();
        asset_data._is_for_sale = query.value( "is_for_sale" ).toBool();
        asset_data._owner_id = query.value( "owner_id" ).toUInt();
        return true;
    }

    return false;
}

bool DBP::DatabaseManager::BuyAsset( AssetData & asset_data, UserData * buyer )
{
    if ( !db.isOpen() || buyer == nullptr || buyer->_id == asset_data._owner_id )
        return false;

    if ( !db.transaction() )
        return false;   // Failed to start transaction!

    QSqlQuery query;
    query.prepare( "SELECT owner_id, price FROM Assets WHERE id = :assetId AND is_for_sale = TRUE" );
    query.bindValue( ":assetId", asset_data._id );

    if ( !query.exec() || !query.next() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    unsigned seller_id = query.value( "owner_id" ).toUInt();
    double price = query.value( "price" ).toDouble();

    query.prepare( "SELECT balance FROM Users WHERE id = :buyerId" );
    query.bindValue( ":buyerId", buyer->_id );

    if ( !query.exec() || !query.next() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    double buyer_balance = query.value( "balance" ).toDouble();
    if ( buyer_balance < price )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    query.prepare( "UPDATE Users SET balance = balance - :price WHERE id = :buyerId" );
    query.bindValue( ":price", price );
    query.bindValue( ":buyerId", buyer->_id );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    query.prepare( "UPDATE Users SET balance = balance + :price WHERE id = :sellerId" );
    query.bindValue( ":price", price );
    query.bindValue( ":sellerId", seller_id );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    query.prepare( "UPDATE Assets SET is_for_sale = FALSE, owner_id = :buyerId WHERE id = :assetId" );
    query.bindValue( ":buyerId", buyer->_id );
    query.bindValue( ":assetId", asset_data._id );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    query.prepare( "INSERT INTO Trades (buyer_id, seller_id, asset_id, price, timestamp) "
        "VALUES (:buyerId, :sellerId, :assetId, :price, NOW())" );
    query.bindValue( ":buyerId", buyer->_id );
    query.bindValue( ":sellerId", seller_id );
    query.bindValue( ":assetId", asset_data._id );
    query.bindValue( ":price", price );

    if ( !query.exec() )
    {
        if ( !db.rollback() )
            throw std::runtime_error( "Failed to rollback transaction!" );

        return false;
    }

    if ( !db.commit() )
        throw std::runtime_error( "Failed to commit transaction!" );


    DatabaseProcessing::UserData * temp = GetUserData( buyer->_nickname );
    buyer->_balance = temp->_balance;
    delete temp;

    return true;
}

bool DatabaseProcessing::DatabaseManager::PutForSale( unsigned id )
{
    if ( !db.isOpen() )
        return false;

    QSqlQuery query;
    query.prepare( "UPDATE Assets SET is_for_sale = 'true' WHERE id = :id" );
    query.bindValue( ":id", id );
    
    return query.exec();
}

QString DBP::DatabaseManager::GetCountryName( Countries country )
{
    if ( !db.isOpen() )
        return { };

    QSqlQuery query;
    query.prepare( "SELECT name FROM Countries WHERE id = :countryId" );
    query.bindValue( ":countryId", static_cast<unsigned>( country ) );

    if ( query.exec() && query.next() )
        return query.value( "name" ).toString() ;

    return { };
}

QVector<DBP::TradeData> DBP::DatabaseManager::GetUserTradesHistory( unsigned id )
{
    if ( !db.isOpen() )
        return { };

    QSqlQuery query;
    query.prepare( "SELECT * FROM Trades "
        "WHERE buyer_id = :userId OR seller_id = :userId "
        "ORDER BY timestamp ASC" );
    query.bindValue( ":userId", id );

    QVector<TradeData> result;
    if ( query.exec() )
    {
        while ( query.next() )
        {
            TradeData trade;
            trade._id = query.value( "id" ).toUInt();
            trade._buyer_id = query.value( "buyer_id" ).toUInt();
            trade._seller_id = query.value( "seller_id" ).toUInt();
            trade._asset_id = query.value( "asset_id" ).toUInt();
            trade._price = query.value( "price" ).toDouble();
            trade._timestamp = query.value( "timestamp" ).toDateTime();
            result.append( trade );
        }
    }

    return result;
}