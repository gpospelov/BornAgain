// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerFillLimits.h
//! @brief     Defines class LayerFillLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERFILLLIMITS_H
#define LAYERFILLLIMITS_H

#include "ZLimits.h"
#include <cstddef>
#include <vector>
#include <utility>

//! Helper class for the graded layer approximation. Generates limits for each layer, indicating
//! the region of the layer (along z) that contains particle(s)
//!
//! The constructor takes the bottom layer z-coordinates as parameter. This means that for N
//! layers, only N-1 coordinates need to be passed (the last layer is assumed to be semi-infinite).
//! @ingroup algorithms_internal

class LayerFillLimits
{
public:
    LayerFillLimits(std::vector<double> layers_bottomz);

    void update(std::pair<double, double> particle_limits, double offset=0.0);

    std::vector<ZLimits> layerZLimits() const;
private:
    size_t layerIndexTop(double top_z) const;
    size_t layerIndexBottom(double bottom_z) const;
    void updateLayerLimits(size_t i_layer, ZLimits limits);
    std::vector<double> m_layers_bottomz;
    std::vector<ZLimits> m_layer_fill_limits;
};

#endif // LAYERFILLLIMITS_H
