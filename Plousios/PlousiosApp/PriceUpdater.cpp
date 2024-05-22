#include "stdafx.h"
#include "PriceUpdater.h"
#include "DatabaseManager.h"

#include <QTimer>
#include <QThread>

PriceUpdater::PriceUpdater( QObject * parent ) 
    : QObject( parent )
{ }

void PriceUpdater::StartWork() 
{
    while ( QThread::currentThread()->isInterruptionRequested() == false )
    {
        DoWork();
        QThread::sleep( 30 );
    }
}

void PriceUpdater::DoWork()
{
    auto * db_manager = DatabaseProcessing::DatabaseManager::Instance();
    bool result = db_manager->UpdatePrices();
    if ( result == false )
        emit ConnectionLoss();
}