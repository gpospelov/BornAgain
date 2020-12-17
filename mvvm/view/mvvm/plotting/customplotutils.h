//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/customplotutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_CUSTOMPLOTUTILS_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_CUSTOMPLOTUTILS_H

#include "mvvm/view_export.h"

class QCPColorScale;
class QCPAxis;

namespace ModelView {

namespace Utils {

//! Switch axis to logarithmic scale mode.

MVVM_VIEW_EXPORT void SetLogarithmicScale(QCPColorScale* axis, bool is_log_scale);

//! Switch axis to logarithmic scale mode.

MVVM_VIEW_EXPORT void SetLogarithmicScale(QCPAxis* axis, bool is_log_scale);

} // namespace Utils

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_CUSTOMPLOTUTILS_H
