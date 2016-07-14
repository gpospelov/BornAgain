// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobViewFlags.h
//! @brief     Declares class JobViewFlags
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBVIEWFLAGS_H
#define JOBVIEWFLAGS_H

#include <QWidget>
#include "WinDllMacros.h"

//! The JobViewFlags class is a namespace for various flags used in JobView.

class JobViewFlags {
public:

    enum EDocksId {
        JOB_LIST_DOCK,
        REAL_TIME_DOCK,
        FIT_PANEL_DOCK,
        JOB_MESSAGE_DOCK,
        NUMBER_OF_DOCKS
    };
    Q_DECLARE_FLAGS(Dock, EDocksId)

    enum EActivities {
        JOB_VIEW_ACTIVITY,
        REAL_TIME_ACTIVITY,
        FITTING_ACTIVITY,
    };
    Q_DECLARE_FLAGS(Activity, EActivities)

};

Q_DECLARE_OPERATORS_FOR_FLAGS(JobViewFlags::Dock)
Q_DECLARE_OPERATORS_FOR_FLAGS(JobViewFlags::Activity)

#endif // JOBVIEWFLAGS_H
