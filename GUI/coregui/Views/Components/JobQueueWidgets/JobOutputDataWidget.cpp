// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/JobQueueWidgets/JobOutputDataWidget.cpp
//! @brief     Implements class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobOutputDataWidget.h"
//#include "JobQueueModel.h"
#include "NJobModel.h"
#include "NJobItem.h"
#include "OutputDataWidget.h"
#include "JobOutputDataToolBar.h"
#include "JobView.h"
#include "projectmanager.h"
#include "styledbar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QDebug>
#include "GUIHelpers.h"


JobOutputDataWidget::JobOutputDataWidget(NJobModel *jobModel, ProjectManager *projectManager, QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
    , m_projectManager(projectManager)
    , m_stack(new QStackedWidget(this))
    , m_toolBar(new JobOutputDataToolBar())
{
    setJobModel(jobModel);

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setWindowTitle(QLatin1String("Job OutputData"));
    setObjectName(QLatin1String("Job OutputData"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_stack);
    m_stack->setMinimumSize(600, 600);
    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setLayout(mainLayout);

    connectSignals();

}


//void JobOutputDataWidget::setJobQueueModel(JobQueueModel *jobQueueModel)
//{
//    Q_ASSERT(jobQueueModel);
//    if(jobQueueModel != m_jobQueueModel) {
//        m_jobQueueModel = jobQueueModel;

//        connect(m_jobQueueModel,
//            SIGNAL( selectionChanged(JobItem *) ),
//            this,
//            SLOT( itemClicked(JobItem *) )
//            );

//        connect(m_jobQueueModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
//                , this, SLOT(onJobItemFinished(QString)));

//        connect(m_jobQueueModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
//                , this, SLOT(onJobItemDelete(JobItem*)));
//    }
//}

void JobOutputDataWidget::setJobModel(NJobModel *jobModel)
{
    //FIXME
    return;

    Q_ASSERT(jobModel);
    if(jobModel != m_jobModel) {
        m_jobModel = jobModel;

        connect(m_jobModel,
            SIGNAL( selectionChanged(NJobItem *) ),
            this,
            SLOT( itemClicked(NJobItem *) )
            );

        connect(m_jobModel->getJobQueueData(), SIGNAL(jobIsFinished(QString))
                , this, SLOT(onJobItemFinished(QString)));

        connect(m_jobModel, SIGNAL(aboutToDeleteJobItem(NJobItem*))
                , this, SLOT(onJobItemDelete(NJobItem*)));
    }
}


void JobOutputDataWidget::itemClicked(NJobItem * item)
{
    qDebug() << "JobOutputDataWidget::itemClicked()";



    m_currentJobItem = item;

    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget && (item->isCompleted() || item->isCanceled())) {

        qDebug() << "JobOutputDataWidget::itemClicked() -> creating";
        widget = new OutputDataWidget(this, false, false, false);
        widget->setCurrentItem(item->getIntensityDataItem());
        widget->setProjectManager(m_projectManager);
        m_stack->addWidget(widget);
        m_jobItemToPlotWidget[item] = widget;

    }
    else
    {
        if( m_stack->currentWidget())
        {
            m_stack->currentWidget()->hide();
        }
    }


    if(widget)
    {
        qDebug() << "JobOutputDataWidget::itemClicked() -> setCurrentWidget";

        if(widget->isHidden())
        {
            widget->show();
        }

        m_stack->setCurrentWidget(widget);
    }
}


void JobOutputDataWidget::onJobItemFinished(const QString &identifier)
{
    qDebug() << "JobOutputDataWidget::onJobItemFinished";
    Q_ASSERT(0);
    Q_UNUSED(identifier);

//    qDebug() << "JobOutputDataWidget::onJobItemFinished()";
//    NJobItem *jobItem = m_jobModel->getJobQueueData()->getJobItem(identifier);

//    if(jobItem == m_currentJobItem)
//    {
//        if((jobItem->isCompleted() || jobItem->isCanceled()) && jobItem->getIntensityDataItem())
//        {
//            qDebug() << "JobOutputDataWidget::dataChanged() JobItem::Completed";
//            itemClicked(jobItem);
//        }
//    }
}


void JobOutputDataWidget::togglePropertyPanel()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->togglePropertyPanel();
}


void JobOutputDataWidget::toggleProjections()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->toggleProjections();
}


void JobOutputDataWidget::resetTriggered()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->resetTriggered();
}


void JobOutputDataWidget::savePlot()
{
    OutputDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->savePlot();
}


void JobOutputDataWidget::onActivityChanged(int activity)
{
    m_toolBar->onActivityChanged(activity);
    if(activity == JobView::REAL_TIME_ACTIVITY) {
        OutputDataWidget *widget = getCurrentOutputDataWidget();
        if(widget) {
            widget->setPropertyPanelVisible(false);
            //widget->setProjectionsVisible(false);
        }
    }
}


void JobOutputDataWidget::connectSignals()
{
    connect(m_toolBar, SIGNAL(jobViewActivityRequest(int)), this, SIGNAL(jobViewActivityRequest(int)));
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(resetTriggered()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(savePlot()));
}


OutputDataWidget *JobOutputDataWidget::getCurrentOutputDataWidget()
{
    OutputDataWidget *result = dynamic_cast<OutputDataWidget *>(m_stack->currentWidget());
    if(result && result->isHidden()) result = 0;
    return result;
}


void JobOutputDataWidget::onJobItemDelete(NJobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget ) {
        // this is the case when user removes failed job which doesn't have propper widget
        //throw GUIHelpers::Error("JobOutputDataWidget::onJobItemDelete -> Can't find widget");
        return;
    }

    QMap<NJobItem *, OutputDataWidget *>::iterator it = m_jobItemToPlotWidget.begin();
    while(it!=m_jobItemToPlotWidget.end()) {
        if(it.value() == widget) {
            it = m_jobItemToPlotWidget.erase(it);
        } else {
            ++it;
        }
    }

    m_stack->removeWidget(widget);
    delete widget;
}

