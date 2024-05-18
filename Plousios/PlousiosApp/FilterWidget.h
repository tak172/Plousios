#pragma once

#include <QWidget>
#include <QLineEdit>
#include "DatabaseHelper.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			FilterWidget.h
    @Created:		16.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

// Виджет фильтрации данных
class FilterWidget : public QWidget
{
    Q_OBJECT

public:
    FilterWidget( QWidget * parent = nullptr );
    ~FilterWidget();

public slots:
    // слот выбора станы
    void OnSelectCountry( DatabaseProcessing::Countries );

private:
    QLineEdit * _searchLE; // ввод шаблона имени акции
};
