// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayoutStrategyBuilder.cpp
//! @brief     Implements class LayoutStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayoutStrategyBuilder.h"
#include "DecouplingApproximationStrategy.h"
#include "Exceptions.h"
#include "FormFactorCoherentSum.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "IFresnelMap.h"
#include "ILayout.h"
#include "IParticle.h"
#include "InterferenceFunctionNone.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "SlicedFormFactorList.h"
#include "SSCApproximationStrategy.h"


LayoutStrategyBuilder::LayoutStrategyBuilder(
    const MultiLayer* p_multilayer, const ILayout* p_layout,
    const IFresnelMap* p_fresnel_map, bool polarized,
    const SimulationOptions& sim_params, size_t layer_index)
    : mp_multilayer(p_multilayer)
    , mp_layout(p_layout)
    , mp_fresnel_map(p_fresnel_map)
    , m_polarized {polarized}
    , m_sim_params (sim_params)
    , m_layer_index(layer_index)
{
    createStrategy();
}

// needs class definitions => don't move to .h
LayoutStrategyBuilder::~LayoutStrategyBuilder()
{}

IInterferenceFunctionStrategy* LayoutStrategyBuilder::releaseStrategy()
{
    return mP_strategy.release();
}

std::map<size_t, std::vector<HomogeneousRegion> > LayoutStrategyBuilder::regionMap() const
{
    return m_region_map;
}

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
void LayoutStrategyBuilder::createStrategy()
{
    SafePointerVector<class FormFactorCoherentSum> ff_wrappers = collectFormFactorList();

    switch (mp_layout->getApproximation())
    {
    case ILayout::DA:
        mP_strategy.reset( new DecouplingApproximationStrategy(m_sim_params, m_polarized) );
        break;
    case ILayout::SSCA:
        double kappa = mp_layout ? mp_layout->interferenceFunction()->getKappa()
                                 : 0.0;
        if (kappa<=0.0)
            throw Exceptions::ClassInitializationException(
                "SSCA requires a nontrivial interference function "
                "with a strictly positive coupling coefficient kappa");
        mP_strategy.reset( new SSCApproximationStrategy(m_sim_params, kappa, m_polarized) );
        break;
    }
    if (!mP_strategy)
        throw Exceptions::ClassInitializationException("Could not create appropriate strategy");
    mP_strategy->init(ff_wrappers, mp_layout->interferenceFunction());
    return;
}

//! Sets m_formfactor_wrappers, the list of weighted form factors.
SafePointerVector<class FormFactorCoherentSum> LayoutStrategyBuilder::collectFormFactorList()
{
    SafePointerVector<class FormFactorCoherentSum> result;
    double layout_abundance = mp_layout->getTotalAbundance();
    for (const IParticle* particle: mp_layout->particles()) {
        auto p_ff_coh = createFormFactorCoherentSum(particle);
        p_ff_coh->scaleRelativeAbundance(layout_abundance);
        result.push_back(p_ff_coh);
    }
    double scale_factor = mp_layout->totalParticleSurfaceDensity()/layout_abundance;
    ScaleRegionMap(m_region_map, scale_factor);
    return result;
}

//! Returns a new formfactor wrapper for a given particle in given ambient material.
FormFactorCoherentSum* LayoutStrategyBuilder::createFormFactorCoherentSum(
    const IParticle* particle)
{
    double abundance = particle->abundance();
    auto sliced_ffs = CreateSlicedFormFactors(*particle, *mp_multilayer, m_layer_index);
    auto region_map = sliced_ffs.regionMap();
    ScaleRegionMap(region_map, abundance);
    mergeRegionMap(region_map);
    std::unique_ptr<FormFactorCoherentSum> P_result(new FormFactorCoherentSum(abundance));
    for (size_t i=0; i < sliced_ffs.size(); ++i) {
        auto ff_pair = sliced_ffs[i];
        std::unique_ptr<IFormFactor> P_ff_framework;
        if (mp_multilayer->numberOfLayers()>1) {
            if (m_polarized)
                P_ff_framework.reset(new FormFactorDWBAPol(*ff_pair.first));
            else
                P_ff_framework.reset(new FormFactorDWBA(*ff_pair.first));
        } else
            P_ff_framework.reset(ff_pair.first->clone());

        size_t layer_index = ff_pair.second;
        const HomogeneousMaterial* p_layer_material = mp_multilayer->layer(layer_index)->material();
        P_ff_framework->setAmbientMaterial(*p_layer_material);

        auto part = FormFactorCoherentPart(P_ff_framework.release());
        part.setSpecularInfo(mp_fresnel_map, layer_index);

        P_result->addCoherentPart(part);
    }
    return P_result.release();
}

void LayoutStrategyBuilder::mergeRegionMap(
        const std::map<size_t, std::vector<HomogeneousRegion>>& region_map)
{
    for (auto& entry : region_map)
    {
        size_t layer_index = entry.first;
        auto regions = entry.second;
        m_region_map[layer_index].insert(m_region_map[layer_index].begin(),
                                         regions.begin(), regions.end());
    }
}

void ScaleRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map, double factor)
{
    for (auto& entry : region_map)
    {
        for (auto& region : entry.second)
        {
            region.m_volume *= factor;
        }
    }
}
