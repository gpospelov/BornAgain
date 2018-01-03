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
#include "MultiLayer.h"

static_assert(std::is_copy_constructible<IFresnelMap>::value == false,
    "IFresnelMap should not be copy constructable");
static_assert(std::is_copy_assignable<IFresnelMap>::value == false,
    "IFresnelMap should not be copy assignable");

IFresnelMap::IFresnelMap()
    : m_use_cache(true)
{}
IFresnelMap::~IFresnelMap() {}

void IFresnelMap::setMultilayer(const MultiLayer& multilayer)
{
    mP_multilayer.reset(multilayer.clone());
}

void IFresnelMap::disableCaching()
{
    m_use_cache = false;
}
