// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SLDProfile.h
//! @brief     Defines class SLDProfile.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SLDPROFILE_H
#define SLDPROFILE_H

#include "Complex.h"
#include "Material.h"
#include "WinDllMacros.h"
#include <vector>

//! Object that can generate the SLD profile of a sample as a function of depth.
//!
//! If the usage of average materials is requested, layers and particles are sliced into multiple
//! slices and the average material is calculated for each slice.
//!
//! @ingroup algorithms_internal

class ProcessedSample;

class BA_CORE_API_ SLDProfile
{
public:
    SLDProfile(const ProcessedSample& sample);
    ~SLDProfile();

private:
    complex_t sld(double z, const std::vector<complex_t>& slds) const;
    std::vector<Material> m_materials;
    std::vector<double> m_zlimits;
    std::vector<double> m_sigmas;
};

#endif // SLDPROFILE_H
