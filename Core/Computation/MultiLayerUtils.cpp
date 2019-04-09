// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerUtils.cpp
//! @brief     Implements helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiLayerUtils.h"
#include "ILayout.h"
#include "Layer.h"
#include "LayerFillLimits.h"
#include "MultiLayer.h"

namespace {
std::vector<double> BottomLayerCoordinates(const MultiLayer& multilayer);
}

std::vector<ZLimits> MultiLayerUtils::ParticleRegions(const MultiLayer &multilayer,
                                                      bool use_slicing)
{
    auto bottom_coords = BottomLayerCoordinates(multilayer);
    LayerFillLimits layer_fill_limits(bottom_coords);
    if (use_slicing) {
        for (size_t i=0; i<multilayer.numberOfLayers(); ++i)
        {
            auto p_layer = multilayer.layer(i);
            double offset = (i==0) ? 0 : bottom_coords[i-1];
            for (auto p_layout : p_layer->layouts())
            {
                for (auto p_particle : p_layout->particles())
                    layer_fill_limits.update(p_particle->bottomTopZ(), offset);
            }
        }
    }
    return layer_fill_limits.layerZLimits();
}

namespace {
std::vector<double> BottomLayerCoordinates(const MultiLayer& multilayer)
{
    auto n_layers = multilayer.numberOfLayers();
    if (n_layers < 2) return {};
    std::vector<double> result(n_layers-1);
    result[0] = 0.0;
    for (size_t i=1; i < n_layers - 1; ++i) {
        result[i] = result[i-1] - multilayer.layerThickness(i);
    }
    return result;
}
}  // unnamed namespace

