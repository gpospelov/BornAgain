// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobView.cpp
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
#include "JobActivityStatusBar.h"
#include "JobItem.h"
#include "JobModel.h"
#include "JobOutputDataWidget.h"
#include "JobProgressAssistant.h"
#include "JobSelectorWidget.h"
#include "JobViewDocks.h"
#include "mainwindow.h"
#include <QMenu>

JobView::JobView(MainWindow *mainWindow)
    : m_docks(new JobViewDocks(this))
    , m_jobActivityStatusBar(new JobActivityStatusBar(mainWindow))
    , m_progressAssistant(new JobProgressAssistant(mainWindow))
    , m_currentItem(0)
    , m_mainWindow(mainWindow)
{
    setObjectName("JobView");
    m_docks->initViews(mainWindow->jobModel());

    connectSignals();
}

void JobView::onFocusRequest(JobItem *jobItem)
{
    if(jobItem->runInBackground())
        return;

    setAppropriateActivityForJob(jobItem);
    m_docks->jobSelector()->makeJobItemSelected(jobItem);

    emit focusRequest(MainWindow::JOB);
}

//! Sets docks visibility in accordance with required activity.

void JobView::setActivity(int activity)
{
    m_docks->setActivity(activity);
    emit activityChanged(activity);
}

//! Creates global dock menu at cursor position.

void JobView::onDockMenuRequest()
{
    QMenu *menu = createPopupMenu();
    menu->exec(QCursor::pos());
    delete menu;
}

//! Propagates change in JobItem's selection down into main widgets.

void JobView::onSelectionChanged(JobItem *jobItem)
{
    m_docks->setItem(jobItem);
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
    connectActivityRelated();
    connectLayoutRelated();
    connectJobRelated();
}

//! Connects signal related to activity change.

void JobView::connectActivityRelated()
{
    // Change activity requests: JobActivityStatusBar -> this
    connect(m_jobActivityStatusBar, SIGNAL(changeActivityRequest(int)),
            this, SLOT(setActivity(int)));

    // Activity was changed: this -> JobActivityStatusBar
    connect(this, SIGNAL(activityChanged(int)),
            m_jobActivityStatusBar, SLOT(onActivityChanged(int)));

    // Activity was changed: this -> JobOutputDataWidget
    connect(this, SIGNAL(activityChanged(int)),
            m_docks->jobOutputDataWidget(), SLOT(onActivityChanged(int)));

}

//! Connects signals related to dock layout.

void JobView::connectLayoutRelated()
{
    connect(this, SIGNAL(resetLayout()), m_docks, SLOT(onResetLayout()));

    // Toggling of JobSelector request: JobActivityStatusBar -> this
    connect(m_jobActivityStatusBar, SIGNAL(toggleJobSelectorRequest()),
            m_docks, SLOT(onToggleJobSelector()));

    // Dock menu request: JobActivityStatusBar -> this
    connect(m_jobActivityStatusBar, SIGNAL(dockMenuRequest()),
            this, SLOT(onDockMenuRequest()));
}

//! Connects signals related to JobItem

void JobView::connectJobRelated()
{
    // Focus request: JobModel -> this
    connect(m_mainWindow->jobModel(), SIGNAL(focusRequest(JobItem *)),
            this, SLOT(onFocusRequest(JobItem *)));

    // JobItem selection: JobSelectorWidget -> this
    connect(m_docks->jobSelector(), SIGNAL(selectionChanged(JobItem*)),
            this, SLOT(onSelectionChanged(JobItem*)));

}

//! Sets appropriate activity for new JobItem

void JobView::setAppropriateActivityForJob(JobItem *jobItem)
{
    if(m_docks->jobSelector()->currentJobItem() != jobItem) {
        if(jobItem->isValidForFitting())
            setActivity(JobViewFlags::FITTING_ACTIVITY);
//        else
//            setActivity(JobViewFlags::JOB_VIEW_ACTIVITY);
    }
}
