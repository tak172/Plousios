#include "stdafx.h"
#include "PriceUpdater.h"
#include "DatabaseManager.h"

#include <QTimer>
#include <QThread>

/*
    Plousios source code. Tak172. 2024.

    @Name:			PriceUpdater.cpp
    @Created:		23.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

PriceUpdater::PriceUpdater( QObject * parent ) 
    : QObject( parent )
{ }

void PriceUpdater::StartWork() 
{
    while ( QThread::currentThread()->isInterruptionRequested() == false )
    {
        DoWork();
        QThread::sleep( 2 );
    }
}

void PriceUpdater::DoWork()
{
    auto * db_manager = DatabaseProcessing::DatabaseManager::Instance();
    bool result = db_manager->UpdatePrices();
    if ( result == false )
        emit ConnectionLoss();
}