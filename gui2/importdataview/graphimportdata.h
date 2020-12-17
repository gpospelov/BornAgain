//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/graphimportdata.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

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
