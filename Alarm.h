//----------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------

#include <QString>

//----------------------------------------------------------------------

class Batch;

//----------------------------------------------------------------------
class Alarm
{

public:

    static Alarm *fromString ( QString &i_stringDefinition );

    void setParentBatch ( Batch *i_parentBatch );

    Batch * getParentBatch ();

    QString getId ();

    QString getOwnerPackageName ();

    QString getAlarmType ();

    QString getWhen ();

    QString getFireDateTime ();

private:

    Alarm ( QString &i_stringDefinition );

    bool setParameter ( QString &i_expression );

    char m_signature [6];

    QString m_alarmType;
    int m_index;
    QString m_id;
    int m_type;
    QString m_ownerPackageName;
    Batch *m_parentBatch;
    qulonglong m_when;
};