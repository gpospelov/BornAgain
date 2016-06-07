// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobViewActivities.cpp
//! @brief     Implements class JobViewActivities
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobViewActivities.h"
#include "mainwindow_constants.h"
#include "GUIHelpers.h"

namespace {
JobViewActivities::activity_map_t createActivityMap()
{
    JobViewActivities::activity_map_t result;
    result[JobViewFlags::JOB_VIEW_ACTIVITY] = QVector<JobViewFlags::Dock>()
                                            << JobViewFlags::JOB_LIST_DOCK;
    result[JobViewFlags::REAL_TIME_ACTIVITY] = QVector<JobViewFlags::Dock>()
                                             << JobViewFlags::REAL_TIME_DOCK;
    result[JobViewFlags::FITTING_ACTIVITY] = QVector<JobViewFlags::Dock>()
                                           << JobViewFlags::REAL_TIME_DOCK
                                           << JobViewFlags::FIT_PANEL_DOCK
                                           << JobViewFlags::JOB_MESSAGE_DOCK;
    return result;
}
}

JobViewActivities::activity_map_t JobViewActivities::m_activityToDocks = createActivityMap();

//! Returns list of available activity names.

QStringList JobViewActivities::activityList()
{
    QStringList result = QStringList() << Constants::JobViewActivityName
        << Constants::JobRealTimeActivityName << Constants::JobFittingActivityName;
    return result;
}

//! Returns vector of JobView's dockId which have to be shown for given activity

QVector<JobViewFlags::Dock> JobViewActivities::activeDocks(JobViewFlags::Activity activity)
{
    activity_map_t::iterator it = m_activityToDocks.find(activity);
    if(it == m_activityToDocks.end()) {
        GUIHelpers::Error("JobViewActivities::activeDocks -> Error. Unknown activity");
    }
    return m_activityToDocks[activity];
}
