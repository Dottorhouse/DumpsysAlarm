//----------------------------------------------------------------------

#include <QStringList>

#include "Alarm.h"

#include "Batch.h"

//----------------------------------------------------------------------
Batch *Batch::fromString ( QString &i_stringDefinition )
{
    QStringList components = i_stringDefinition.split (" ");

    if (components.count () < 4)
    {
        return nullptr;
    }

    return new Batch (components);
}

//----------------------------------------------------------------------
bool Batch::isValidPtr ( Batch *i_batch )
{
    if (i_batch == nullptr)
    {
        return false;
    }

    return i_batch->compareSignature ("BATCH") == 0;
}

//----------------------------------------------------------------------
Batch::Batch ( QStringList &i_components )
{
    strcpy (m_signature, "BATCH");

    m_id = i_components [0];

    if (i_components.count () >= 5)
    {
        m_flags = i_components [4];
    }

    setParameter (i_components [1]);
    setParameter (i_components [2]);
    setParameter (i_components [3]);
}

//----------------------------------------------------------------------
bool Batch::setParameter ( QString &i_expression )
{
    QStringList components = i_expression.split ("=");
    if (components.length () != 2)
    {
        return false;
    }

    if (components [0] == "num")
    {
        m_alarmCount = components [1].toInt ();
        return true;
    }

    // https://stackoverflow.com/questions/28742884/how-to-read-adb-shell-dumpsys-alarm-output
    // the start and end numbers represent the number of milliseconds that have elapsed since the system was last rebooted as described in this post, (https://stackoverflow.com/a/15400014/296725)
    // and also roughly represent the window of time in which the alarms in the batch should be triggered.
    if (components [0] == "start")
    {
        m_start = components [1].toInt ();
        return true;
    }

    if (components [0] == "end")
    {
        m_end = components [1].toInt ();
        return true;
    }

    return false;
}

//----------------------------------------------------------------------
int Batch::compareSignature ( const char *i_signature )
{
    return strcmp (m_signature, i_signature);
}

//----------------------------------------------------------------------
int Batch::getAlarmCount ()
{
    return m_alarmCount;
}

//----------------------------------------------------------------------
int Batch::getFilteredAlarmCount ()
{
    return m_listAlarms.count ();
}

//----------------------------------------------------------------------
Alarm * Batch::getAlarm ( int i_index )
{
    return m_listAlarms [i_index];
}

//----------------------------------------------------------------------
QString Batch::getId ()
{
    return m_id;
}

//----------------------------------------------------------------------
void Batch::appendAlarm ( Alarm *i_alarm )
{
    i_alarm->setParentBatch (this);
    m_listAlarms.append (i_alarm);
}