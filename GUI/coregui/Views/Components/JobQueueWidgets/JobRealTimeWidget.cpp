// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobRealTimeWidget.cpp
//! @brief     Implements class JobRealTimeWidget
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobRealTimeWidget.h"
#include "JobQueueModel.h"
#include "ModelTuningWidget.h"
#include "JobRealTimeToolBar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include "GUIHelpers.h"


JobRealTimeWidget::JobRealTimeWidget(JobQueueModel *jobQueueModel, QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(0)
    , m_currentJobItem(0)
    , m_stack(new QStackedWidget(this))
    , m_toolBar(new JobRealTimeToolBar)
{
    setJobQueueModel(jobQueueModel);

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


void JobRealTimeWidget::setJobQueueModel(JobQueueModel *jobQueueModel)
{
    Q_ASSERT(jobQueueModel);
    if(jobQueueModel != m_jobQueueModel) {
        if(m_jobQueueModel) {
            disconnect(m_jobQueueModel,
                SIGNAL( selectionChanged(JobItem *) ),
                this,
                SLOT( itemClicked(JobItem *) )
                );

            disconnect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                    , this, SLOT(onJobItemFinished(QString)));

            disconnect(m_jobQueueModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                    , this, SLOT(onJobItemDelete(JobItem*)));
        }

        m_jobQueueModel = jobQueueModel;

        connect(m_jobQueueModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( itemClicked(JobItem *) )
            );

        connect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                , this, SLOT(onJobItemFinished(QString)));

        connect(m_jobQueueModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
                , this, SLOT(onJobItemDelete(JobItem*)));
    }
}


void JobRealTimeWidget::itemClicked(JobItem * item)
{
    qDebug() << "JobOutputDataWidget::itemClicked()";
    m_currentJobItem = item;

    if(!isVisible()) return;

    ModelTuningWidget *widget = m_jobItemToTuningWidget[item];
    if( !widget && isValidJobItem(item)) {

        qDebug() << "JobOutputDataWidget::itemClicked() -> creating";
        widget = new ModelTuningWidget(m_jobQueueModel->getJobQueueData());
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


void JobRealTimeWidget::onJobItemFinished(const QString &identifier)
{
    qDebug() << "JobOutputDataWidget::onJobItemFinished()";
    JobItem *jobItem = m_jobQueueModel->getJobQueueData()->getJobItem(identifier);

    if(jobItem == m_currentJobItem) {
        if((jobItem->getStatus() == JobItem::COMPLETED || jobItem->getStatus() == JobItem::CANCELLED) && jobItem->getOutputDataItem()) {
            qDebug() << "JobOutputDataWidget::dataChanged() JobItem::Completed";
            itemClicked(jobItem);
        }
    }
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
bool JobRealTimeWidget::isValidJobItem(JobItem *item)
{
 return (item->getStatus() == JobItem::COMPLETED || item->getStatus() == JobItem::CANCELLED) && item->getSampleModel() && item->getInstrumentModel();
}


void JobRealTimeWidget::onJobItemDelete(JobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    ModelTuningWidget *widget = m_jobItemToTuningWidget[item];
    if( !widget ) {
        // this is the case when user removes failed job which doesn't have propper widget
        return;
    }

    QMap<JobItem *, ModelTuningWidget *>::iterator it = m_jobItemToTuningWidget.begin();
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

