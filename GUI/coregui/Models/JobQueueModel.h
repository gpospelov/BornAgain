#ifndef JOBQUEUEMODEL_H
#define JOBQUEUEMODEL_H

#include <QStandardItemModel>
#include <QAbstractItemModel>

#include "JobQueueItem.h"
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

//class JobQueueModel : public QStandardItemModel
//{
//    Q_OBJECT
//    public:
//    explicit JobQueueModel(QObject *parent = 0);

//};

namespace JobQueueXML {
const QString ItemTag("Item");
const QString ModelTypeAttribute("ModelType");
const QString ItemNameAttribute("ItemName");
const QString ParameterTag("Parameter");
const QString ParameterNameAttribute("ParName");
const QString ParameterValueAttribute("ParValue");
}


class JobQueueModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Column {
        ItemName,
//        ModelType,
        MaxColumns
    };

    explicit JobQueueModel(QObject *parent = 0);
    ~JobQueueModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    Qt::DropActions supportedDragActions() const
        { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const
        { return Qt::MoveAction; }
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                         int row, int column, const QModelIndex &parent) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);


    QModelIndex indexOfItem(JobQueueItem *item) const;


    void insertNewItem(JobQueueItem *itemToInsert,
                                     const QModelIndex &parent=QModelIndex(),
                                     int row=-1);

    JobQueueItem *getRootItem() {return m_root_item; }

private:
//    JobQueueItem *insertNewItem(QString model_type,
//                                     JobQueueItem *parent,
//                                     int row=-1);

    void writeItemAndChildItems(QXmlStreamWriter *writer,
                                              JobQueueItem *item) const;

    void readItems(QXmlStreamReader *reader, JobQueueItem *item,
                   int row=-1);

    JobQueueItem *itemForIndex(const QModelIndex &index) const;

    JobQueueItem *m_root_item;


};



#endif
