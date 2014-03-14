#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include "JobItem.h"
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


JobQueueModel::JobQueueModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_name("DefaultName")

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


void JobQueueModel::addJob(JobQueueItem *item)
{
    int position = m_jobs.size();
    beginInsertRows(QModelIndex(), position, position);
    m_jobs.append(item);
    endInsertRows();
}



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

//    QString buff;
//    QXmlStreamWriter writer2(&buff);
//    jobItem->writeTo(&writer2);
//    qDebug() << buff;

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
            if (reader.name() == JobQueueXML::JobTag) {
                beginInsertRows(QModelIndex(), beginRow, beginRow);

                JobQueueItem *item = new JobQueueItem("");
                item->readFrom(&reader);
                m_jobs.insert(beginRow, item);
                endInsertRows();

            }
        }
    }

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

    writer->writeStartElement(JobQueueXML::ModelTag);
    writer->writeAttribute(JobQueueXML::ModelNameAttribute, getName());

    foreach(JobQueueItem *item, m_jobs) {
        item->writeTo(writer);
    }

    writer->writeEndElement(); // ModelTag
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

    clear();
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {

            if (reader->name() == JobQueueXML::ModelTag) {
                beginResetModel();
                const QString name = reader->attributes()
                        .value(JobQueueXML::ModelNameAttribute).toString();
                qDebug() << "JobQueueModel::readFrom " << name;
                setName(name);
            } else if(reader->name() == JobQueueXML::JobTag) {
                JobQueueItem *job = new JobQueueItem("");
                job->readFrom(reader);
                addJob(job);
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == JobQueueXML::ModelTag) {
                endResetModel();
            }
        }
    }

}

void JobQueueModel::onSelectionChanged( const QItemSelection &selected, const QItemSelection & /*deselected*/)
{
    qDebug() << "JobQueueModel::onSelectionChanged" << selected;
    if(!selected.empty() and !selected.first().indexes().empty()) {
        int row = selected.first().indexes().at(0).row();
        JobQueueItem *item = m_jobs.at(row);
        emit selectionChanged(item);
    }

//    if(!selected.empty() ) {
//        emit selectionChanged(selected.first());
//    }
}


//! returns model index of given JobQueueItem
QModelIndex JobQueueModel::indexOfItem(JobQueueItem *item) const
{
    if(m_jobs.contains(item)) {
        return index(m_jobs.indexOf(item), 0);
    }
    throw GUIHelpers::Error("JobQueueModel::indexOfItem() -> Can't find index for item");
}


//! Method should be called to inform given model about changes in JobQueueItem
void JobQueueModel::jobQueueItemIsChanged(JobQueueItem *changed_item)
{
    QModelIndex item_index = indexOfItem(changed_item);
    qDebug() << "JobQueueModel::jobQueueItemIsChanged" << item_index;
    dataChanged(item_index, item_index);
}


//! returns JobQueueItem for given index
JobQueueItem *JobQueueModel::getJobQueueItemForIndex(const QModelIndex &index)
{
    if(!index.isValid())
        throw GUIHelpers::Error("JobQueueModel::getJobQueueItemForIndex() -> Can't find item for index");
    if(index.row() >=0 && index.row() < rowCount())
        return m_jobs.at(index.row());
    throw GUIHelpers::Error("JobQueueModel::getJobQueueItemForIndex() -> Can't find item for index p2");
}

const JobQueueItem *JobQueueModel::getJobQueueItemForIndex(const QModelIndex &index) const
{
    if(!index.isValid())
        throw GUIHelpers::Error("JobQueueModel::getJobQueueItemForIndex() -> Can't find item for index");
    if(index.row() >=0 && index.row() < rowCount())
        return m_jobs.at(index.row());
    throw GUIHelpers::Error("JobQueueModel::getJobQueueItemForIndex() -> Can't find item for index p2");
}


void JobQueueModel::runInThread(JobQueueItem *job)
{
    qDebug() << "JobQueueItem::run(): preparing to run a thread" << job->getName();
    JobItem *jobItem = new JobItem();
    QThread *thread = new QThread();
    jobItem->moveToThread(thread);

    // thread will start jobItem::run
    connect(thread, SIGNAL(started()), jobItem, SLOT(run()));

    // thread will quit after JobItem is done
    connect(jobItem, SIGNAL(finished()), thread, SLOT(quit()));
    //connect(jobItem, SIGNAL(finished()), this, SLOT(onJobFinished()));
    connect(jobItem, SIGNAL(progressUpdate(int)), job, SLOT(setProgress(int)));
    connect(job, SIGNAL(modified(JobQueueItem*)), this, SLOT(jobQueueItemIsChanged(JobQueueItem*)));

    // objects will be deleted after JobItem is done
    connect(jobItem, SIGNAL(finished()), jobItem, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    qDebug() << "JobQueueItem::run(): starting thread";
    thread->start();
    qDebug() << "JobQueueItem::run(): thread is started";

}


