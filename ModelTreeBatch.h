//----------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------

#include <QAbstractItemModel>

//----------------------------------------------------------------------

class Batch;

//----------------------------------------------------------------------
class ModelTreeBatch : public QAbstractItemModel
{

public:

    void setBatchList ( QList<Batch*> i_listBatches );

protected:

    //virtual Qt::ItemFlags flags ( const QModelIndex &i_index ) const;

    virtual QVariant data ( const QModelIndex &i_index, int i_role = Qt::DisplayRole ) const;

    virtual QVariant headerData ( int i_section, Qt::Orientation i_orientation, int i_role = Qt::DisplayRole ) const;

    virtual int rowCount ( const QModelIndex &i_parent = QModelIndex () ) const;

    virtual int columnCount ( const QModelIndex &i_parent = QModelIndex () ) const;

    virtual QModelIndex index ( int i_row, int i_column, const QModelIndex &i_parent = QModelIndex () ) const;

    virtual QModelIndex parent ( const QModelIndex &i_index ) const;

private:

    QList<Batch*> m_listBatches;

};