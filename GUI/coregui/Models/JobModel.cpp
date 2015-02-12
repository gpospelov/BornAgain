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
#include <QUuid>
#include <QDebug>
#include <QItemSelection>


JobModel::JobModel(QObject *parent)
    : SessionModel(SessionXML::JobModelTag, parent)
    , m_queue_data(0)
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

JobItem *JobModel::addJob(SampleModel *sampleModel, InstrumentModel *instrumentModel, const QString &run_policy, int numberOfThreads)
{
    JobItem *jobItem = dynamic_cast<JobItem *>(insertNewItem(Constants::JobItemType));
    jobItem->setItemName(generateJobName());
    jobItem->setSampleModel(sampleModel);
    jobItem->setInstrumentModel(instrumentModel);
    jobItem->setIdentifier(generateJobIdentifier());
    jobItem->setNumberOfThreads(numberOfThreads);

    ComboProperty combo_property = jobItem->getRegisteredProperty(JobItem::P_RUN_POLICY).value<ComboProperty>();
    combo_property.setValue(run_policy);
    jobItem->setRegisteredProperty(JobItem::P_RUN_POLICY, combo_property.getVariant());

    if(jobItem->runImmediately() || jobItem->runInBackground())
        m_queue_data->runJob(jobItem);

//    if( jobItem->getRunPolicy() & (JobItem::RUN_IMMEDIATELY | JobItem::RUN_IN_BACKGROUND)  && jobItem->getStatus()!=JobItem::COMPLETED)
//        runJob(queue_item->getIdentifier());

    return jobItem;
}

void JobModel::runJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::runJob(const QModelIndex &index)";
    m_queue_data->runJob(getJobItemForIndex(index));
}

void JobModel::cancelJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::cancelJob(const QModelIndex &index)";
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

