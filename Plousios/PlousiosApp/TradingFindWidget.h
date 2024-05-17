#pragma once

#include <QWidget>
#include <QLineEdit>

/*
    Plousios source code. Tak172. 2024.

    @Name:			TradingFindWidget.h
    @Created:		16.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

// Виджет фильтрации данных
class TradingFindWidget : public QWidget
{
    Q_OBJECT

public:
    // множество стран
    enum class Countries
    {
        ALL,
        RU,
        US,
        UK,
        SN,
        BR,
        CAN,
        EG,
        FR,
        CH,
        IT,
        JP,
        CMB,
        EST,
        GM,
        ICD,
        INZ,
        ISR,
        PTG,
        UAE
    };

    TradingFindWidget( QWidget * parent = nullptr );
    ~TradingFindWidget();

public slots:
    // слот выбора станы
    void OnSelectCountry( Countries );

private:
    QLineEdit * _searchLE; // ввод шаблона имени акции
};
