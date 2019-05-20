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

#include "IMultiLayerFresnelMap.h"
#include "MultiLayer.h"

static_assert(std::is_copy_constructible<IMultiLayerFresnelMap>::value == false,
    "IFresnelMap should not be copy constructable");
static_assert(std::is_copy_assignable<IMultiLayerFresnelMap>::value == false,
    "IFresnelMap should not be copy assignable");

IMultiLayerFresnelMap::IMultiLayerFresnelMap()
    : m_use_cache(true)
{}
IMultiLayerFresnelMap::~IMultiLayerFresnelMap() {}

void IMultiLayerFresnelMap::setMultilayer(const MultiLayer& multilayer)
{
    mP_multilayer.reset(multilayer.clone());
}

void IMultiLayerFresnelMap::disableCaching()
{
    m_use_cache = false;
}
