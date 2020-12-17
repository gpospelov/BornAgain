//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testview/customplot_test_utils.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "customplot_test_utils.h"
#include <qcustomplot.h>

std::vector<double> TestUtils::binCenters(const QCPGraph* graph)
{
    return get_values(graph, [](auto x) { return x.key; });
}

std::vector<double> TestUtils::binValues(const QCPGraph* graph)
{
    return get_values(graph, [](auto x) { return x.value; });
}

std::vector<double> TestUtils::binErrors(const QCPGraph* graph)
{
    std::vector<double> result;
    if (auto errorBars = GetPlottable<QCPErrorBars>(graph->parentPlot()); errorBars) {
        auto container = errorBars->data();
        std::transform(container->begin(), container->end(), std::back_inserter(result),
                       [](auto x) { return x.errorPlus; });
    };
    return result;
}
