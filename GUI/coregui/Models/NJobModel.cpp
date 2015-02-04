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

#include "NJobModel.h"
#include "NJobItem.h"
#include "ComboProperty.h"
#include <QUuid>
#include <QDebug>
#include <QItemSelection>


NJobModel::NJobModel(QObject *parent)
    : SessionModel(SessionXML::JobModelTag, parent)
    , m_queue_data(new JobQueueData)
{

}

NJobModel::~NJobModel()
{
    delete m_queue_data;
}

//size_t NJobModel::getNumberOfJobs()
//{
//    return rowCount(QModelIndex());
//}

const NJobItem *NJobModel::getJobItemForIndex(const QModelIndex &index) const
{
    const NJobItem *result = dynamic_cast<const NJobItem *>(itemForIndex(index));
    Q_ASSERT(result);
    return result;
}

NJobItem *NJobModel::getJobItemForIndex(const QModelIndex &index)
{
    NJobItem *result = dynamic_cast<NJobItem *>(itemForIndex(index));
    Q_ASSERT(result);
    return result;
}

NJobItem *NJobModel::addJob(SampleModel *sampleModel, InstrumentModel *instrumentModel, const QString &run_policy, int numberOfThreads)
{
    //    JobItem *jobItem = new JobItem(jobSampleModel, jobInstrumentModel, runPolicySelectionBox->currentText());
    //    jobItem->setNumberOfThreads(getNumberOfThreads());
    //    m_jobQueueModel->addJob(jobItem);

    NJobItem *jobItem = dynamic_cast<NJobItem *>(insertNewItem(Constants::JobItemType));
    jobItem->setItemName(generateJobName());
    jobItem->setSampleModel(sampleModel);
    jobItem->setInstrumentModel(instrumentModel);
    jobItem->setRegisteredProperty(NJobItem::P_IDENTIFIER, generateJobIdentifier());
    jobItem->setRegisteredProperty(NJobItem::P_NTHREADS, numberOfThreads);

    ComboProperty combo_property = jobItem->getRegisteredProperty(NJobItem::P_RUN_POLICY).value<ComboProperty>();
    combo_property.setValue(run_policy);
    jobItem->setRegisteredProperty(NJobItem::P_RUN_POLICY, combo_property.getVariant());


//    if( jobItem->getRunPolicy() & (JobItem::RUN_IMMEDIATELY | JobItem::RUN_IN_BACKGROUND)  && jobItem->getStatus()!=JobItem::COMPLETED)
//        runJob(queue_item->getIdentifier());

    return jobItem;
}

void NJobModel::runJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::runJob(const QModelIndex &index)";
    Q_ASSERT(0);
    Q_UNUSED(index);
}

void NJobModel::cancelJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::cancelJob(const QModelIndex &index)";
    Q_ASSERT(0);
    Q_UNUSED(index);
}

void NJobModel::removeJob(const QModelIndex &index)
{
    qDebug() << "NJobModel::removeJob(const QModelIndex &index)";
    Q_ASSERT(0);
    Q_UNUSED(index);
}

void NJobModel::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    qDebug() << "NJobModel::onSelectionChanged" << selected;
    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        emit selectionChanged(getJobItemForIndex(indices.back()));
    } else {
        emit selectionChanged(0);
    }

//    if(!selected.empty() &&  !selected.first().indexes().empty()) {
//        QModelIndex index = selected.first().indexes().at(0);
//        emit selectionChanged(getJobItemForIndex(index));
//    }
}

//! generates job name
QString NJobModel::generateJobName()
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
QString NJobModel::generateJobIdentifier()
{
    return QUuid::createUuid().toString();
}

