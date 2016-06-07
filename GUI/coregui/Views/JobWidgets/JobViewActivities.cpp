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

//if(activity == JobViewActivities::JOB_VIEW_ACTIVITY) {
//    m_docks->dock(JobViewDocks::JOB_LIST_DOCK)->show();
//    m_docks->dock(JobViewDocks::REAL_TIME_DOCK)->hide();
//    m_docks->dock(JobViewDocks::FIT_PANEL_DOCK)->hide();
//    m_docks->dock(JobViewDocks::JOB_MESSAGE_DOCK)->hide();
//}

//else if(activity == JobViewActivities::REAL_TIME_ACTIVITY) {
//    m_docks->dock(JobViewDocks::JOB_LIST_DOCK)->hide();
//    m_docks->dock(JobViewDocks::REAL_TIME_DOCK)->show();
//    m_docks->dock(JobViewDocks::FIT_PANEL_DOCK)->hide();
//    m_docks->dock(JobViewDocks::JOB_MESSAGE_DOCK)->hide();
//    m_docks->jobRealTimeWidget()->updateCurrentItem();
//}

//else if(activity == JobViewActivities::FITTING_ACTIVITY) {
//    m_docks->dock(JobViewDocks::JOB_LIST_DOCK)->hide();
//    m_docks->dock(JobViewDocks::REAL_TIME_DOCK)->show();
//    m_docks->dock(JobViewDocks::FIT_PANEL_DOCK)->show();
//    m_docks->dock(JobViewDocks::JOB_MESSAGE_DOCK)->show();
//    m_docks->jobRealTimeWidget()->updateCurrentItem();
//    m_docks->fitActivityPanel()->updateCurrentItem();
//}

//namespace {
//QMap<QString, QStringList> result;
//result[Constants::JobViewActivityName] = QStringList() << Constants::
//}

//QMap<QString, QStringList> JobViewActivities::m_activityToWidgetNames = acitivyToWidgetMap();


QStringList JobViewActivities::activityList()
{
    QStringList result = QStringList() << Constants::JobViewActivityName
        << Constants::JobRealTimeActivityName << Constants::JobFittingActivityName;
    return result;
}
