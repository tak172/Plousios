#pragma once

/*
    Plousios source code. Tak172. 2024.

    @Name:			DatabaseHelper.h
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

namespace DatabaseProcessing
{
    struct UserData
    {
        unsigned _id;
        QString _nickname;
        QString _password;
        double _balance;

        bool operator==( const UserData & other ) const
        {
            return _id == other._id &&
                _nickname == other._nickname &&
                _password == other._password &&
                _balance == other._balance;
        }
    };

    struct AssetData
    {
        unsigned _id;
        QString _name;
        unsigned _country_id;
        double _price;
        bool _is_for_sale;
        unsigned _owner_id;
    };

    struct AssetPriceData
    {
        unsigned _id;
        unsigned _asset_id;
        double _price;
        QDateTime _timestamp;
    };

    enum class Countries
    {
        ALL,
        RU,     // Россия
        US,     // Америка
        UK,     // Англия
        SN,     // Испания
        BR,     // Бразилия
        CAN,    // Канада
        EG,     // Египет
        FR,     // Франция
        CH,     // Китай
        IT,     // Италия
        JP,     // Япония
        CMB,    // Камбоджи
        EST,    // Эстония
        GM,     // Германия
        ICD,    // Исландия
        INZ,    // Индонезия
        ISR,    // Израиль
        PTG,    // Португалия
        UAE     // ОАЭ
    };

    struct TradeData
    {
        unsigned _id;
        unsigned _buyer_id;
        unsigned _seller_id;
        unsigned _asset_id;
        double _price;
        QDateTime _timestamp;
    };
}