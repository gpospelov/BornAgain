// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IFresnelMap.cpp
//! @brief     Implements class IFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IFresnelMap.h"
#include "Slice.h"

IFresnelMap::IFresnelMap()
    : m_use_cache(true)
{}

void IFresnelMap::setSlices(const std::vector<Slice> &slices)
{
    m_slices = slices;
}

IFresnelMap::~IFresnelMap() = default;

void IFresnelMap::disableCaching()
{
    m_use_cache = false;
}
