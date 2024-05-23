#pragma once
#include "DatabaseManager.h"

/*
    Plousios source code. Tak172. 2024.

    @Name:			FilterHelper.h
    @Created:		23.05.2024
    @Programmer:	Timofey Kromachev

    Implementations. */

struct Filter
{
    DatabaseProcessing::Countries _country;
    QString _pattern;
};