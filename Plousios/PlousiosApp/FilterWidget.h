#pragma once

#include <QWidget>
#include <QLineEdit>

#include "DatabaseHelper.h"
#include "FilterHelper.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			FilterWidget.h
    @Created:		16.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

// ������ ���������� ������
class FilterWidget : public QWidget
{
    Q_OBJECT

public:
    FilterWidget( QWidget * parent = nullptr );
    ~FilterWidget();

signals:
    void FilterChanged( const Filter & );

public slots:
    // ���� ������ �����
    void OnSelectCountry( DatabaseProcessing::Countries );
    void OnChanged();

private:
    QLineEdit * _searchLE; // ���� ������� ����� �����
    DatabaseProcessing::Countries _used_country;
};
