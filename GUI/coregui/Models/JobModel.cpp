// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobModel.cpp
//! @brief     Implements class JobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobModel.h"
#include "JobQueueData.h"
#include "JobItem.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "MultiLayerItem.h"
#include "InstrumentItem.h"
#include "ParameterModelBuilder.h"
#include "ParameterTreeItems.h"
#include "SimulationOptionsItem.h"
#include "JobResultsPresenter.h"
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
    setObjectName(SessionXML::JobModelTag);
}

JobModel::~JobModel()
{
    delete m_queue_data;
}

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


//! Main method to add a job
JobItem *JobModel::addJob(const MultiLayerItem *multiLayerItem, const InstrumentItem *instrumentItem,
        const SimulationOptionsItem *optionItem)
{
    Q_ASSERT(multiLayerItem);
    Q_ASSERT(instrumentItem);
    Q_ASSERT(optionItem);

    JobItem *jobItem = dynamic_cast<JobItem *>(insertNewItem(Constants::JobItemType));
    jobItem->setItemName(generateJobName());
    jobItem->setIdentifier(generateJobIdentifier());

    SessionItem *multilayer = copyParameterizedItem(multiLayerItem, jobItem, JobItem::T_SAMPLE);
    multilayer->setItemName(Constants::MultiLayerType);
    copyParameterizedItem(instrumentItem, jobItem, JobItem::T_INSTRUMENT);
    copyParameterizedItem(optionItem, jobItem, JobItem::T_SIMULATION_OPTIONS);

    jobItem->getItem(JobItem::P_SAMPLE_NAME)->setValue(multiLayerItem->itemName());
    jobItem->getItem(JobItem::P_INSTRUMENT_NAME)->setValue(instrumentItem->itemName());

    ParameterModelBuilder::createParameterTree(jobItem, JobItem::T_PARAMETER_TREE);

    insertNewItem(Constants::IntensityDataType, indexOfItem(jobItem), -1, JobItem::T_OUTPUT);
    insertNewItem(Constants::IntensityDataType, indexOfItem(jobItem), -1, JobItem::T_REALDATA);

    return jobItem;
}

//! restore instrument and sample model from backup for given JobItem
void JobModel::restore(JobItem *jobItem)
{
    restoreItem(jobItem->getItem(JobItem::T_PARAMETER_TREE));
}

bool JobModel::hasUnfinishedJobs()
{
    return m_queue_data->hasUnfinishedJobs();
}

void JobModel::clear()
{
    QMap<QString, SessionItem *> jobs = getTopItemMap(Constants::JobItemType);
    for(auto it = jobs.begin(); it!=jobs.end(); ++it) {
        removeJob(it.value()->index());
    }

    SessionModel::clear();
}

//! Loads OutputData from the projectDir to JobItem

void JobModel::loadNonXMLData(const QString &projectDir)
{
    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = getJobItemForIndex(index(i, 0, QModelIndex()));
        JobResultsPresenter::loadIntensityData(jobItem, projectDir);
    }

}

//! Saves JobItem's OutputData to the projectDir

void JobModel::saveNonXMLData(const QString &projectDir)
{
    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = getJobItemForIndex(index(i, 0, QModelIndex()));
        JobResultsPresenter::saveIntensityData(jobItem, projectDir);
    }
}

void JobModel::runJob(const QModelIndex &index)
{
    m_queue_data->runJob(getJobItemForIndex(index));
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
    Q_ASSERT(jobItem);
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

         if (SessionItem *item = itemForIndex(itemIndex)){
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

void JobModel::restoreItem(SessionItem *item)
{
    if (ParameterItem *parameter = dynamic_cast<ParameterItem*>(item)) {
        parameter->propagateValueLink(true);
    }
    for (auto child : item->childItems()) {
        restoreItem(child);
    }
}

