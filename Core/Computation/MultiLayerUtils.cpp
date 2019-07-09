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
#include "LayerInterface.h"
#include "MaterialUtils.h"
#include "MultiLayer.h"
#include "ProcessedSample.h"
#include "ProfileHelper.h"
#include "SimulationOptions.h"

namespace
{
std::vector<double> BottomLayerCoordinates(const MultiLayer& multilayer);
std::vector<double> GenerateZValues(int n_points, double z_min, double z_max);
} // namespace

double MultiLayerUtils::LayerThickness(const MultiLayer& multilayer, size_t i)
{
    return multilayer.layer(i)->thickness();
}

const LayerInterface* MultiLayerUtils::LayerTopInterface(const MultiLayer& multilayer, size_t i)
{
    if (i == 0)
        return nullptr;
    return multilayer.layerInterface(i - 1);
}

const LayerInterface* MultiLayerUtils::LayerBottomInterface(const MultiLayer& multilayer, size_t i)
{
    if (i + 1 < multilayer.numberOfLayers())
        return multilayer.layerInterface(i);
    return nullptr;
}

const LayerRoughness* MultiLayerUtils::LayerTopRoughness(const MultiLayer& multilayer, size_t i)
{
    if (i == 0)
        return nullptr;
    return multilayer.layerInterface(i - 1)->getRoughness();
}

size_t MultiLayerUtils::IndexOfLayer(const MultiLayer& multilayer, const Layer* p_layer)
{
    for (size_t i = 0; i < multilayer.numberOfLayers(); ++i)
        if (p_layer == multilayer.layer(i))
            return i;
    throw std::out_of_range("MultiLayerUtils::IndexOfLayer: layer not found");
}

bool MultiLayerUtils::ContainsCompatibleMaterials(const MultiLayer& multilayer)
{
    return MaterialUtils::checkMaterialTypes(multilayer.containedMaterials())
           != MATERIAL_TYPES::InvalidMaterialType;
}

std::vector<ZLimits> MultiLayerUtils::ParticleRegions(const MultiLayer& multilayer,
                                                      bool use_slicing)
{
    auto bottom_coords = BottomLayerCoordinates(multilayer);
    LayerFillLimits layer_fill_limits(bottom_coords);
    if (use_slicing) {
        for (size_t i = 0; i < multilayer.numberOfLayers(); ++i) {
            auto p_layer = multilayer.layer(i);
            double offset = (i == 0) ? 0 : bottom_coords[i - 1];
            for (auto p_layout : p_layer->layouts()) {
                for (auto p_particle : p_layout->particles())
                    layer_fill_limits.update(p_particle->bottomTopZ(), offset);
            }
        }
    }
    return layer_fill_limits.layerZLimits();
}

std::vector<complex_t> MultiLayerUtils::MaterialProfile(const MultiLayer& multilayer, int n_points,
                                                        double z_min, double z_max)
{
    SimulationOptions options;
    options.setUseAvgMaterials(true);
    ProcessedSample sample(multilayer, options);
    ProfileHelper helper(sample);
    std::vector<double> z_values = GenerateZValues(n_points, z_min, z_max);
    return helper.calculateProfile(z_values);
}

namespace
{
std::vector<double> BottomLayerCoordinates(const MultiLayer& multilayer)
{
    auto n_layers = multilayer.numberOfLayers();
    if (n_layers < 2)
        return {};
    std::vector<double> result(n_layers - 1);
    result[0] = 0.0;
    for (size_t i = 1; i < n_layers - 1; ++i) {
        result[i] = result[i - 1] - MultiLayerUtils::LayerThickness(multilayer, i);
    }
    return result;
}
std::vector<double> GenerateZValues(int n_points, double z_min, double z_max)
{
    std::vector<double> result;
    if (n_points < 1)
        return result;
    double step = n_points > 1 ? (z_max - z_min) / (n_points - 1) : 0.0;
    for (int i = 0; i < n_points; ++i) {
        result.push_back(z_min + i * step);
    }
    return result;
}
} // unnamed namespace
