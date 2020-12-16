// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H
#define DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H

#include "darefl_export.h"
#include "gui2/quicksimeditor/quicksim_types.h"

class MultiLayerItem;

class Slice;

//! Collection of utility funcitons for running quick simulations.
namespace DaRefl::Utils {

//! Creates multi-slice presentation of internal multilayer structure.
DAREFLCORE_EXPORT multislice_t CreateMultiSlice(const MultiLayerItem& multilayer);

DAREFLCORE_EXPORT std::vector<Slice> createBornAgainSlices(const multislice_t& multislice);

} // namespace DaRefl::Utils

#endif // DAREFL_QUICKSIMEDITOR_QUICKSIMUTILS_H
