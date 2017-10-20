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
    , m_currentItem(nullptr)
    , m_mainWindow(mainWindow)
{
    setObjectName("JobView");
    m_docks->initViews(mainWindow->jobModel());

    connectSignals();
}

void JobView::onFocusRequest(JobItem* jobItem)
{
    if (jobItem->runInBackground())
        return;

    m_docks->jobSelector()->makeJobItemSelected(jobItem);
    setAppropriateActivityForJob(jobItem);

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
    std::unique_ptr<QMenu> menu(createPopupMenu());
    menu->exec(QCursor::pos());
}

//! Propagates change in JobItem's selection down into main widgets.

void JobView::onSelectionChanged(JobItem* jobItem) {
    m_docks->setItem(jobItem);
}

void JobView::showEvent(QShowEvent*)
{
    if (isVisible())
        m_jobActivityStatusBar->show();
}

void JobView::hideEvent(QHideEvent*)
{
    if (isHidden())
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
    connect(m_jobActivityStatusBar, &JobActivityStatusBar::changeActivityRequest,
            this, &JobView::setActivity);

    // Activity was changed: this -> JobActivityStatusBar
    connect(this, &JobView::activityChanged,
            m_jobActivityStatusBar, &JobActivityStatusBar::onActivityChanged);

    // Activity was changed: this -> JobOutputDataWidget
    connect(this, &JobView::activityChanged,
            m_docks->jobOutputDataWidget(), &JobOutputDataWidget::onActivityChanged);
}

//! Connects signals related to dock layout.

void JobView::connectLayoutRelated()
{
    connect(this, &JobView::resetLayout, m_docks, &JobViewDocks::onResetLayout);

    // Toggling of JobSelector request: JobActivityStatusBar -> this
    connect(m_jobActivityStatusBar, &JobActivityStatusBar::toggleJobSelectorRequest,
            m_docks, &JobViewDocks::onToggleJobSelector);

    // Dock menu request: JobActivityStatusBar -> this
    connect(m_jobActivityStatusBar, &JobActivityStatusBar::dockMenuRequest,
            this, &JobView::onDockMenuRequest);
}

//! Connects signals related to JobItem

void JobView::connectJobRelated()
{
    // Focus request: JobModel -> this
    connect(m_mainWindow->jobModel(), &JobModel::focusRequest, this, &JobView::onFocusRequest);

    // JobItem selection: JobSelectorWidget -> this
    connect(m_docks->jobSelector(), &JobSelectorWidget::selectionChanged,
            this, &JobView::onSelectionChanged);
}

//! Sets appropriate activity for new JobItem

void JobView::setAppropriateActivityForJob(JobItem* jobItem)
{
    if (!jobItem) return;

    if (jobItem->isValidForFitting())
        setActivity(JobViewFlags::FITTING_ACTIVITY);
    else
        setActivity(JobViewFlags::JOB_VIEW_ACTIVITY);
}
