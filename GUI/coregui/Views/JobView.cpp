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
#include "projectmanager.h"
#include "JobRealTimeWidget.h"
#include "projectmanager.h"
#include "mainwindow.h"
#include "progressbar.h"
#include "GUIHelpers.h"
#include "FitActivityPanel.h"
#include "JobMessagePanel.h"
#include "JobActivityStatusBar.h"
#include <QFrame>
#include <QDockWidget>
#include <QAbstractItemView>
#include <QStatusBar>
#include <QMenu>
#include <QCursor>
#include <QDebug>

class JobViewPrivate
{
public:
    JobViewPrivate(MainWindow *mainWindow);

    Manhattan::ProgressBar *progressBar() { return m_mainWindow->progressBar(); }
    JobModel *jobModel() { return m_mainWindow->jobModel(); }

    QVector<QWidget *> m_subWindows;
    QVector<QDockWidget *> m_dockWidgets;

    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputDataWidget;
    JobRealTimeWidget *m_jobRealTimeWidget;
    JobActivityStatusBar *m_jobActivityStatusBar;
    FitActivityPanel *m_fitActivityPanel;
    MainWindow *m_mainWindow;
};


JobViewPrivate::JobViewPrivate(MainWindow *mainWindow)
    : m_jobSelector(0)
    , m_jobOutputDataWidget(0)
    , m_jobRealTimeWidget(0)
    , m_jobActivityStatusBar(0)
    , m_fitActivityPanel(0)
    , m_mainWindow(mainWindow)
{
}


JobView::JobView(MainWindow *mainWindow)
    : m_d(new JobViewPrivate(mainWindow))
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

    m_d->m_jobActivityStatusBar = new JobActivityStatusBar;
    m_d->m_mainWindow->statusBar()->addWidget(m_d->m_jobActivityStatusBar, 1);
    m_d->m_mainWindow->statusBar()->setSizeGripEnabled(false);
    m_d->m_jobActivityStatusBar->hide();

    connectSignals();
}

JobView::~JobView()
{

}

QStringList JobView::getActivityStringList()
{
    QStringList result = QStringList() << QStringLiteral("Job View Activity")
        << QStringLiteral("Real Time Activity") << QStringLiteral("Fitting Activity");
    return result;
}

void JobView::updateGlobalProgressBar(int progress)
{
    Q_ASSERT(m_d->progressBar());
    if(progress<0 || progress >= 100) {
        m_d->progressBar()->setFinished(true);
        m_d->progressBar()->hide();
    } else {
        m_d->progressBar()->show();
        m_d->progressBar()->setFinished(false);
        m_d->progressBar()->setValue(progress);
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

    addDockWidget(Qt::LeftDockWidgetArea, m_d->m_dockWidgets[JOB_LIST_DOCK]);
    addDockWidget(Qt::RightDockWidgetArea, m_d->m_dockWidgets[REAL_TIME_DOCK]);
    addDockWidget(Qt::RightDockWidgetArea, m_d->m_dockWidgets[FIT_PANEL_DOCK]);
    addDockWidget(Qt::BottomDockWidgetArea, m_d->m_dockWidgets[JOB_MESSAGE_DOCK]);

    foreach (QDockWidget *dockWidget, dockWidgetList)
        dockWidget->show();

    setTrackingEnabled(true);

    setActivity(JOB_VIEW_ACTIVITY);
//    setActivity(FITTING_ACTIVITY);
}

void JobView::setActivity(int activity)
{
    if(activity == JOB_VIEW_ACTIVITY) {
        m_d->m_dockWidgets[JOB_LIST_DOCK]->show();
        m_d->m_dockWidgets[REAL_TIME_DOCK]->hide();
        m_d->m_dockWidgets[FIT_PANEL_DOCK]->hide();
        m_d->m_dockWidgets[JOB_MESSAGE_DOCK]->hide();
    }

    else if(activity == REAL_TIME_ACTIVITY) {
        m_d->m_dockWidgets[JOB_LIST_DOCK]->hide();
        m_d->m_dockWidgets[REAL_TIME_DOCK]->show();
        m_d->m_dockWidgets[FIT_PANEL_DOCK]->hide();
        m_d->m_dockWidgets[JOB_MESSAGE_DOCK]->hide();
        m_d->m_jobRealTimeWidget->updateCurrentItem();
    }

    else if(activity == FITTING_ACTIVITY) {
        m_d->m_dockWidgets[JOB_LIST_DOCK]->hide();
        m_d->m_dockWidgets[REAL_TIME_DOCK]->show();
        m_d->m_dockWidgets[FIT_PANEL_DOCK]->show();
        m_d->m_dockWidgets[JOB_MESSAGE_DOCK]->show();
        m_d->m_jobRealTimeWidget->updateCurrentItem();
        m_d->m_fitActivityPanel->updateCurrentItem();
    }

    else {
        throw GUIHelpers::Error("JobView::setActivity -> Error. Unknown activity");
    }

    emit activityChanged(activity);
}

void JobView::onToggleJobListRequest()
{
    m_d->m_dockWidgets[JOB_LIST_DOCK]->setHidden(!m_d->m_dockWidgets[JOB_LIST_DOCK]->isHidden());
}

//! creates global dock menu
void JobView::onDockMenuRequest()
{
    QMenu *menu = createPopupMenu();
    menu->exec(QCursor::pos());
    delete menu;
}

void JobView::showEvent(QShowEvent *)
{
    if(isVisible())
        m_d->m_jobActivityStatusBar->show();
}

void JobView::hideEvent(QHideEvent *)
{
    if(isHidden())
        m_d->m_jobActivityStatusBar->hide();
}

void JobView::initWindows()
{
    m_d->m_subWindows.resize(NUMBER_OF_DOCKS);
    m_d->m_dockWidgets.resize(NUMBER_OF_DOCKS);

    // central widget
    m_d->m_jobOutputDataWidget
        = new JobOutputDataWidget(m_d->jobModel(), this);
    setCentralWidget(m_d->m_jobOutputDataWidget);

    m_d->m_jobSelector = new JobSelectorWidget(m_d->jobModel(), this);
    m_d->m_subWindows[JOB_LIST_DOCK] = m_d->m_jobSelector;

    m_d->m_jobRealTimeWidget = new JobRealTimeWidget(m_d->jobModel(), this);
    m_d->m_subWindows[REAL_TIME_DOCK] = m_d->m_jobRealTimeWidget;

    m_d->m_fitActivityPanel = new FitActivityPanel(m_d->jobModel(), this);
    m_d->m_fitActivityPanel->setRealTimeWidget(m_d->m_jobRealTimeWidget);
    m_d->m_subWindows[FIT_PANEL_DOCK] = m_d->m_fitActivityPanel;

    m_d->m_subWindows[JOB_MESSAGE_DOCK] = new JobMessagePanel(this);
}

void JobView::connectSignals()
{
    Q_ASSERT(m_d->progressBar());
    Q_ASSERT(m_d->jobModel());
    connect(this, SIGNAL(resetLayout()), this, SLOT(resetToDefaultLayout()));
    connect(m_d->jobModel(), SIGNAL(globalProgress(int)),
            this, SLOT(updateGlobalProgressBar(int)));
    connect(m_d->jobModel(), SIGNAL(focusRequest(JobItem *)),
            this, SLOT(onFocusRequest(JobItem *)));
    connect(m_d->progressBar(), SIGNAL(clicked()),
            m_d->jobModel()->getJobQueueData(), SLOT(onCancelAllJobs()));

    // global statusBar notifies JobView about changes in the activity
    connect(m_d->m_jobActivityStatusBar, SIGNAL(changeActivityRequest(int)),
            this, SLOT(setActivity(int)));
    connect(m_d->m_jobActivityStatusBar, SIGNAL(toggleJobListRequest()),
            this, SLOT(onToggleJobListRequest()));
    connect(m_d->m_jobActivityStatusBar, SIGNAL(dockMenuRequest()),
            this, SLOT(onDockMenuRequest()));

    // JobView notifies others about changes in the activity
    connect(this, SIGNAL(activityChanged(int)),
            m_d->m_jobActivityStatusBar, SLOT(onActivityChanged(int)));
    connect(this, SIGNAL(activityChanged(int)),
            m_d->m_jobOutputDataWidget, SLOT(onActivityChanged(int)));
}
