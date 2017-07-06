//----------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------

#include <QString>

//----------------------------------------------------------------------
class ParseUtils
{

public:

    static int getEndingIndex ( QByteArray &i_byteArray, const char *i_szStringToSearch, int &o_offset );

    static int getNextNumber ( QByteArray &i_byteArray, int &o_offset );

    static int getNextNumberAfter ( QByteArray &i_byteArray, const char *i_szStringToSearch, int &o_offset );

    static QString getTextBetween ( QByteArray &i_byteArray, const char *i_startString, const char *i_endString, int &o_offset );

    static QString readLines ( QByteArray &i_byteArray, int linesCount, int &o_offset );

    static QString getNextWord ( QByteArray &i_byteArray, int &o_offset );

};