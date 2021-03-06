//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testview/customplot_test_utils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_TESTS_TESTVIEW_CUSTOMPLOT_TEST_UTILS_H
#define BORNAGAIN_MVVM_TESTS_TESTVIEW_CUSTOMPLOT_TEST_UTILS_H

#include <algorithm>
#include <qcustomplot.h>
#include <vector>

//! Various common utils for unit tests.

namespace TestUtils {

//! Returns vector representing bin centers/values on QCPGraph.

template <typename G, typename T> std::vector<double> get_values(const G* graph, T operand)
{
    std::vector<double> result;
    auto graph_data = *graph->data();
    std::transform(std::begin(graph_data), std::end(graph_data), std::back_inserter(result),
                   [operand](const auto& point) { return operand(point); });
    return result;
}

//! Returns vector representing bin centers on QCPgraph.
std::vector<double> binCenters(const QCPGraph* graph);

//! Returns vector representing y-values on QCPgraph.
std::vector<double> binValues(const QCPGraph* graph);

//! Returns vector representing bin errors of QCPGraph.
std::vector<double> binErrors(const QCPGraph* graph);

//! Finds and returns specific plottable in QCustomPlot canvas.
template <typename T> T* GetPlottable(QCustomPlot* custom_plot)
{
    for (int i = 0; i < custom_plot->plottableCount(); ++i) {
        if (auto plottable = dynamic_cast<T*>(custom_plot->plottable()); plottable)
            return plottable;
    }
    return nullptr;
}
} // namespace TestUtils

Q_DECLARE_METATYPE(QCPRange)

#endif // BORNAGAIN_MVVM_TESTS_TESTVIEW_CUSTOMPLOT_TEST_UTILS_H
