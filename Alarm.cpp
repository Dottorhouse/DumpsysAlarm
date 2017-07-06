//----------------------------------------------------------------------

#include <QStringList>
#include <QDateTime>

#include "ParseUtils.h"
#include "SharedData.h"

#include "Alarm.h"

//----------------------------------------------------------------------
Alarm *Alarm::fromString ( QString &i_stringDefinition )
{
    return new Alarm (i_stringDefinition);
}

//----------------------------------------------------------------------
Alarm::Alarm ( QString &i_stringDefinition )
{
    strcpy (m_signature, "ALARM");

    m_parentBatch = nullptr;

    QByteArray byteArray (i_stringDefinition.toLatin1 ().data ());
    int offset = 0;
    //m_alarmType = ParseUtils::getNextWord (byteArray, offset);

    //if (m_alarmType.startsWith ("RTC") == false && m_alarmType.startsWith ("ELAPSED") == false)
    //{
    //    int asd = 0;
    //}

    offset += 2;

    m_index = ParseUtils::getNextNumber (byteArray, offset);

    QString alarmDefinition = ParseUtils::getTextBetween (byteArray, "Alarm{", "}", offset);

    QStringList tmp = alarmDefinition.split (" ");

    m_id = tmp [0];
    m_type = tmp [2].toInt ();

    if (tmp.length () >= 5)
    {
        m_when = tmp [4].toULongLong ();
    }

    if (tmp.last ().startsWith ("com") == true)
    {
        m_ownerPackageName = tmp.last ();
    }

    if (tmp.length () >= 6)
    {
        m_ownerPackageName = tmp [5];
    }

    switch (m_type)
    {
        case 0: m_alarmType = "RTC_WAKEUP"; break;
        case 1: m_alarmType = "RTC"; break;
        case 2: m_alarmType = "ELAPSED_WAKEUP"; break;
        case 3: m_alarmType = "ELAPSED"; break;
    }
}

//----------------------------------------------------------------------
bool Alarm::setParameter ( QString &i_expression )
{
    //QStringList components = i_expression.split ("=");
    //if (components.length () != 2)
    //{
    //    return false;
    //}

    //if (components [0] == "num")
    //{
    //    m_alarmCount = components [1].toInt ();
    //    return true;
    //}

    //// https://stackoverflow.com/questions/28742884/how-to-read-adb-shell-dumpsys-alarm-output
    //// the start and end numbers represent the number of milliseconds that have elapsed since the system was last rebooted as described in this post, (https://stackoverflow.com/a/15400014/296725)
    //// and also roughly represent the window of time in which the alarms in the batch should be triggered.
    //if (components [0] == "start")
    //{
    //    m_start = components [1].toInt ();
    //    return true;
    //}

    //if (components [0] == "end")
    //{
    //    m_end = components [1].toInt ();
    //    return true;
    //}

    return false;
}

//----------------------------------------------------------------------
void Alarm::setParentBatch ( Batch *i_parentBatch )
{
    m_parentBatch = i_parentBatch;
}

//----------------------------------------------------------------------
Batch * Alarm::getParentBatch ()
{
    return m_parentBatch;
}

//----------------------------------------------------------------------
QString Alarm::getId ()
{
    return m_id;
}

//----------------------------------------------------------------------
QString Alarm::getOwnerPackageName ()
{
    return m_ownerPackageName;
}

//----------------------------------------------------------------------
QString Alarm::getAlarmType ()
{
    return m_alarmType;
}

//----------------------------------------------------------------------
QString Alarm::getWhen ()
{
    if (m_alarmType.startsWith ("ELAPSED") == true)
    {
        SharedData *sharedData = SharedData::getInstance ();

        qulonglong millisecondsToFire = m_when - sharedData->getUptimeMilliseconds ();

        return QString ("Fire in %1 seconds").arg (millisecondsToFire / 1000L);
    }
    else if (m_alarmType.startsWith ("RTC") == true)
    {
        SharedData *sharedData = SharedData::getInstance ();

        qulonglong millisecondsToFire = m_when - sharedData->getCurrentTimestamp ();

        return QString ("Fire in %1 seconds").arg (millisecondsToFire / 1000L);
    }

    return "";
}

//----------------------------------------------------------------------
QString Alarm::getFireDateTime ()
{
if (m_alarmType.startsWith ("ELAPSED") == true)
    {
        SharedData *sharedData = SharedData::getInstance ();

        qulonglong millisecondsToFire = m_when - sharedData->getUptimeMilliseconds ();

        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch (sharedData->getCurrentTimestamp () + millisecondsToFire);

        return dateTime.toString ("yyyy/MM/dd hh:mm:ss");
    }
    else if (m_alarmType.startsWith ("RTC") == true)
    {
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch (m_when);

        return dateTime.toString ("yyyy/MM/dd hh:mm:ss");
    }

    return "";
}