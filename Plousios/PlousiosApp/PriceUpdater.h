#pragma once
#include <QObject>

/*
    Plousios source code. Tak172. 2024.

    @Name:			PriceUpdater.h
    @Created:		23.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

class PriceUpdater : public QObject
{ 
    Q_OBJECT

public:
    explicit PriceUpdater( QObject * parent = nullptr );

signals:
    void ConnectionLoss();

public slots:
    void StartWork();

private slots:
    void DoWork();
};

