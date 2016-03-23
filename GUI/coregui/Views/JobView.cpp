// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobView.cpp
//! @brief     Implements class JobView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobView.h"
#include "JobQueueData.h"
#include "TestView.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "JobModel.h"
#include "JobRealTimeWidget.h"
#include "projectmanager.h"
#include "mainwindow.h"
#include "progressbar.h"
#include <QFrame>
#include <QDockWidget>
#include <QAbstractItemView>

struct JobViewPrivate
{
    JobViewPrivate(JobModel *jobModel, ProjectManager *projectManager);
    QWidget *m_subWindows[JobView::NUMBER_OF_DOCKS];
    QDockWidget *m_dockWidgets[JobView::NUMBER_OF_DOCKS];
    JobModel *m_jobModel;
    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputDataWidget;
    JobRealTimeWidget *m_jobRealTimeWidget;
    Manhattan::ProgressBar *m_progressBar; //!< general progress bar
    ProjectManager *m_projectManager;
};


JobViewPrivate::JobViewPrivate(JobModel *jobModel, ProjectManager *projectManager)
    : m_jobModel(jobModel)
    , m_jobSelector(0)
    , m_jobOutputDataWidget(0)
    , m_jobRealTimeWidget(0)
    , m_progressBar(0)
    , m_projectManager(projectManager)
{
    qFill(m_subWindows, m_subWindows + JobView::NUMBER_OF_DOCKS,
          static_cast<QWidget*>(0));
    qFill(m_dockWidgets, m_dockWidgets + JobView::NUMBER_OF_DOCKS,
          static_cast<QDockWidget*>(0));
}


JobView::JobView(JobModel *jobModel, ProjectManager *projectManager, QWidget *parent)
    : Manhattan::FancyMainWindow(parent)
    , m_d(new JobViewPrivate(jobModel, projectManager))
{
    setObjectName("JobView");

    initWindows();

    setDocumentMode(true);
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::South);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    for (int i = 0; i < NUMBER_OF_DOCKS; i++) {
        QWidget *subWindow = m_d->m_subWindows[i];
        m_d->m_dockWidgets[i] = addDockForWidget(subWindow);

        // Since we have 1-pixel splitters, we generally want to remove
        // frames around item views. So we apply this hack for now.
        QList<QAbstractItemView*> frames =
                subWindow->findChildren<QAbstractItemView*>();
        for (int i = 0 ; i< frames.count(); ++i)
            frames[i]->setFrameStyle(QFrame::NoFrame);

    }

    resetToDefaultLayout();

    connectSignals();
}

JobView::~JobView()
{
    delete m_d;
}

void JobView::setProgressBar(Manhattan::ProgressBar *progressBar)
{
    if(m_d->m_progressBar != progressBar) {
        m_d->m_progressBar = progressBar;
        m_d->m_progressBar->hide();
        connect(m_d->m_progressBar, SIGNAL(clicked()), m_d->m_jobModel->getJobQueueData(), SLOT(onCancelAllJobs()));
    }
}

void JobView::updateGlobalProgressBar(int progress)
{
    Q_ASSERT(m_d->m_progressBar);
    if(progress<0 || progress >= 100) {
        m_d->m_progressBar->setFinished(true);
        m_d->m_progressBar->hide();
    } else {
        m_d->m_progressBar->show();
        m_d->m_progressBar->setFinished(false);
        m_d->m_progressBar->setValue(progress);
    }
}

void JobView::onFocusRequest(JobItem *item)
{
    m_d->m_jobSelector->makeJobItemSelected(item);
    emit focusRequest(MainWindow::JOB);
}

void JobView::resetToDefaultLayout()
{
    setTrackingEnabled(false);
    QList<QDockWidget *> dockWidgetList = dockWidgets();
    foreach (QDockWidget *dockWidget, dockWidgetList) {
        dockWidget->setFloating(false);
        removeDockWidget(dockWidget);
    }

    addDockWidget(Qt::LeftDockWidgetArea,
                  m_d->m_dockWidgets[JOB_LIST_DOCK]);
    addDockWidget(Qt::RightDockWidgetArea,
                  m_d->m_dockWidgets[REAL_TIME_DOCK]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);

    setActivity(JOB_VIEW_ACTIVITY);
}

void JobView::setActivity(int activity)
{
    if(activity == JOB_VIEW_ACTIVITY) {
        m_d->m_dockWidgets[JOB_LIST_DOCK]->show();
        m_d->m_dockWidgets[REAL_TIME_DOCK]->hide();
        emit activityChanged(activity);
    } else if(activity == REAL_TIME_ACTIVITY) {
        m_d->m_dockWidgets[JOB_LIST_DOCK]->hide();
        m_d->m_dockWidgets[REAL_TIME_DOCK]->show();
        m_d->m_jobRealTimeWidget->updateCurrentItem();
        emit activityChanged(activity);
    }
}

void JobView::initWindows()
{
    // central widget
    m_d->m_jobOutputDataWidget = new JobOutputDataWidget(m_d->m_jobModel, m_d->m_projectManager, this);
    setCentralWidget(m_d->m_jobOutputDataWidget);

    m_d->m_jobSelector = new JobSelectorWidget(m_d->m_jobModel, this);
    m_d->m_subWindows[JOB_LIST_DOCK] = m_d->m_jobSelector;

    m_d->m_jobRealTimeWidget = new JobRealTimeWidget(m_d->m_jobModel, this);
    m_d->m_subWindows[REAL_TIME_DOCK] = m_d->m_jobRealTimeWidget;
}

void JobView::connectSignals()
{
    connect(this, SIGNAL(resetLayout()), this, SLOT(resetToDefaultLayout()));
    connect(m_d->m_jobModel, SIGNAL(globalProgress(int)), this, SLOT(updateGlobalProgressBar(int)));
    connect(m_d->m_jobModel, SIGNAL(focusRequest(JobItem*)), this, SLOT(onFocusRequest(JobItem*)));
    connect(m_d->m_jobOutputDataWidget, SIGNAL(jobViewActivityRequest(int)), this, SLOT(setActivity(int)));
    connect(this, SIGNAL(activityChanged(int)),  m_d->m_jobOutputDataWidget, SLOT(onActivityChanged(int)));
}
