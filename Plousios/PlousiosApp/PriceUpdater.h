#pragma once
#include <QObject>

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

