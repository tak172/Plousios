#pragma once

#include <QDate>
#include <QVector>  

static QString WToQ( const std::wstring & stdWStr )
{
	return QString::fromStdWString( stdWStr );
}