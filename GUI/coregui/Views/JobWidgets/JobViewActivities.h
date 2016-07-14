// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewActivities.h
//! @brief     Declares class JobViewActivities
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBVIEWACTIVITIES_H
#define JOBVIEWACTIVITIES_H

#include <QMap>
#include <QStringList>
#include <QVector>
#include "JobViewFlags.h"
#include "WinDllMacros.h"

//! The JobViewActivities class is a helper static class to get info related to JobView activities
//! (JobViewActivity, RealTimeActivity and FittingActivity).

class BA_CORE_API_ JobViewActivities {

public:
    using activity_map_t = QMap<JobViewFlags::Activity, QVector<JobViewFlags::Dock>>;

    static QStringList activityList();

    static QVector<JobViewFlags::Dock> activeDocks(JobViewFlags::Activity activity);

private:
    static activity_map_t m_activityToDocks;
};

#endif // JOBVIEWACTIVITIES_H
