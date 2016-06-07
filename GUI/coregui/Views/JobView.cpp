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
#include "JobViewDocks.h"
#include "JobQueueData.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"
#include "JobModel.h"
#include "mainwindow.h"
#include "progressbar.h"
#include "JobActivityStatusBar.h"
#include <QMenu>
#include <QCursor>
#include <QDebug>


JobView::JobView(MainWindow *mainWindow)
    : m_docks(new JobViewDocks(this))
    , m_jobActivityStatusBar(new JobActivityStatusBar(mainWindow))
    , m_mainWindow(mainWindow)
{
    setObjectName("JobView");
    m_docks->initViews(mainWindow->jobModel());

    connectSignals();
}

void JobView::updateGlobalProgressBar(int progress)
{
    Q_ASSERT(m_mainWindow->progressBar());
    if(progress<0 || progress >= 100) {
        m_mainWindow->progressBar()->setFinished(true);
        m_mainWindow->progressBar()->hide();
    } else {
        m_mainWindow->progressBar()->show();
        m_mainWindow->progressBar()->setFinished(false);
        m_mainWindow->progressBar()->setValue(progress);
    }
}

void JobView::onFocusRequest(JobItem *item)
{
    m_docks->jobSelector()->makeJobItemSelected(item);
    emit focusRequest(MainWindow::JOB);
}

void JobView::setActivity(int activity)
{
    m_docks->setActivity(activity);
    emit activityChanged(activity);
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
        m_jobActivityStatusBar->show();
}

void JobView::hideEvent(QHideEvent *)
{
    if(isHidden())
        m_jobActivityStatusBar->hide();
}


void JobView::connectSignals()
{
    Q_ASSERT(m_mainWindow->progressBar());
    Q_ASSERT(m_mainWindow->jobModel());

    connect(this, SIGNAL(resetLayout()), m_docks, SLOT(onResetLayout()));
    connect(m_jobActivityStatusBar, SIGNAL(toggleJobSelectorRequest()),
            m_docks, SLOT(onToggleJobSelector()));

    connect(m_mainWindow->jobModel(), SIGNAL(globalProgress(int)),
            this, SLOT(updateGlobalProgressBar(int)));
    connect(m_mainWindow->jobModel(), SIGNAL(focusRequest(JobItem *)),
            this, SLOT(onFocusRequest(JobItem *)));
    connect(m_mainWindow->progressBar(), SIGNAL(clicked()),
            m_mainWindow->jobModel()->getJobQueueData(), SLOT(onCancelAllJobs()));

    // global statusBar notifies JobView about changes in the activity
    connect(m_jobActivityStatusBar, SIGNAL(changeActivityRequest(int)),
            this, SLOT(setActivity(int)));

    connect(m_jobActivityStatusBar, SIGNAL(dockMenuRequest()),
            this, SLOT(onDockMenuRequest()));

    // JobView notifies others about changes in the activity
    connect(this, SIGNAL(activityChanged(int)),
            m_jobActivityStatusBar, SLOT(onActivityChanged(int)));
    connect(this, SIGNAL(activityChanged(int)),
            m_docks->jobOutputDataWidget(), SLOT(onActivityChanged(int)));
}
