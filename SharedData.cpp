//----------------------------------------------------------------------

#include "SharedData.h"

//----------------------------------------------------------------------

SharedData *SharedData::s_instance = nullptr;

//----------------------------------------------------------------------
SharedData::SharedData ()
{
    m_dateTime = "";
    m_timestamp = 0L;
    m_uptimeMs = 0L;
}

//----------------------------------------------------------------------
SharedData *SharedData::getInstance ()
{
    if (SharedData::s_instance == nullptr)
    {
        SharedData::s_instance = new SharedData ();
    }

    return SharedData::s_instance;
}

//----------------------------------------------------------------------
void SharedData::setCurrentTimestamp ( qulonglong i_timestamp )
{
    m_timestamp = i_timestamp;
}

//----------------------------------------------------------------------
qulonglong SharedData::getCurrentTimestamp ()
{
    return m_timestamp;
}

//----------------------------------------------------------------------
void SharedData::setDateTime ( QString i_dateTime )
{
    m_dateTime = i_dateTime;
}

//----------------------------------------------------------------------
QString SharedData::getDateTime ()
{
    return m_dateTime;
}

//----------------------------------------------------------------------
void SharedData::setUptimeMilliseconds ( qulonglong i_uptimeMs )
{
    m_uptimeMs = i_uptimeMs;
}

//----------------------------------------------------------------------
qulonglong SharedData::getUptimeMilliseconds ()
{
    return m_uptimeMs;
}