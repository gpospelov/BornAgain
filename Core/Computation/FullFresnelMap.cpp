// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/FullFresnelMap.cpp
//! @brief     Implements class FullFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FullFresnelMap.h"
#include "ILayerSpecularInfo.h"

FullFresnelMap::FullFresnelMap()
{}

FullFresnelMap::~FullFresnelMap()
{}

void FullFresnelMap::setMap(ILayerSpecularInfo* p_map)
{
    mP_map.reset(p_map);
}

const ILayerRTCoefficients*FullFresnelMap::getOutCoefficients(
    const SimulationElement& sim_element, size_t layer_index) const
{
    return mP_map->getOutCoefficients(sim_element, layer_index);
}

const ILayerRTCoefficients*FullFresnelMap::getInCoefficients(
    const SimulationElement& sim_element, size_t layer_index) const
{
    return mP_map->getInCoefficients(sim_element, layer_index);
}

