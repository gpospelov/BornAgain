#include "JobQueueModel.h"
#include "mainwindow_constants.h"
#include "Exceptions.h"
#include <QMimeData>
#include <iostream>
#include <QDebug>
#include <QtGlobal>


JobQueueModel::JobQueueModel(QObject *parent) :
    QAbstractListModel(parent)
{



}


JobQueueModel::~JobQueueModel()
{
    qDeleteAll(m_jobs);
}


int JobQueueModel::rowCount(const QModelIndex & /* parent */) const
{
    return m_jobs.size();
}


QVariant JobQueueModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_jobs.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return m_jobs.at(index.row())->getName();
    }
    return QVariant();
}


Qt::ItemFlags JobQueueModel::flags(const QModelIndex &index) const
{
//    qDebug() << "JobQueueModel::flags" << index;
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);
    if(index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsEditable | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}


bool JobQueueModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_jobs.at(index.row())->setName(value.toString());
        return true;
    }
    return false;
}


//bool JobQueueModel::insertRows(int position, int rows, const QModelIndex & /* parent */)
//{
//    qDebug() << "JobQueueModel::insertRows";
//    beginInsertRows(QModelIndex(), position, position+rows-1);

//    for (int row = 0; row < rows; ++row) {
//        m_jobs.insert(position, new JobQueueItem(""));
//    }

//    endInsertRows();
//    return true;
//}


bool JobQueueModel::removeRows(int position, int rows, const QModelIndex &/* parent */)
{
    qDebug() << "JobQueueModel::removeRows";
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_jobs.removeAt(position);
    }

    endRemoveRows();
    return true;
}


QStringList JobQueueModel::mimeTypes() const
{
    return QStringList() << Constants::MIME_JOBQUEUE;
}


QMimeData *JobQueueModel::mimeData(const QModelIndexList &indices) const
{
    qDebug() << "----";
    qDebug() << "JobQueueModel::mimeData()" << indices.count() << indices;
    if (indices.count() != 1) return 0;

    JobQueueItem *jobItem = m_jobs.at(indices.at(0).row());
    Q_ASSERT(jobItem);

    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QXmlStreamWriter writer(&encodedData);

    jobItem->writeTo(&writer);

    QString buff;
    QXmlStreamWriter writer2(&buff);
    jobItem->writeTo(&writer2);
    qDebug() << buff;

    const int MaxCompression = 9;
    mimeData->setData(Constants::MIME_JOBQUEUE, qCompress(encodedData, MaxCompression));

    return mimeData;
}


bool JobQueueModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                int row, int column, const QModelIndex &parent)
{
    qDebug() << "JobQueueModel::dropMimeData() 1.1" << row << column << action;
    if (action == Qt::IgnoreAction)
        return true;

    if(!data->hasFormat(Constants::MIME_JOBQUEUE))
        return false;

    if(column > 0)
        return false;

    int beginRow;
    if(row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    qDebug() << "JobQueueModel::dropMimeData() 1.2 beginRow" << beginRow;

    QByteArray encodedData = qUncompress(data->data(Constants::MIME_JOBQUEUE));
    QXmlStreamReader reader(encodedData);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == JobQueueXML::ItemTag) {
                const QString item_name = reader.attributes()
                        .value(JobQueueXML::ItemNameAttribute).toString();
                qDebug() << "JobQueueModel::dropMimeData() 1.2 item_name" << item_name;

                beginInsertRows(QModelIndex(), beginRow, beginRow);

                JobQueueItem *item = new JobQueueItem(item_name);
                m_jobs.insert(beginRow, item);
                endInsertRows();

            }
        }
    }

    return true;
}
