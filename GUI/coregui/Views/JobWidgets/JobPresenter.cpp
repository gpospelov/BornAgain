// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobPresenter.cpp
//! @brief     Implements class JobPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobPresenter.h"
#include "JobModel.h"
#include "JobItem.h"
#include "JobQueueData.h"

JobPresenter::JobPresenter(JobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_currentItem(0)
{
    setJobModel(jobModel);
}

void JobPresenter::setJobModel(JobModel *jobModel)
{
    Q_UNUSED(jobModel);
//    if(jobModel != m_jobModel) {
//        if(m_jobModel) {
//            disconnect(m_jobModel, SIGNAL(selectionChanged(JobItem *)),
//                       this, SLOT(setItem(JobItem *)));

//            disconnect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)),
//                       this, SLOT(onJobItemFinished(QString)));

//            disconnect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*)),
//                       this, SLOT(onJobItemDelete(JobItem*)));

//            disconnect(m_jobModel, SIGNAL(modelLoaded()),
//                       this, SLOT(onModelLoaded()));
//        }

//        m_jobModel = jobModel;

//        if(m_jobModel) {
//            connect(m_jobModel, SIGNAL(selectionChanged(JobItem *)),
//                    this, SLOT(setItem(JobItem *)), Qt::UniqueConnection);

//            connect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString)),
//                    this, SLOT(onJobItemFinished(QString)), Qt::UniqueConnection);

//            connect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*)),
//                    this, SLOT(onJobItemDelete(JobItem*)), Qt::UniqueConnection);

//            connect(m_jobModel, SIGNAL(modelLoaded()), this,
//                    SLOT(onModelLoaded()), Qt::UniqueConnection);
//        }

//    }
}

void JobPresenter::setItem(JobItem *item)
{
    m_currentItem = item;
}

void JobPresenter::onJobItemDelete(JobItem *item)
{
    if(m_currentItem == item)
        m_currentItem = 0;
}

void JobPresenter::onJobItemFinished(const QString &identifier)
{
    Q_UNUSED(identifier);
}

void JobPresenter::updateCurrentItem()
{

}

void JobPresenter::onActivityChange(int nactivity)
{
    Q_UNUSED(nactivity);
}

void JobPresenter::onModelLoaded()
{

}

bool JobPresenter::isValidJobItem(JobItem *item)
{
    Q_UNUSED(item);
    return true;
}
