//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/statusstringreporterfactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/plotting/statusstringreporterfactory.h"
#include "mvvm/plotting/colormapinfoformatter.h"
#include "mvvm/plotting/graphinfoformatter.h"
#include "mvvm/plotting/statusstringreporter.h"

namespace ModelView {

std::unique_ptr<StatusStringReporter>
CreateGraphReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return std::make_unique<StatusStringReporter>(custom_plot, callback,
                                                  std::make_unique<GraphInfoFormatter>());
}

std::unique_ptr<StatusStringReporter>
CreateColorMapReporter(QCustomPlot* custom_plot, std::function<void(const std::string&)> callback)
{
    return std::make_unique<StatusStringReporter>(custom_plot, callback,
                                                  std::make_unique<ColorMapInfoFormatter>());
}

} // namespace ModelView
