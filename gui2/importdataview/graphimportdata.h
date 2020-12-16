// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_IMPORTDATAVIEW_GRAPHIMPORTDATA_H
#define BORNAGAIN_GUI2_IMPORTDATAVIEW_GRAPHIMPORTDATA_H

#include "darefl_export.h"
#include <string>
#include <vector>

namespace gui2 {

//! Raw data to construct GraphItem and Data1DItem's.

struct DAREFLCORE_EXPORT GraphImportData {
    std::string graph_description;

    std::vector<double> bin_centers;
    std::string axis_units;

    std::vector<double> bin_values;
    std::string signal_units;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_IMPORTDATAVIEW_GRAPHIMPORTDATA_H
