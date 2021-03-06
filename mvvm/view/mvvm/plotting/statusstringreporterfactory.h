//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/statusstringreporterfactory.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H

//! Contains factory methods to create StatusStringReporter

#include "mvvm/view_export.h"
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView {

class StatusStringReporter;

//! Creates reporter for status string in QCustomPlot containing graphs.
MVVM_VIEW_EXPORT std::unique_ptr<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

//! Creates reporter for status string in QCustomPlot containing QCPColorMap.
MVVM_VIEW_EXPORT std::unique_ptr<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback);

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_STATUSSTRINGREPORTERFACTORY_H
