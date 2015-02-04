// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobRealTimeWidget.cpp
//! @brief     Implements class JobRealTimeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobRealTimeWidget.h"
//#include "JobQueueModel.h"
#include "NJobModel.h"
#include "NJobItem.h"
#include "ModelTuningWidget.h"
#include "JobRealTimeToolBar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include "GUIHelpers.h"


JobRealTimeWidget::JobRealTimeWidget(NJobModel *jobModel, QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_currentJobItem(0)
    , m_stack(new QStackedWidget(this))
    , m_toolBar(new JobRealTimeToolBar)
{
    setJobModel(jobModel);

    setMinimumSize(100, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setWindowTitle(QLatin1String("Job Real Time"));
    setObjectName(QLatin1String("Job Real Time"));

    m_stack->setMinimumSize(100, 400);
    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stack);

    setLayout(mainLayout);

    connect(m_toolBar, SIGNAL(resetParameters()), this, SLOT(onResetParameters()));
    //connect(m_toolBar, SIGNAL(exportParameters()), this, SLOT(onExportParameters()));
}


void JobRealTimeWidget::setJobModel(NJobModel *jobModel)
{
    Q_ASSERT(jobModel);
    if(jobModel != m_jobModel) {
        if(m_jobModel) {
            disconnect(m_jobModel,
                SIGNAL( selectionChanged(NJobItem *) ),
                this,
                SLOT( itemClicked(NJobItem *) )
                );

            disconnect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                    , this, SLOT(onJobItemFinished(QString)));

            disconnect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                    , this, SLOT(onJobItemDelete(JobItem*)));
        }

        m_jobModel = jobModel;

        connect(m_jobModel,
            SIGNAL( selectionChanged(NJobItem *) ),
            this,
            SLOT( itemClicked(NJobItem *) )
            );

        connect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                , this, SLOT(onJobItemFinished(QString)));

        connect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                , this, SLOT(onJobItemDelete(JobItem*)));
    }
}


void JobRealTimeWidget::itemClicked(NJobItem * item)
{
    qDebug() << "JobOutputDataWidget::itemClicked()";
    m_currentJobItem = item;

    if(!isVisible()) return;

    ModelTuningWidget *widget = m_jobItemToTuningWidget[item];
    if( !widget && isValidJobItem(item)) {

        qDebug() << "JobOutputDataWidget::itemClicked() -> creating";
        widget = new ModelTuningWidget(m_jobModel->getJobQueueData());
        widget->setCurrentItem(item);
        m_stack->addWidget(widget);
        m_jobItemToTuningWidget[item] = widget;

    } else {
        if( m_stack->currentWidget()) {
            m_stack->currentWidget()->hide();
        }
    }

    if(widget) {
        if(widget->isHidden()) {
            widget->show();
        }

        m_stack->setCurrentWidget(widget);
    }
}


void JobRealTimeWidget::onJobItemFinished(const QString &/*identifier*/)
{
    Q_ASSERT(0);
    // FIXME
//    qDebug() << "JobOutputDataWidget::onJobItemFinished()";
//    NJobItem *jobItem = m_jobModel->getJobQueueData()->getJobItem(identifier);

//    if(jobItem == m_currentJobItem) {
//        if((jobItem->getStatus() == JobItem::COMPLETED || jobItem->getStatus() == JobItem::CANCELLED) && jobItem->getOutputDataItem()) {
//            qDebug() << "JobOutputDataWidget::dataChanged() JobItem::Completed";
//            itemClicked(jobItem);
//        }
//    }
}

void JobRealTimeWidget::onResetParameters()
{
    ModelTuningWidget *widget = getCurrentModelTuningWidget();
    if(widget)
        widget->restoreModelsOfCurrentJobItem();
}

void JobRealTimeWidget::updateCurrentItem()
{
    if(!m_currentJobItem) return;
    itemClicked(m_currentJobItem);
}

//void JobRealTimeWidget::onExportParameters()
//{

//}


ModelTuningWidget *JobRealTimeWidget::getCurrentModelTuningWidget()
{
    ModelTuningWidget *result = dynamic_cast<ModelTuningWidget *>(m_stack->currentWidget());
    if(result && result->isHidden()) result = 0;
    return result;
}

//! Returns true if JobItem is valid for real time simulation, i.e.
//! it is not already running and it has valid models
bool JobRealTimeWidget::isValidJobItem(NJobItem *item)
{
 return (item->isCompleted() || item->isCanceled()) && item->getSampleModel() && item->getInstrumentModel();
}


void JobRealTimeWidget::onJobItemDelete(NJobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    ModelTuningWidget *widget = m_jobItemToTuningWidget[item];
    if( !widget ) {
        // this is the case when user removes failed job which doesn't have propper widget
        return;
    }

    QMap<NJobItem *, ModelTuningWidget *>::iterator it = m_jobItemToTuningWidget.begin();
    while(it!=m_jobItemToTuningWidget.end()) {
        if(it.value() == widget) {
            it = m_jobItemToTuningWidget.erase(it);
        } else {
            ++it;
        }
    }

    m_stack->removeWidget(widget);
    delete widget;
}

