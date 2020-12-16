// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_IMPORTDATAVIEW_GRAPHIMPORTDATA_H
#define DAREFL_IMPORTDATAVIEW_GRAPHIMPORTDATA_H

#include "darefl_export.h"
#include <string>
#include <vector>

namespace DaRefl {

//! Raw data to construct GraphItem and Data1DItem's.

struct DAREFLCORE_EXPORT GraphImportData {
    std::string graph_description;

    std::vector<double> bin_centers;
    std::string axis_units;

    std::vector<double> bin_values;
    std::string signal_units;
};

} // namespace DaRefl

#endif // DAREFL_IMPORTDATAVIEW_GRAPHIMPORTDATA_H
