// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_QUICKSIMEDITOR_MATERIALPROFILE_H
#define DAREFL_QUICKSIMEDITOR_MATERIALPROFILE_H

#include "darefl_export.h"
#include "gui2/quicksimeditor/quicksim_types.h"

namespace DaRefl {

//! Collection of methods borrowed from BornAgain for material profile calculations.

namespace MaterialProfile {

//! Calculate average material profile for given multilayer
DAREFLCORE_EXPORT std::vector<complex_t> CalculateProfile(const multislice_t& multilayer,
                                                          int n_points, double z_min, double z_max);

//! Get default z limits for generating a material profile
DAREFLCORE_EXPORT std::pair<double, double>
DefaultMaterialProfileLimits(const multislice_t& multilayer);

//! Generate z values (equidistant) for use in MaterialProfile
DAREFLCORE_EXPORT std::vector<double> GenerateZValues(int n_points, double z_min, double z_max);

} // namespace MaterialProfile

} // namespace DaRefl

#endif // DAREFL_QUICKSIMEDITOR_MATERIALPROFILE_H
