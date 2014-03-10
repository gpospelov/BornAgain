#ifndef JOBQUEUEMODEL_H
#define JOBQUEUEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "JobQueueItem.h"


namespace JobQueueXML {
const QString ItemTag("Job");
const QString ItemNameAttribute("JobName");
}


class JobQueueModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JobQueueModel(QObject *parent = 0);
    virtual ~JobQueueModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

//    bool insertRows(int position, int rows, const QModelIndex &parent);
    bool removeRows(int position, int rows, const QModelIndex &parent);

    Qt::DropActions supportedDragActions() const { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const { return Qt::MoveAction; }

    QStringList mimeTypes() const;

    QMimeData *mimeData(const QModelIndexList &indexes) const;

    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);


    void addJob(JobQueueItem *item)
    {
        m_jobs.append(item);
    }

private:
    QList <JobQueueItem *> m_jobs;
};


#endif
