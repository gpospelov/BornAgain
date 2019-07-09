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

#include "Slice.h"
#include <vector>

//! Object that can generate the SLD profile of a sample as a function of depth.
//!
//! If the usage of average materials is requested, layers and particles are sliced into multiple
//! slices and the average material is calculated for each slice.
//!
//! @ingroup algorithms_internal

class BA_CORE_API_ SLDProfile
{
public:
    SLDProfile(const std::vector<Slice>& slices);
    ~SLDProfile();

private:
    std::vector<Slice> m_slices;
};

#endif // SLDPROFILE_H
