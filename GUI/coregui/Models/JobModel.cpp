// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobModel.cpp
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
#include "FitSuiteItem.h"
#include "GUIHelpers.h"
#include "InstrumentItem.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "JobItemHelper.h"
#include "JobQueueData.h"
#include "MultiLayerItem.h"
#include "ParameterTreeBuilder.h"
#include "ParameterTreeItems.h"
#include "RealDataItem.h"
#include "SimulationOptionsItem.h"
#include "JobModelFunctions.h"
#include "ImportDataAssistant.h"
#include <QDebug>


JobModel::JobModel(QObject *parent)
    : SessionModel(SessionXML::JobModelTag, parent)
    , m_queue_data(0)
{
    m_queue_data = new JobQueueData(this);
    connect(m_queue_data, SIGNAL(focusRequest(JobItem *)), this, SIGNAL(focusRequest(JobItem *)));
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
JobItem *JobModel::addJob(const MultiLayerItem *multiLayerItem,
                          const InstrumentItem *instrumentItem,
                          const RealDataItem *realDataItem,
                          const SimulationOptionsItem *optionItem)
{
    Q_ASSERT(multiLayerItem);
    Q_ASSERT(instrumentItem);
    Q_ASSERT(optionItem);

    JobItem *jobItem = dynamic_cast<JobItem *>(insertNewItem(Constants::JobItemType));
    jobItem->setItemName(generateJobName());
    jobItem->setIdentifier(GUIHelpers::createUuid());

    SessionItem *multilayer = copyParameterizedItem(multiLayerItem, jobItem, JobItem::T_SAMPLE);
    multilayer->setItemName(Constants::MultiLayerType);
    SessionItem *instrument = copyParameterizedItem(instrumentItem, jobItem, JobItem::T_INSTRUMENT);
    instrument->setItemName(Constants::InstrumentType);
    copyParameterizedItem(optionItem, jobItem, JobItem::T_SIMULATION_OPTIONS);

    jobItem->getItem(JobItem::P_SAMPLE_NAME)->setValue(multiLayerItem->itemName());
    jobItem->getItem(JobItem::P_INSTRUMENT_NAME)->setValue(instrumentItem->itemName());

    ParameterTreeBuilder::createParameterTree(jobItem, JobItem::T_PARAMETER_TREE);

    insertNewItem(Constants::IntensityDataType, indexOfItem(jobItem), -1, JobItem::T_OUTPUT);

    if(realDataItem)
        JobModelFunctions::setupJobItemForFit(jobItem, realDataItem);

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
    foreach (SessionItem *item, topItems(Constants::JobItemType)) {
        removeJob(item->index());
    }
    SessionModel::clear();
}

//! Loads OutputData from the projectDir to JobItem

void JobModel::loadNonXMLData(const QString &projectDir)
{
    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = getJobItemForIndex(index(i, 0, QModelIndex()));
        JobItemHelper::loadIntensityData(jobItem, projectDir);
        if(RealDataItem *refItem = jobItem->realDataItem()) {
            ImportDataAssistant::loadIntensityData(refItem, projectDir);
            refItem->linkToInstrument(jobItem->instrumentItem());
        }
    }
}

//! Saves JobItem's OutputData to the projectDir

void JobModel::saveNonXMLData(const QString &projectDir)
{
    for (int i = 0; i < rowCount(QModelIndex()); ++i) {
        JobItem *jobItem = getJobItemForIndex(index(i, 0, QModelIndex()));
        JobItemHelper::saveIntensityData(jobItem->intensityDataItem(), projectDir);
        if(RealDataItem *refItem = jobItem->realDataItem())
            JobItemHelper::saveIntensityData(refItem->intensityDataItem(), projectDir);
    }
}

void JobModel::onCancelAllJobs()
{
    m_queue_data->onCancelAllJobs();
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

void JobModel::restoreItem(SessionItem *item)
{
    if (ParameterItem *parameter = dynamic_cast<ParameterItem*>(item)) {
        parameter->propagateValueLink(true);
    }
    for (auto child : item->childItems()) {
        restoreItem(child);
    }
}
