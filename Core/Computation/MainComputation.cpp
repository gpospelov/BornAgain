// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MainComputation.cpp
//! @brief     Implements class MainComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MainComputation.h"
#include "ParticleLayoutComputation.h"
#include "Layer.h"
#include "IFresnelMap.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "RoughMultiLayerComputation.h"
#include "SpecularComputation.h"
#include "ScalarFresnelMap.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"
#include <iterator> // needed for back_inserter

//#include <iostream>
namespace
{
HomogeneousMaterial CalculateAverageMaterial(const HomogeneousMaterial& layer_mat,
                                             const std::vector<HomogeneousRegion>& regions);
}

MainComputation::MainComputation(
    const MultiLayer& multi_layer,
    const SimulationOptions& options,
    ProgressHandler& progress,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
    : mP_multi_layer(multi_layer.clone())
    , mP_inverted_multilayer(multi_layer.cloneInvertB())
    , m_sim_options(options)
    , m_progress(&progress)
    , m_begin_it(begin_it)
    , m_end_it(end_it)
    , mP_fresnel_map(createFresnelMap(mP_multi_layer.get(), mP_inverted_multilayer.get()))
{
    bool polarized = mP_multi_layer->containsMagneticMaterial();
    size_t nLayers = mP_multi_layer->numberOfLayers();
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mP_multi_layer->layer(i);
        for (size_t j=0; j<layer->numberOfLayouts(); ++j)
            m_computation_terms.emplace_back(
                        new ParticleLayoutComputation(
                            mP_multi_layer.get(), mP_fresnel_map.get(), layer->layout(j), i,
                            m_sim_options, polarized));
    }
    // scattering from rough surfaces in DWBA
    if (mP_multi_layer->hasRoughness())
        m_computation_terms.emplace_back(new RoughMultiLayerComputation(mP_multi_layer.get(),
                                                                     mP_fresnel_map.get()));
    if (m_sim_options.includeSpecular())
        m_computation_terms.emplace_back(new SpecularComputation(mP_multi_layer.get(),
                                                              mP_fresnel_map.get()));
    if (m_sim_options.useAvgMaterials())
        adjustFresnelMap();
}

MainComputation::~MainComputation()
{}

void MainComputation::run()
{
    m_status.setRunning();
    try {
        runProtected();
        m_status.setCompleted();
    } catch(const std::exception &ex) {
        m_status.setErrorMessage(std::string(ex.what()));
        m_status.setFailed();
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// For specular peak: |R|^2 * sin(alpha_i) / solid_angle
// This allows them to be added and normalized together to the beam afterwards
void MainComputation::runProtected()
{
    // add intensity of all IComputationTerms:
    for (auto& comp: m_computation_terms) {
        if (!m_progress->alive())
            return;
        comp->eval(m_progress, m_begin_it, m_end_it );
    }
}

IFresnelMap* MainComputation::createFresnelMap(const MultiLayer* p_multilayer,
                                               const MultiLayer* p_inverted_multilayer)
{
        if (!p_multilayer->requiresMatrixRTCoefficients())
            return new ScalarFresnelMap(p_multilayer);
        else
            return new MatrixFresnelMap(p_multilayer, p_inverted_multilayer);
}

void MainComputation::adjustFresnelMap()
{
    std::map<size_t, std::vector<HomogeneousRegion>> region_map;
    for (auto& comp: m_computation_terms) {
        comp->mergeRegionMap(region_map);
    }
    // TODO: use this multilayer!!!
    std::unique_ptr<MultiLayer> p_multilayer(mP_multi_layer->clone());
    for (auto& entry : region_map)
    {
        auto i_layer = entry.first;
        auto layer_mat = p_multilayer->layerMaterial(i_layer);
        if (!checkRegions(entry.second))
            throw std::runtime_error("MainComputation::adjustFresnelMap: "
                                     "total volumetric fraction of particles exceeds 1!");
        auto new_mat = CalculateAverageMaterial(layer_mat, entry.second);
        p_multilayer->setLayerMaterial(i_layer, new_mat);
//        std::cout << "Layer: " << entry.first << std::endl;
//        for (auto& region : entry.second)
//            std::cout << "  Region: vol: " << region.m_volume << std::endl;
    }
}

bool MainComputation::checkRegions(const std::vector<HomogeneousRegion>& regions) const
{
    double total_fraction = 0;
    for (auto& region : regions)
        total_fraction += region.m_volume;
    return (total_fraction >= 0 && total_fraction <= 1);
}

namespace
{
HomogeneousMaterial CalculateAverageMaterial(const HomogeneousMaterial& layer_mat,
                                             const std::vector<HomogeneousRegion>& regions)
{
    kvector_t magnetization_layer = layer_mat.magneticField();
    complex_t refr_index2_layer = layer_mat.refractiveIndex2();
    kvector_t magnetization_avg = magnetization_layer;
    complex_t refr_index2_avg = refr_index2_layer;
    for (auto& region : regions)
    {
        kvector_t magnetization_region = region.m_material.magneticField();
        complex_t refr_index2_region = region.m_material.refractiveIndex2();
        magnetization_avg += region.m_volume*(magnetization_region - magnetization_layer);
        refr_index2_avg += region.m_volume*(refr_index2_region - refr_index2_layer);
    }
    complex_t refr_index_avg = std::sqrt(refr_index2_avg);
    HomogeneousMaterial result(layer_mat.getName()+"_avg", refr_index_avg, magnetization_avg);
    return result;
}
}
