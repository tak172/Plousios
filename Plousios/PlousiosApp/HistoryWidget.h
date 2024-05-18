#pragma once
#include <QTableWidget>

/*
    Plousios source code. Tak172. 2024.

    @Name:			HistoryWidget.h
    @Created:		18.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

class HistoryWidget : public QTableWidget
{ 
    Q_OBJECT

public:
    HistoryWidget( unsigned user_id, QWidget * = nullptr );
    ~HistoryWidget();

    void UpdateHistory();

signals:
    void ClickAsset( unsigned );

private slots:
    void OnClickAsset( int );

private:
    unsigned _user_id;
};

