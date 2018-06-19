// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBAComputation.cpp
//! @brief     Implements class DWBAComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DWBAComputation.h"
#include "GISASSpecularComputation.h"
#include "IComputationUtils.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ParticleLayoutComputation.h"
#include "ProgressHandler.h"
#include "RoughMultiLayerComputation.h"
#include "ScalarFresnelMap.h"
#include "SimulationElement.h"

static_assert(std::is_copy_constructible<DWBAComputation>::value == false,
    "DWBAComputation should not be copy constructable");
static_assert(std::is_copy_assignable<DWBAComputation>::value == false,
    "DWBAComputation should not be copy assignable");

DWBAComputation::DWBAComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                                 ProgressHandler& progress,
                                 std::vector<SimulationElement>::iterator begin_it,
                                 std::vector<SimulationElement>::iterator end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it)
    , m_end_it(end_it)
{
    mP_fresnel_map = IComputationUtils::CreateFresnelMap(multilayer, options);
    bool polarized = mP_multi_layer->containsMagneticMaterial();
    size_t nLayers = mP_multi_layer->numberOfLayers();
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mP_multi_layer->layer(i);
        for (auto p_layout : layer->layouts())
            m_single_computation.addLayoutComputation(
                        new ParticleLayoutComputation(mP_multi_layer.get(), mP_fresnel_map.get(),
                                                      p_layout, i, m_sim_options, polarized));
    }
    // scattering from rough surfaces in DWBA
    if (mP_multi_layer->hasRoughness())
        m_single_computation.setRoughnessComputation(
                    new RoughMultiLayerComputation(mP_multi_layer.get(), mP_fresnel_map.get()));
    if (m_sim_options.includeSpecular())
        m_single_computation.setSpecularBinComputation(
                    new GISASSpecularComputation(mP_multi_layer.get(), mP_fresnel_map.get()));
    initFresnelMap();
}

DWBAComputation::~DWBAComputation() = default;

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// For specular peak: |R|^2 * sin(alpha_i) / solid_angle
// This allows them to be added and normalized together to the beam afterwards
void DWBAComputation::runProtected()
{
    m_single_computation.setProgressHandler(mp_progress);
    if (!mp_progress->alive())
        return;
    for (auto it=m_begin_it; it != m_end_it; ++it) {
        m_single_computation.compute(*it);
    }
}

std::unique_ptr<MultiLayer> DWBAComputation::getAveragedMultilayer() const
{
    std::map<size_t, std::vector<HomogeneousRegion>> region_map;
    m_single_computation.mergeRegionMap(region_map);
    std::unique_ptr<MultiLayer> P_result(mP_multi_layer->clone());
    auto last_layer_index = P_result->numberOfLayers()-1;
    for (auto& entry : region_map)
    {
        auto i_layer = entry.first;
        if (i_layer==0 || i_layer==last_layer_index)
            continue;  // skip semi-infinite layers
        auto layer_mat = P_result->layerMaterial(i_layer);
        if (!checkRegions(entry.second))
            throw std::runtime_error("DWBAComputation::getAveragedMultilayer: "
                                     "total volumetric fraction of particles exceeds 1!");
        auto new_mat = createAveragedMaterial(layer_mat, entry.second);
        P_result->setLayerMaterial(i_layer, new_mat);
    }
    return P_result;
}

std::unique_ptr<MultiLayer> DWBAComputation::getMultilayerForFresnel() const
{
    std::unique_ptr<MultiLayer> P_result = m_sim_options.useAvgMaterials()
                                           ? getAveragedMultilayer()
                                           : std::unique_ptr<MultiLayer>(mP_multi_layer->clone());
    P_result->initBFields();
    return P_result;
}

void DWBAComputation::initFresnelMap()
{
    auto multilayer = getMultilayerForFresnel();
    mP_fresnel_map->setMultilayer(*multilayer);
}

bool DWBAComputation::checkRegions(const std::vector<HomogeneousRegion>& regions) const
{
    double total_fraction = 0;
    for (auto& region : regions)
        total_fraction += region.m_volume;
    return (total_fraction >= 0 && total_fraction <= 1);
}
