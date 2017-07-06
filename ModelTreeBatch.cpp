//----------------------------------------------------------------------

#include "ModelTreeBatch.h"
#include "Batch.h"
#include "Alarm.h"

//----------------------------------------------------------------------
void ModelTreeBatch::setBatchList ( QList<Batch*> i_listBatches )
{
    beginResetModel ();
    m_listBatches = i_listBatches;
    endResetModel ();
}

////----------------------------------------------------------------------
//Qt::ItemFlags ModelTreeBatch::flags ( const QModelIndex &i_index ) const
//{
//}

//----------------------------------------------------------------------
QVariant ModelTreeBatch::data ( const QModelIndex &i_index, int i_role /*= Qt::DisplayRole*/ ) const
{
    if (i_role == Qt::DisplayRole)
    {
        if (i_index.parent () == QModelIndex ())
        {
            if (i_index.column () == 0)
            {
                int alarmCount = m_listBatches [i_index.row ()]->getFilteredAlarmCount ();
                QString batchId = m_listBatches [i_index.row ()]->getId ();
                return QVariant (QString ("Batch [%1] (%2 alarms)").arg (batchId).arg (alarmCount));
            }
        }
        else
        {
            Alarm *alarm = (Alarm *)i_index.internalPointer ();
            if (i_index.column () == 0)
            {
                return QVariant (QString ("Alarm [%1]").arg (alarm->getId ()));
            }
            else if (i_index.column () == 1)
            {
                return QVariant (alarm->getOwnerPackageName ());
            }
            else if (i_index.column () == 2)
            {
                return QVariant (alarm->getAlarmType ());
            }
            else if (i_index.column () == 3)
            {
                return QVariant (alarm->getWhen ());
            }
            else if (i_index.column () == 4)
            {
                return QVariant (alarm->getFireDateTime ());
            }
        }
    }

    return QVariant ();
}

//----------------------------------------------------------------------
QVariant ModelTreeBatch::headerData ( int i_section, Qt::Orientation i_orientation, int i_role /*= Qt::DisplayRole*/ ) const
{
    if (i_orientation != Qt::Orientation::Horizontal)
    {
        return QVariant ();
    }

    if (i_role == Qt::DisplayRole)
    {
        switch (i_section)
        {
            case 0: return QVariant ("Object ID");
            case 1: return QVariant ("Package");
            case 2: return QVariant ("Alarm Type");
            case 3: return QVariant ("When");
            case 4: return QVariant ("Fire DateTime");
        }
    }

    return QVariant ();
}

//----------------------------------------------------------------------
int ModelTreeBatch::rowCount ( const QModelIndex &i_parent /*= QModelIndex ()*/ ) const
{
    if (i_parent == QModelIndex ())
    {
       return m_listBatches.count ();
    }

    Batch *batch = (Batch *)i_parent.internalPointer ();
    if (Batch::isValidPtr (batch) == true)
    {
        return batch->getFilteredAlarmCount ();
    }

    return 0;
}

//----------------------------------------------------------------------
int ModelTreeBatch::columnCount ( const QModelIndex &i_parent /*= QModelIndex ()*/ ) const
{
    return 5;
}

//----------------------------------------------------------------------
QModelIndex ModelTreeBatch::index ( int i_row, int i_column, const QModelIndex &i_parent /*= QModelIndex ()*/ ) const
{
    if (i_parent == QModelIndex ())
    {
        if (m_listBatches.count () > i_row)
        {
            return createIndex (i_row, i_column, m_listBatches [i_row]);
        }
        else
        {
            return createIndex (i_row, i_column, nullptr);
        }
    }

    Batch *batch = (Batch *)i_parent.internalPointer ();

    return createIndex (i_row, i_column, batch->getAlarm (i_row));
}

//----------------------------------------------------------------------
QModelIndex ModelTreeBatch::parent ( const QModelIndex &i_index ) const
{
    Batch *batch = (Batch *)i_index.internalPointer ();
    if (batch == nullptr)
    {
        return QModelIndex ();
    }

    if (Batch::isValidPtr (batch) == true)
    {
        return QModelIndex ();
    }
    else
    {
        Alarm *alarm = (Alarm *)i_index.internalPointer ();
        batch = alarm->getParentBatch ();
        return createIndex (0, 0, batch);
    }
}