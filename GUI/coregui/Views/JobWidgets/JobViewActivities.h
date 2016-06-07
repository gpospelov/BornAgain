// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/JobViewActivities.h
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

#include "WinDllMacros.h"
#include <QStringList>
#include <QMap>

//! The JobViewActivities class is a helper static class to get list of activities,
//! and names of widgets which should be shown/hidden during current activity.

class BA_CORE_API_ JobViewActivities {

public:
    static QStringList activityList();


private:
//    static QMap<QString, QStringList> m_activityToWidgetNames;

};


#endif
