// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.cpp
//! @brief     Implements class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobModel.h"
#include "JobItem.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include <QUuid>
#include <QDebug>
#include <QItemSelection>


JobModel::JobModel(QObject *parent)
    : SessionModel(SessionXML::JobModelTag, parent)
    , m_queue_data(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    m_queue_data = new JobQueueData(this);
    connect(m_queue_data, SIGNAL(focusRequest(QString)), this, SLOT(onFocusRequest(QString)));
    connect(m_queue_data, SIGNAL(globalProgress(int)), this, SIGNAL(globalProgress(int)));
}

JobModel::~JobModel()
{
    delete m_queue_data;
}

//size_t NJobModel::getNumberOfJobs()
//{
//    return rowCount(QModelIndex());
//}

const JobItem *JobModel::getJobItemForIndex(const QModelIndex &index) const
{
    const JobItem *result = dynamic_cast<const JobItem *>(itemForIndex(index));
    Q_ASSERT(result);
    return result;
}

JobItem *JobModel::getJobItemForIndex(const QModelIndex &index)
{
    JobItem *result = dynamic_cast<JobItem *>(itemForIndex(index));
    Q_ASSERT(result);
    return result;
}

JobItem *JobModel::getJobItemForIdentifier(const QString &identifier)
{
    QModelIndex parentIndex;
    for(int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index( i_row, 0, parentIndex );
        JobItem *jobItem = getJobItemForIndex(itemIndex);
        if(jobItem->getIdentifier() == identifier) return jobItem;
    }
    return 0;
}

//JobItem *JobModel::addJob(SampleModel *sampleModel, InstrumentModel *instrumentModel, const QString &run_policy, int numberOfThreads)
//{
//    JobItem *jobItem = dynamic_cast<JobItem *>(insertNewItem(Constants::JobItemType));
//    jobItem->setItemName(generateJobName());
//    jobItem->setSampleModel(sampleModel);
//    jobItem->setInstrumentModel(instrumentModel);
//    jobItem->setIdentifier(generateJobIdentifier());
//    jobItem->setNumberOfThreads(numberOfThreads);

//    jobItem->setRunPolicy(run_policy);

//    if(jobItem->runImmediately() || jobItem->runInBackground())
//        m_queue_data->runJob(jobItem);

//    return jobItem;
//}

//JobItem *JobModel::addJob(const QString &sample_name, const QString &instrument_name, const QString &run_policy, int numberOfThreads)
//{
//    JobItem *jobItem = dynamic_cast<JobItem *>(insertNewItem(Constants::JobItemType));
//    jobItem->setItemName(generateJobName());
//    jobItem->setIdentifier(generateJobIdentifier());
//    jobItem->setNumberOfThreads(numberOfThreads);
//    jobItem->setRunPolicy(run_policy);

//    setSampleForJobItem(jobItem, sample_name);
//    setInstrumentForJobItem(jobItem, instrument_name);

//    if(jobItem->runImmediately() || jobItem->runInBackground())
//        m_queue_data->runJob(jobItem);

//    return jobItem;
//}

JobItem *JobModel::addJob(MultiLayerItem *multiLayerItem, InstrumentItem *instrumentItem, const QString &run_policy, int numberOfThreads)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(insertNewItem(Constants::JobItemType));
    jobItem->setItemName(generateJobName());
    jobItem->setIdentifier(generateJobIdentifier());
    jobItem->setNumberOfThreads(numberOfThreads);
    jobItem->setRunPolicy(run_policy);

    setSampleForJobItem(jobItem, multiLayerItem);
    setInstrumentForJobItem(jobItem, instrumentItem);

    if(jobItem->runImmediately() || jobItem->runInBackground())
        m_queue_data->runJob(jobItem);

    return jobItem;
}

void JobModel::setSampleModel(SampleModel *sampleModel)
{
    m_sampleModel = sampleModel;
}

void JobModel::setInstrumentModel(InstrumentModel *instrumentModel)
{
    m_instrumentModel = instrumentModel;
}

//! The copy of sample with 'sample_name' from m_sampleModel will become a child of given job item
//void JobModel::setSampleForJobItem(JobItem *jobItem, const QString &sample_name)
//{
//    Q_ASSERT(m_sampleModel);
//    Q_ASSERT(jobItem);

//    // removing old multilayer from children of given jobItem
//    MultiLayerItem *old_sample = jobItem->getMultiLayerItem();
//    if(old_sample) {
//        removeRows(indexOfItem(old_sample).row(), 1, indexOfItem(old_sample->parent()));
//    }

//    // copying multilayer to jobItem
//    MultiLayerItem *multilayer = m_sampleModel->getMultiLayerItem(sample_name);
//    Q_ASSERT(multilayer);

//    copyParameterizedItem(multilayer, jobItem);

//    jobItem->setRegisteredProperty(JobItem::P_SAMPLE_NAME, multilayer->itemName());
//}


//! Adds a multilayer to children of given JobItem. If backup=true then multilayer will be added
//! as a backup.
void JobModel::setSampleForJobItem(JobItem *jobItem, MultiLayerItem *multiLayerItem, bool backup)
{
    qDebug() << "WWW 1.1";
    Q_ASSERT(m_sampleModel);
    Q_ASSERT(jobItem);
    Q_ASSERT(multiLayerItem);

    // removing old multilayer (or its backup version) from children of given jobItem
    qDebug() << "WWW 1.2";
    MultiLayerItem *old_sample = jobItem->getMultiLayerItem(backup);
    if(old_sample) {
        removeRows(indexOfItem(old_sample).row(), 1, indexOfItem(old_sample->parent()));
    }

    qDebug() << "WWW 1.3";
    ParameterizedItem *new_item = copyParameterizedItem(multiLayerItem, jobItem);
    QString name = new_item->itemName();
    qDebug() << "WWW 1.4";
    qDebug() << "OOO ";
    qDebug() << "000 " << backup << name << name.remove(Constants::JOB_BACKUP);
    name.remove(Constants::JOB_BACKUP);
    jobItem->setRegisteredProperty(JobItem::P_SAMPLE_NAME, name);

    if(backup) {
        name.append(Constants::JOB_BACKUP);
    }

    new_item->setItemName(name);


}

//! The copy of instrument with 'instrument_name' from m_instrumentModel will become a child of
//! given job item
//void JobModel::setInstrumentForJobItem(JobItem *jobItem, const QString &instrument_name)
//{
//    Q_ASSERT(m_instrumentModel);
//    Q_ASSERT(jobItem);

//    // removing old instrument from children of given jobItem
//    InstrumentItem *old = jobItem->getInstrumentItem();
//    if (old) {
//        removeRows(indexOfItem(old).row(), 1, indexOfItem(old->parent()));
//    }

//    // copying instrument to jobItem
//    InstrumentItem *instrument = m_instrumentModel->getInstrumentItem(instrument_name);
//    Q_ASSERT(instrument);
//    copyParameterizedItem(instrument, jobItem);

//    jobItem->setRegisteredProperty(JobItem::P_INSTRUMENT_NAME, instrument->itemName());
//}

void JobModel::setInstrumentForJobItem(JobItem *jobItem, InstrumentItem *instrumentItem, bool backup)
{
    Q_ASSERT(m_instrumentModel);
    Q_ASSERT(jobItem);
    Q_ASSERT(instrumentItem);

    // removing old instrument from children of given jobItem
    InstrumentItem *old = jobItem->getInstrumentItem(backup);
    if (old) {
        removeRows(indexOfItem(old).row(), 1, indexOfItem(old->parent()));
    }

    ParameterizedItem *new_item = copyParameterizedItem(instrumentItem, jobItem);
    QString name = new_item->itemName();
    name.remove(Constants::JOB_BACKUP);
    jobItem->setRegisteredProperty(JobItem::P_INSTRUMENT_NAME, name);

    if(backup) {
        name.append(Constants::JOB_BACKUP);
    }

    new_item->setItemName(name);

}

//! Backup instrument and sample model for given JobItem. If backup already exists, do nothing.
void JobModel::backup(JobItem *jobItem)
{
    if(!jobItem->getMultiLayerItem(true)) {
        MultiLayerItem *multilayer = jobItem->getMultiLayerItem();
        Q_ASSERT(multilayer);

        setSampleForJobItem(jobItem, multilayer, true);
    }

    if(!jobItem->getInstrumentItem(true)) {
        InstrumentItem *instrument = jobItem->getInstrumentItem();
        Q_ASSERT(instrument);

        setInstrumentForJobItem(jobItem, instrument, true);
    }
}

//! restore instrument and sample model from backup for given JobItem
void JobModel::restore(JobItem *jobItem)
{
    jobItem->blockSignals(true);
    qDebug() << " ";
    qDebug() << " ";
    qDebug() << " ";

    MultiLayerItem *multilayer = jobItem->getMultiLayerItem(true);
    qDebug() << "QQQ" << multilayer->itemName();
    Q_ASSERT(multilayer);

    setSampleForJobItem(jobItem, multilayer);

    InstrumentItem *instrument = jobItem->getInstrumentItem(true);
    Q_ASSERT(instrument);

    setInstrumentForJobItem(jobItem, instrument);

    jobItem->blockSignals(false);
}

void JobModel::runJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::runJob(const QModelIndex &index)";
    JobItem *jobItem = getJobItemForIndex(index);
    jobItem->setRunPolicy(Constants::JOB_RUN_IMMEDIATELY);
    m_queue_data->runJob(jobItem);
}

void JobModel::cancelJob(const QModelIndex &index)
{
    qDebug() << "JobModel::cancelJob(const QModelIndex &index)";
    m_queue_data->cancelJob(getJobItemForIndex(index)->getIdentifier());
}

void JobModel::removeJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::removeJob(const QModelIndex &index)";
    JobItem *jobItem = getJobItemForIndex(index);
    m_queue_data->removeJob(jobItem->getIdentifier());

    emit aboutToDeleteJobItem(jobItem);
    removeRows(index.row(), 1, QModelIndex());
}

void JobModel::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    qDebug() << "NJobModel::onSelectionChanged" << selected;
    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        qDebug() << "NJobModel::onSelectionChanged -> emiting selectionChanged(0)" << indices.back();
        emit selectionChanged(getJobItemForIndex(indices.back()));
    } else {
        qDebug() << "NJobModel::onSelectionChanged -> emiting selectionChanged(0)";
        emit selectionChanged(0);
    }

//    if(!selected.empty() &&  !selected.first().indexes().empty()) {
//        QModelIndex index = selected.first().indexes().at(0);
//        emit selectionChanged(getJobItemForIndex(index));
    //    }
}

// called when jobQueueData asks for focus
void JobModel::onFocusRequest(const QString &identifier)
{
    emit focusRequest(getJobItemForIdentifier(identifier));
}

//! generates job name
QString JobModel::generateJobName()
{
    int glob_index = 0;
    QModelIndex parentIndex;
    for(int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
         QModelIndex itemIndex = index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = itemForIndex(itemIndex)){
             if(item->modelType() == Constants::JobItemType) {
                 QString jobName = item->itemName();
                 if(jobName.startsWith("job")) {
                     int job_index = jobName.remove(0,3).toInt();
                     if(job_index > glob_index) glob_index = job_index;
                 }
             }
         }
    }
    return QString("job")+QString::number(++glob_index);
}


//! generate unique job identifier
QString JobModel::generateJobIdentifier()
{
    return QUuid::createUuid().toString();
}

