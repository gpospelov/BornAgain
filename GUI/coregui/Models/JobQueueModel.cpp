#include "JobQueueModel.h"
#include "JobItem.h"
#include "JobQueueItem.h"
#include "JobRunner.h"
#include "mainwindow_constants.h"
#include "Exceptions.h"
#include "GUIHelpers.h"
#include <QMimeData>
#include <iostream>
#include <QDebug>
#include <QThread>
#include <QtGlobal>
#include <QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>
#include <QItemSelection>
#include <QUuid>


JobQueueModel::JobQueueModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_queue_data(new JobQueueData)
    , m_name("DefaultName")

{

}


JobQueueModel::~JobQueueModel()
{
    qDeleteAll(m_jobs);
    delete m_queue_data;
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
        return getJobItemForIndex(index)->getName();
        //return m_jobs.at(index.row())->getName();
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
        getJobItemForIndex(index)->setName(value.toString());
        //m_jobs.at(index.row())->setName(value.toString());
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


void JobQueueModel::addJob(Simulation *simulation)
{
    int position = m_jobs.size();
    beginInsertRows(QModelIndex(), position, position);
    JobQueueItem *queue_item = m_queue_data->createJobQueueItem(simulation);
    m_jobs.append(queue_item);
    endInsertRows();

    JobItem *item = m_queue_data->getJobItem(queue_item->getIdentifier());
    connect(item, SIGNAL(modified(JobItem*)), this, SLOT(onJobItemIsModified(JobItem*)));
}


bool JobQueueModel::removeRows(int position, int rows, const QModelIndex &/* parent */)
{
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
    if (indices.count() != 1) return 0;

    JobQueueItem *item = m_jobs.at(indices.at(0).row());
    Q_ASSERT(item);

    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream dataStream(&encodedData, QIODevice::WriteOnly);
    dataStream << item->getIdentifier();
    mimeData->setData(Constants::MIME_JOBQUEUE, encodedData);
    return mimeData;
}


bool JobQueueModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                int row, int column, const QModelIndex &parent)
{
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

    QByteArray encodedData = data->data(Constants::MIME_JOBQUEUE);
    QDataStream dataStream(&encodedData, QIODevice::ReadOnly);

    QString identifier;
    dataStream >> identifier;
    JobQueueItem *item = new JobQueueItem(identifier);

    beginInsertRows(QModelIndex(), beginRow, beginRow);
    m_jobs.insert(beginRow, item);
    endInsertRows();

    return true;
}


void JobQueueModel::clear()
{
    beginResetModel();
    qDeleteAll(m_jobs);
    m_jobs.clear();
    endResetModel();
}


void JobQueueModel::save(const QString &filename)
{
    if (filename.isEmpty())
        throw GUIHelpers::Error(tr("no filename specified"));
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", "1.9");

    writeTo(&writer);

    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();
}


void JobQueueModel::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);

//    writer->writeStartElement(JobQueueXML::ModelTag);
//    writer->writeAttribute(JobQueueXML::ModelNameAttribute, getName());

//    foreach(JobItem *item, m_jobs) {
//        item->writeTo(writer);
//    }

//    writer->writeEndElement(); // ModelTag
}


void JobQueueModel::load(const QString &filename)
{
    if (filename.isEmpty())
        throw GUIHelpers::Error(tr("no filename specified"));

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());


    QXmlStreamReader reader(&file);
    readFrom(&reader);

    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());

}


void JobQueueModel::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);

//    clear();
//    while (!reader->atEnd()) {
//        reader->readNext();
//        if (reader->isStartElement()) {

//            if (reader->name() == JobQueueXML::ModelTag) {
//                beginResetModel();
//                const QString name = reader->attributes()
//                        .value(JobQueueXML::ModelNameAttribute).toString();
//                qDebug() << "JobQueueModel::readFrom " << name;
//                setName(name);
//            } else if(reader->name() == JobQueueXML::JobTag) {
//                JobItem *job = new JobItem("");
//                job->readFrom(reader);
//                addJob(job);
//            }
//        } else if (reader->isEndElement()) {
//            if (reader->name() == JobQueueXML::ModelTag) {
//                endResetModel();
//            }
//        }
//    }

}

void JobQueueModel::onSelectionChanged( const QItemSelection &selected, const QItemSelection & /*deselected*/)
{
    qDebug() << "JobQueueModel::onSelectionChanged" << selected;
    if(!selected.empty() and !selected.first().indexes().empty()) {
//        int row = selected.first().indexes().at(0).row();
//        JobQueueItem *queueItem = m_jobs.at(row);
//        JobItem *item = m_queue_data.getJobItem(queueItem->getIdentifier());
//        emit selectionChanged(item);
        QModelIndex index = selected.first().indexes().at(0);
        emit selectionChanged(getJobItemForIndex(index));
    }
}


////! returns model index of given JobQueueItem
//QModelIndex JobQueueModel::indexOfItem(JobItem *item) const
//{
//    if(m_jobs.contains(item)) {
//        return index(m_jobs.indexOf(item), 0);
//    }
//    throw GUIHelpers::Error("JobQueueModel::indexOfItem() -> Can't find index for item");
//}


//! Method should be called to inform given model about changes in JobItem
void JobQueueModel::onJobItemIsModified(JobItem *modified_item)
{
    QString identifier = m_queue_data->getIdentifierForJobItem(modified_item);
    foreach(JobQueueItem *queue_item, m_jobs) {
        if(queue_item->getIdentifier() == identifier) {
            QModelIndex item_index = index(m_jobs.indexOf(queue_item), 0);
            dataChanged(item_index, item_index);
        }
    }
}


//! returns JobIdentifier for given model index
QString JobQueueModel::getIdentifier(const QModelIndex &index) const
{
    if(!index.isValid() || index.row() < 0 || index.row() >= rowCount())
        throw GUIHelpers::Error("JobQueueModel::getIdentifier() -> Wrong index");

    return m_jobs.at(index.row())->getIdentifier();
}


//! returns JobItem for given index (const version)
const JobItem *JobQueueModel::getJobItemForIndex(const QModelIndex &index) const
{
    return m_queue_data->getJobItem(getIdentifier(index));
}


//! returns JobItem for given index
JobItem *JobQueueModel::getJobItemForIndex(const QModelIndex &index)
{
    return const_cast<JobItem *>(static_cast<const JobQueueModel &>(*this).getJobItemForIndex(index));
}


//! runs corresponding job in a thread
void JobQueueModel::runInThread(const QModelIndex &index)
{
    m_queue_data->onSubmitJob(getIdentifier(index));

}

//! cancel corresponding job if it is running
void JobQueueModel::onCancelJob(const QModelIndex &index)
{
    m_queue_data->onCancelJob(getIdentifier(index));
}


