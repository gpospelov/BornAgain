// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerFillLimits.cpp
//! @brief     Implements class LayerFillLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerFillLimits.h"
#include <algorithm>

LayerFillLimits::LayerFillLimits(std::vector<double> layers_bottomz)
    : m_layers_bottomz(std::move(layers_bottomz))
{
    size_t n_layers = layers_bottomz.size() + 1;
    if (n_layers < 2)
        m_layer_fill_limits.emplace_back(ZLimits::INFINITE);
    else
        for (size_t i=0; i<n_layers; ++i)
            m_layer_fill_limits.emplace_back(ZLimits::NONE);
}

void LayerFillLimits::update(std::pair<double, double> particle_limits, double offset)
{
    double top = particle_limits.first + offset;
    double bottom = particle_limits.second + offset;
    if (bottom >= top)
        return;
    size_t top_index = layerIndexTop(top);
    size_t bottom_index = layerIndexBottom(bottom);
}

std::vector<ZLimits> LayerFillLimits::layerZLimits() const
{
    return m_layer_fill_limits;
}

size_t LayerFillLimits::layerIndexTop(double top_z) const
{
    if (m_layers_bottomz.empty())
        return 0;
    if (top_z <= m_layers_bottomz.back())
        return m_layers_bottomz.size();
    auto index_above = std::lower_bound(m_layers_bottomz.rbegin(),
                                        m_layers_bottomz.rend(), top_z);
    return static_cast<size_t>(m_layers_bottomz.rend() - index_above);
}

size_t LayerFillLimits::layerIndexBottom(double bottom_z) const
{
    if (m_layers_bottomz.empty())
        return 0;
    if (bottom_z < m_layers_bottomz.back())
        return m_layers_bottomz.size();
    auto index_below = std::upper_bound(m_layers_bottomz.rbegin(),
                                        m_layers_bottomz.rend(), bottom_z);
    return static_cast<size_t>(m_layers_bottomz.rend() - index_below);

}
