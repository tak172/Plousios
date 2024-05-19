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
        RU,     // ������
        US,     // �������
        UK,     // ������
        SN,     // �������
        BR,     // ��������
        CAN,    // ������
        EG,     // ������
        FR,     // �������
        CH,     // �����
        IT,     // ������
        JP,     // ������
        CMB,    // ��������
        EST,    // �������
        GM,     // ��������
        ICD,    // ��������
        INZ,    // ���������
        ISR,    // �������
        PTG,    // ����������
        UAE     // ���
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