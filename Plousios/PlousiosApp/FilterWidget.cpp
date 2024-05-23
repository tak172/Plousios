#include "stdafx.h"
#include "FilterWidget.h"

#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>

/*
    Plousios source code. Tak172. 2024.

    @Name:			FilterWidget.cpp
    @Created:		16.04.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

#pragma warning(disable: 4700)

namespace DBP = DatabaseProcessing;

FilterWidget::FilterWidget( QWidget * parent )
    : QWidget( parent ), _used_country( DatabaseProcessing::Countries::ALL )
{
    setFixedWidth( 300 );
    QVBoxLayout * mainVL = new QVBoxLayout( this );
    mainVL->setContentsMargins( 0, 0, 0, 0 );
    _searchLE = new QLineEdit( this );
    _searchLE->setPlaceholderText( QString::fromStdWString( L"�����" ) );
    _searchLE->setFixedWidth( 300 );
    mainVL->addWidget( _searchLE );

    QListWidget * countriesLW = new QListWidget( this );
    auto init_bn = [ countriesLW, this ] ( QPushButton * bn,
        const QIcon & icon, const std::wstring & text, DBP::Countries type )
    {
        bn = new QPushButton( this );
        bn->setText( QString::fromStdWString( text ) );
        bn->setIcon( icon );
        bn->setFixedHeight( 30 );
        bn->setFixedWidth( 288 );
        bn->setStyleSheet( "padding: 5px;" );
        QListWidgetItem * item = new QListWidgetItem;
        item->setSizeHint( bn->sizeHint() );
        countriesLW->addItem( item );
        countriesLW->setItemWidget( item, bn );
        connect( bn, &QPushButton::clicked, this, [ this, type ] ()
        {
            this->OnSelectCountry( type );
        } );
    };

    QPushButton * allBN, * rusBN, * usBN, * ukBN, * snBN, * brBN,
        * canBN, * egBN, * frBN, * chBN, * itBN, * jpBN, * cmbBN,
        * estBN, * gmBN, * icd, * inz, * isr, * ptg, * uae;
    init_bn( allBN, QIcon( ":/Plousios/all" ), L"����� ������", DBP::Countries::ALL );
    init_bn( rusBN, QIcon( ":/Plousios/rus" ), L"������", DBP::Countries::RU );
    init_bn( usBN, QIcon( ":/Plousios/us" ), L"����������� �����", DBP::Countries::US );
    init_bn( ukBN, QIcon( ":/Plousios/uk" ), L"������", DBP::Countries::UK );
    init_bn( snBN, QIcon( ":/Plousios/sn" ), L"�������", DBP::Countries::SN );
    init_bn( brBN, QIcon( ":/Plousios/br" ), L"��������", DBP::Countries::BR );
    init_bn( canBN, QIcon( ":/Plousios/can" ), L"������", DBP::Countries::CAN );
    init_bn( egBN, QIcon( ":/Plousios/eg" ), L"������", DBP::Countries::EG );
    init_bn( frBN, QIcon( ":/Plousios/fr" ), L"�������", DBP::Countries::FR );
    init_bn( chBN, QIcon( ":/Plousios/ch" ), L"�����", DBP::Countries::CH );
    init_bn( itBN, QIcon( ":/Plousios/it" ), L"������", DBP::Countries::IT );
    init_bn( jpBN, QIcon( ":/Plousios/jp" ), L"������", DBP::Countries::JP );
    init_bn( cmbBN, QIcon( ":/Plousios/cmb" ), L"��������", DBP::Countries::CMB );
    init_bn( estBN, QIcon( ":/Plousios/est" ), L"�������", DBP::Countries::EST );
    init_bn( gmBN, QIcon( ":/Plousios/gm" ), L"��������", DBP::Countries::GM);
    init_bn( icd, QIcon( ":/Plousios/icd" ), L"��������", DBP::Countries::ICD );
    init_bn( inz, QIcon( ":/Plousios/inz" ), L"���������", DBP::Countries::INZ );
    init_bn( isr, QIcon( ":/Plousios/isr" ), L"�������", DBP::Countries::ISR );
    init_bn( ptg, QIcon( ":/Plousios/ptg" ), L"����������", DBP::Countries::PTG );
    init_bn( uae, QIcon( ":/Plousios/uae" ), L"���", DBP::Countries::UAE );

    countriesLW->setStyleSheet( "QListWidget::item { padding: 5px; }" );
    mainVL->addWidget( countriesLW );
    setLayout( mainVL );

    connect( _searchLE, &QLineEdit::textChanged, this, &FilterWidget::OnChanged );
}

FilterWidget::~FilterWidget()
{}

void FilterWidget::OnSelectCountry( DBP::Countries country )
{
    _used_country = country;
    OnChanged();
}

void FilterWidget::OnChanged()
{
    emit FilterChanged( { _used_country, _searchLE->text() } );
}