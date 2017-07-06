//----------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------

#include <QString>

//----------------------------------------------------------------------
class SharedData
{

public:

    static SharedData *getInstance ();

    void setCurrentTimestamp ( qulonglong i_timestamp );

    qulonglong getCurrentTimestamp ();

    void setDateTime ( QString i_dateTime );

    QString getDateTime ();

    void setUptimeMilliseconds ( qulonglong i_uptimeMs );

    qulonglong getUptimeMilliseconds ();

private:

    SharedData ();

    static SharedData *s_instance;

    qulonglong m_timestamp;
    qulonglong m_uptimeMs;
    QString m_dateTime;

};