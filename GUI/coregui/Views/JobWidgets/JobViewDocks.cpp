// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewDocks.cpp
//! @brief     Implements class JobViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "JobViewDocks.h"
#include "FitActivityPanel.h"
#include "JobMessagePanel.h"
#include "JobModel.h"
#include "JobOutputDataWidget.h"
#include "JobRealTimeWidget.h"
#include "JobSelectorWidget.h"
#include "JobView.h"
#include "JobViewActivities.h"
#include "JobViewFlags.h"
#include <QDockWidget>

namespace
{
const JobViewFlags::Activity default_activity = JobViewFlags::JOB_VIEW_ACTIVITY;
}

JobViewDocks::JobViewDocks(JobView* parent)
    : DocksController(parent), m_jobSelector(nullptr), m_jobOutputDataWidget(nullptr),
      m_jobRealTimeWidget(nullptr), m_fitActivityPanel(nullptr), m_jobMessagePanel(nullptr),
      m_jobView(parent)
{
}

void JobViewDocks::initViews(JobModel* jobModel)
{
    m_jobOutputDataWidget = new JobOutputDataWidget(jobModel, m_jobView);

    m_jobSelector = new JobSelectorWidget(jobModel, m_jobView);
    addWidget(JobViewFlags::JOB_LIST_DOCK, m_jobSelector, Qt::LeftDockWidgetArea);

    m_jobRealTimeWidget = new JobRealTimeWidget(jobModel, m_jobView);
    addWidget(JobViewFlags::REAL_TIME_DOCK, m_jobRealTimeWidget, Qt::RightDockWidgetArea);

    m_fitActivityPanel = new FitActivityPanel(jobModel, m_jobView);
    addWidget(JobViewFlags::FIT_PANEL_DOCK, m_fitActivityPanel, Qt::RightDockWidgetArea);

    m_jobMessagePanel = new JobMessagePanel(m_jobView);
    connect(m_jobMessagePanel, &JobMessagePanel::widgetHeightRequest, this,
            &DocksController::setDockHeightForWidget);
    connect(m_jobMessagePanel, &JobMessagePanel::widgetCloseRequest, this,
            &JobViewDocks::onWidgetCloseRequest);

    addWidget(JobViewFlags::JOB_MESSAGE_DOCK, m_jobMessagePanel, Qt::BottomDockWidgetArea);

    m_fitActivityPanel->setRealTimeWidget(m_jobRealTimeWidget);
    m_fitActivityPanel->setJobMessagePanel(m_jobMessagePanel);

    m_jobView->setCentralWidget(m_jobOutputDataWidget);

    onResetLayout();
}

JobRealTimeWidget* JobViewDocks::jobRealTimeWidget()
{
    return m_jobRealTimeWidget;
}

FitActivityPanel* JobViewDocks::fitActivityPanel()
{
    return m_fitActivityPanel;
}

JobSelectorWidget* JobViewDocks::jobSelector()
{
    return m_jobSelector;
}

JobOutputDataWidget* JobViewDocks::jobOutputDataWidget()
{
    return m_jobOutputDataWidget;
}

JobMessagePanel* JobViewDocks::jobMessagePanel()
{
    return m_jobMessagePanel;
}

//! Sets docks visibility so they match the activity flag.

void JobViewDocks::setActivity(int activity)
{
    QVector<JobViewFlags::Dock> docksToShow
        = JobViewActivities::activeDocks(JobViewFlags::Activity(activity));

    std::vector<int> docks_id;
    for (auto x : docksToShow)
        docks_id.push_back(static_cast<int>(x));

    show_docks(docks_id);
}

void JobViewDocks::setItem(JobItem* jobItem)
{
    jobOutputDataWidget()->setItem(jobItem);
    jobRealTimeWidget()->setItem(jobItem);
    fitActivityPanel()->setItem(jobItem);
}

//! Sets the state of JobView to the default.

void JobViewDocks::onResetLayout()
{
    DocksController::onResetLayout();
    setActivity(static_cast<int>(default_activity));
}

//! Shows/hides JobSelectorWidget.

void JobViewDocks::onToggleJobSelector()
{
    auto selectorDock = findDock(JobViewFlags::JOB_LIST_DOCK);
    selectorDock->setHidden(!selectorDock->isHidden());
}
