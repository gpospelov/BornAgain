//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/mouseposinfo.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_MOUSEPOSINFO_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_MOUSEPOSINFO_H

#include "mvvm/view_export.h"

class QCustomPlot;

namespace ModelView {

//! Aggregate to hold mouse position info in QCustomPlot context.
//! Position is given in axis coordinates corresponding to the current zoom level.

struct MVVM_VIEW_EXPORT MousePosInfo {
    double xpos{0.0};
    double ypos{0.0};
    bool in_axes_range{false};
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_MOUSEPOSINFO_H
