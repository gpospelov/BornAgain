// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobOutputDataWidget.cpp
//! @brief     Implements class JobOutputDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobOutputDataWidget.h"
#include "JobModel.h"
#include "JobItem.h"
#include "IntensityDataWidget.h"
#include "JobOutputDataToolBar.h"
#include "JobView.h"
#include "JobViewActivities.h"
#include "AppSvc.h"
#include "projectmanager.h"
#include "JobViewFlags.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QStandardPaths>
#include <QDebug>
#include "GUIHelpers.h"

JobOutputDataWidget::JobOutputDataWidget(JobModel *jobModel, QWidget *parent)
    : JobPresenter(jobModel, parent)
    , m_stack(new QStackedWidget(this))
    , m_toolBar(new JobOutputDataToolBar())
{
    setWindowTitle(QLatin1String("Job OutputData"));

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

//void JobOutputDataWidget::setJobModel(JobModel *jobModel)
//{
//    Q_ASSERT(jobModel);

//    if(jobModel != m_jobModel) {

//        if(m_jobModel) {
//            disconnect(m_jobModel,
//                SIGNAL( selectionChanged(JobItem *) ),
//                this,
//                SLOT( setItem(JobItem *) )
//                );

//            disconnect(m_jobModel, SIGNAL(focusRequest(JobItem*)), this, SLOT(setItem(JobItem*)));
//        }

//        m_jobModel = jobModel;

//        connect(m_jobModel,
//            SIGNAL( selectionChanged(JobItem *) ),
//            this,
//            SLOT( setItem(JobItem *) )
//            );

//        connect(m_jobModel, SIGNAL(aboutToDeleteJobItem(JobItem*))
//                , this, SLOT(onJobItemDelete(JobItem*)));
//        connect(m_jobModel, SIGNAL(focusRequest(JobItem*)), this, SLOT(setItem(JobItem*)));
//    }
//}


void JobOutputDataWidget::setItem(JobItem * item)
{
    //qDebug() << "JobOutputDataWidget::setItem()" << item;
    if(!item) return;

    m_currentItem = item;

    IntensityDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget && (item->isCompleted() || item->isCanceled())) {

        widget = new IntensityDataWidget(this);
        connect(widget, SIGNAL(savePlotRequest()), this, SLOT(onSavePlot()));
        widget->setItem(item->getIntensityDataItem());
        m_stack->addWidget(widget);
        m_jobItemToPlotWidget[item] = widget;

    } else {
        if( m_stack->currentWidget() && m_stack->currentWidget() != widget) {
            m_stack->currentWidget()->hide();
        }
    }

    if(widget) {
        qDebug() << "JobOutputDataWidget::itemClicked() -> setCurrentWidget";

        if(widget->isHidden()) {
            widget->show();
        }

        m_stack->setCurrentWidget(widget);
    }
}

void JobOutputDataWidget::togglePropertyPanel()
{
    IntensityDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->togglePropertyPanel();
}

void JobOutputDataWidget::toggleProjections()
{
    IntensityDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->toggleProjections();
}

void JobOutputDataWidget::onResetView()
{
    IntensityDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->onResetView();
}

void JobOutputDataWidget::onSavePlot()
{
    IntensityDataWidget *widget = getCurrentOutputDataWidget();
    if(widget) widget->savePlot(AppSvc::projectManager()->userExportDir());
}

void JobOutputDataWidget::onActivityChanged(int activity)
{
    if(activity == JobViewFlags::REAL_TIME_ACTIVITY) {
        IntensityDataWidget *widget = getCurrentOutputDataWidget();
        if(widget) {
            widget->setPropertyPanelVisible(false);
        }
    }
}

void JobOutputDataWidget::connectSignals()
{
    connect(m_toolBar, SIGNAL(togglePropertyPanel()), this, SLOT(togglePropertyPanel()));
    connect(m_toolBar, SIGNAL(toggleProjections()), this, SLOT(toggleProjections()));
    connect(m_toolBar, SIGNAL(resetView()), this, SLOT(onResetView()));
    connect(m_toolBar, SIGNAL(savePlot()), this, SLOT(onSavePlot()));
}

IntensityDataWidget *JobOutputDataWidget::getCurrentOutputDataWidget()
{
    IntensityDataWidget *result = dynamic_cast<IntensityDataWidget *>(m_stack->currentWidget());
    if(result && result->isHidden()) result = 0;
    return result;
}

void JobOutputDataWidget::onJobItemDelete(JobItem *item)
{
    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
    IntensityDataWidget *widget = m_jobItemToPlotWidget[item];
    if( !widget ) {
        // this is the case when user removes failed job which doesn't have propper widget
        //throw GUIHelpers::Error("JobOutputDataWidget::onJobItemDelete -> Can't find widget");
        return;
    }

    QMap<JobItem *, IntensityDataWidget *>::iterator it = m_jobItemToPlotWidget.begin();
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

