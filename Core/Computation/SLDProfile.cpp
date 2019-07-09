// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SLDProfile.cpp
//! @brief     Implements class SLDProfile.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SLDProfile.h"

SLDProfile::SLDProfile(const std::vector<Slice> &slices)
    : m_slices(slices)
{}

SLDProfile::~SLDProfile() = default;
