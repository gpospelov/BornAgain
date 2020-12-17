//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/quicksimeditor/quicksimutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMUTILS_H
#define BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMUTILS_H

#include "darefl_export.h"
#include "gui2/quicksimeditor/quicksim_types.h"

class Slice;

namespace gui2 {

class MultiLayerItem;

//! Collection of utility functions for running quick simulations.
namespace Utils {

//! Creates multi-slice presentation of internal multilayer structure.
DAREFLCORE_EXPORT multislice_t CreateMultiSlice(const MultiLayerItem& multilayer);

DAREFLCORE_EXPORT std::vector<Slice> createBornAgainSlices(const multislice_t& multislice);

} // namespace Utils

} // namespace gui2

#endif // BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIMUTILS_H
