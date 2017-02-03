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

void FullFresnelMap::push_back(ILayerSpecularInfo* p_layer_map)
{
    m_full_map.push_back(p_layer_map);
}

size_t FullFresnelMap::size() const
{
    return m_full_map.size();
}

const ILayerRTCoefficients*FullFresnelMap::getOutCoefficients(
    const SimulationElement& sim_element, size_t layer_index) const
{
    return layerFresnelMap(layer_index)->getOutCoefficients(sim_element);
}

const ILayerRTCoefficients*FullFresnelMap::getInCoefficients(
    const SimulationElement& sim_element, size_t layer_index) const
{
    return layerFresnelMap(layer_index)->getInCoefficients(sim_element);
}

const ILayerSpecularInfo* FullFresnelMap::layerFresnelMap(size_t index) const
{
    return m_full_map[index];
}
