// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationUtils.cpp
//! @brief     Implements utility functions for IComputation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IComputationUtils.h"
#include "ILayout.h"
#include "IParticle.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "SimulationOptions.h"
#include "SlicedFormFactorList.h"

namespace {
void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor);
bool CheckRegions(const std::vector<HomogeneousRegion>& regions);
std::unique_ptr<MultiLayer> CreateAveragedMultilayerImpl(
        const MultiLayer& multilayer,
        const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);
}

namespace IComputationUtils {
std::unique_ptr<MultiLayer> CreateAveragedMultilayer(
        const MultiLayer& multilayer, const SimulationOptions& sim_options,
        const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    auto P_multilayer = sim_options.useAvgMaterials()
                        ? CreateAveragedMultilayerImpl(multilayer, region_map)
                        : std::unique_ptr<MultiLayer>(multilayer.clone());
    P_multilayer->initBFields();
    return P_multilayer;
}

std::unique_ptr<MultiLayer> CreateAveragedMultilayer(const MultiLayer& multilayer,
                                                     const SimulationOptions& sim_options)
{
    return CreateAveragedMultilayer(multilayer, sim_options, GetRegionMap(multilayer));
}

std::map<size_t, std::vector<HomogeneousRegion>> GetRegionMap(const MultiLayer& multilayer)
{
    std::map<size_t, std::vector<HomogeneousRegion>> result_map;
    size_t nLayers = multilayer.numberOfLayers();
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = multilayer.layer(i);
        for (auto p_layout : layer->layouts()) {
            double layout_abundance = p_layout->getTotalAbundance();
            double weight = p_layout->weight();
            double scale_factor = weight*p_layout->totalParticleSurfaceDensity()/layout_abundance;
            for (const IParticle* particle: p_layout->particles()) {
                auto sliced_ffs = SlicedFormFactorList::CreateSlicedFormFactors(
                                      *particle, multilayer, i);
                auto particle_region_map = sliced_ffs.regionMap();
                double particle_scaling = particle->abundance()*scale_factor;
                ScaleRegionMap(particle_region_map, particle_scaling);
                MergeRegionMap(result_map, particle_region_map);
            }
        }
    }
    return result_map;
}

void MergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& dest,
                    const std::map<size_t, std::vector<HomogeneousRegion>>& source)
{
    for (auto& entry : source) {
        size_t layer_index = entry.first;
        auto regions = entry.second;
        dest[layer_index].insert(dest[layer_index].begin(), regions.begin(), regions.end());
    }
}

}  // namespace IComputationUtils

namespace {
void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor)
{
    for (auto& entry : region_map) {
        for (auto& region : entry.second) {
            region.m_volume *= factor;
        }
    }
}
bool CheckRegions(const std::vector<HomogeneousRegion>& regions)
{
    double total_fraction = 0.0;
    for (auto& region : regions)
        total_fraction += region.m_volume;
    return (total_fraction >= 0 && total_fraction <= 1);
}
std::unique_ptr<MultiLayer> CreateAveragedMultilayerImpl(
        const MultiLayer& multilayer,
        const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    std::unique_ptr<MultiLayer> P_result(multilayer.clone());
    auto last_layer_index = P_result->numberOfLayers()-1;
    for (auto& entry : region_map)
    {
        auto i_layer = entry.first;
        if (i_layer==0 || i_layer==last_layer_index)
            continue;  // skip semi-infinite layers
        auto layer_mat = P_result->layerMaterial(i_layer);
        if (!CheckRegions(entry.second))
            throw std::runtime_error("IComputationUtils::CreateAveragedMultilayer: "
                                     "total volumetric fraction of particles exceeds 1!");
        auto new_mat = CreateAveragedMaterial(layer_mat, entry.second);
        P_result->setLayerMaterial(i_layer, new_mat);
    }
    return P_result;
}
}  // unnamed namespace

