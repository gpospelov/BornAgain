//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/statusstringformatterinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_STATUSSTRINGFORMATTERINTERFACE_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_STATUSSTRINGFORMATTERINTERFACE_H

#include "mvvm/view_export.h"
#include <string>

class QCustomPlot;

namespace ModelView {

//! Pure virtual interface to format string with status info corresponding to the current mouse
//! position on QCustomPlot.

class MVVM_VIEW_EXPORT StatusStringFormatterInterface {
public:
    virtual ~StatusStringFormatterInterface() = default;

    virtual std::string status_string(QCustomPlot* custom_plot, double x, double y) const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_STATUSSTRINGFORMATTERINTERFACE_H
