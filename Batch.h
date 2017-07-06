//----------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------

#include <QString>

//----------------------------------------------------------------------

class Alarm;

//----------------------------------------------------------------------
class Batch
{

public:

    static Batch *fromString ( QString &i_stringDefinition );

    static bool isValidPtr ( Batch *i_batch );

    int getAlarmCount ();

    int getFilteredAlarmCount ();

    Alarm * getAlarm ( int i_index );

    QString getId ();

    void appendAlarm ( Alarm *i_alarm );

private:

    Batch ( QStringList &i_components );

    bool setParameter ( QString &i_expression );

    int compareSignature ( const char *i_signature );

    char m_signature [6];

    QString m_id;
    int m_alarmCount;
    int m_start;
    int m_end;
    QString m_flags;

    QList<Alarm *> m_listAlarms;
};