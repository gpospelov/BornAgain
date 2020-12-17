//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/quicksimeditor/quicksim_types.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIM_TYPES_H
#define BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIM_TYPES_H

#include "darefl_export.h"
#include <complex>
#include <vector>

namespace gui2 {

using complex_t = std::complex<double>;

//! Data structure for simple multilayer representation.
struct DAREFLCORE_EXPORT SliceData {
    complex_t material;
    double thickness{0.0};
    double sigma{0.0}; // top interface sigma
};
using multislice_t = std::vector<SliceData>;

//! Represents data to run specular simulations.
struct DAREFLCORE_EXPORT SimulationInput {
    std::vector<double> qvalues;
    multislice_t slice_data;
    double intensity;
};

//! Represents results of the simulation.
struct DAREFLCORE_EXPORT SimulationResult {
    std::vector<double> qvalues;
    std::vector<double> amplitudes;
};

//! Represents results of SLD profile calculations.
struct DAREFLCORE_EXPORT SLDProfile {
    double zmin{0.0};
    double zmax{0.0};
    std::vector<double> sld_real_values;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_QUICKSIMEDITOR_QUICKSIM_TYPES_H
