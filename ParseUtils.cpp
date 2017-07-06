//----------------------------------------------------------------------

#include "ParseUtils.h"

//----------------------------------------------------------------------
int ParseUtils::getEndingIndex ( QByteArray &i_byteArray, const char *i_szStringToSearch, int &o_offset )
{
    QString stringToSearch (i_szStringToSearch);
    return i_byteArray.indexOf (stringToSearch, o_offset) + stringToSearch.length ();
}

//----------------------------------------------------------------------
int ParseUtils::getNextNumber ( QByteArray &i_byteArray, int &o_offset )
{
    QString digits;

    for ( int i = o_offset; i < o_offset + 20; ++i )
    {
        if (i_byteArray [i] < '0' || i_byteArray [i] > '9')
        {
            break;
        }

        digits.append (i_byteArray.at (i));
    }

    o_offset += digits.length ();

    return digits.toInt ();
}

//----------------------------------------------------------------------
int ParseUtils::getNextNumberAfter ( QByteArray &i_byteArray, const char *i_szStringToSearch, int &o_offset )
{
    int endingIndex = ParseUtils::getEndingIndex (i_byteArray, i_szStringToSearch, o_offset);
    int result = ParseUtils::getNextNumber (i_byteArray, endingIndex);
    o_offset = endingIndex;
    return result;
}

//----------------------------------------------------------------------
QString ParseUtils::getTextBetween ( QByteArray &i_byteArray, const char *i_startString, const char *i_endString, int &o_offset )
{
    int startIndex = ParseUtils::getEndingIndex (i_byteArray, i_startString, o_offset);
    int endIndex = i_byteArray.indexOf (i_endString, startIndex);

    o_offset = endIndex + 1;

    return QString (i_byteArray.mid (startIndex, endIndex - startIndex));
}

//----------------------------------------------------------------------
QString ParseUtils::readLines ( QByteArray &i_byteArray, int linesCount, int &o_offset )
{
    QString result;
    int totalLines = 0;

    while (o_offset < i_byteArray.length ())
    {
        if (i_byteArray [o_offset] == '\n')
        {
            if (++totalLines == linesCount)
            {
                break;
            }
        }

        result.append (i_byteArray.at (o_offset));
        ++o_offset;
    }

    return result.trimmed ();
}

//----------------------------------------------------------------------
QString ParseUtils::getNextWord ( QByteArray &i_byteArray, int &o_offset )
{
    QString result;

    for ( int i = o_offset; i < o_offset + 1000; ++i )
    {
        if (i_byteArray [i] == ' ' || i_byteArray [i] == '\r' || i_byteArray [i] == '\n' || i_byteArray [i] == '\t')
        {
            break;
        }

        result.append (i_byteArray. at (i));
        ++o_offset;
    }

    return result;
}