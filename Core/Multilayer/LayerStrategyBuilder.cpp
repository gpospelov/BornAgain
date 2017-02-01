// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/LayerStrategyBuilder.cpp
//! @brief     Implements class LayerStrategyBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerStrategyBuilder.h"
#include "Exceptions.h"
#include "FormFactorCoherentSum.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "ILayout.h"
#include "IParticle.h"
#include "InterferenceFunctionNone.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "ILayerSpecularInfo.h"
#include "DecouplingApproximationStrategy.h"
#include "SSCApproximationStrategy.h"

LayerStrategyBuilder::LayerStrategyBuilder(
    const MultiLayer* p_multilayer, const ILayout* p_layout,
    const SafePointerVector<ILayerSpecularInfo>* p_specular_info, bool polarized,
    const SimulationOptions& sim_params, size_t layer_index)
    : mp_multilayer(p_multilayer)
    , mp_layout(p_layout)
    , mp_specular_info_map(p_specular_info)
    , m_polarized {polarized}
    , m_sim_params (sim_params)
    , m_layer_index(layer_index)
{}

LayerStrategyBuilder::~LayerStrategyBuilder()
{} // needs class definitions => don't move to .h

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy() const
{
    SafePointerVector<class FormFactorCoherentSum> ff_wrappers = collectFormFactorList();

    IInterferenceFunctionStrategy* p_result = nullptr;
    switch (mp_layout->getApproximation())
    {
    case ILayout::DA:
        if (m_polarized)
            p_result = new DecouplingApproximationStrategy2(m_sim_params);
        else
            p_result = new DecouplingApproximationStrategy1(m_sim_params);
        break;
    case ILayout::SSCA:
        double kappa = mp_layout ? mp_layout->getInterferenceFunction()->getKappa()
                                 : 0.0;
        if (kappa<=0.0)
            throw Exceptions::ClassInitializationException(
                "SSCA requires a nontrivial interference function "
                "with a strictly positive coupling coefficient kappa");
        if (m_polarized)
            p_result = new SSCApproximationStrategy2(m_sim_params, kappa);
        else
            p_result = new SSCApproximationStrategy1(m_sim_params, kappa);
        break;
    }
    if (!p_result)
        throw Exceptions::ClassInitializationException(
            "Could not create appropriate strategy");
    p_result->init(ff_wrappers, mp_layout->getInterferenceFunction());
    return p_result;
}

//! Sets m_formfactor_wrappers, the list of weighted form factors.
SafePointerVector<class FormFactorCoherentSum> LayerStrategyBuilder::collectFormFactorList() const
{
    SafePointerVector<class FormFactorCoherentSum> result;
    const IMaterial* p_layer_material = mp_multilayer->getLayer(m_layer_index)->getMaterial();
    double layout_abundance = mp_layout->getTotalAbundance();
    if (layout_abundance<=0.0) // TODO: why this can happen? why not throw error?
        layout_abundance = 1.0;
    for (const IParticle* particle: mp_layout->getParticles()) {
        FormFactorCoherentSum* p_ff_coh;
        p_ff_coh = createFormFactorCoherentSum(particle, p_layer_material);
        p_ff_coh->scaleRelativeAbundance(layout_abundance);
        p_ff_coh->setSpecularInfo(*(*mp_specular_info_map)[m_layer_index]);
        result.push_back(p_ff_coh);
    }
    return result;
}

//! Returns a new formfactor wrapper for a given particle in given ambient material.
FormFactorCoherentSum* LayerStrategyBuilder::createFormFactorCoherentSum(
    const IParticle* particle, const IMaterial* p_ambient_material) const
{
    const std::unique_ptr<IParticle> P_particle_clone{ particle->clone() };
    P_particle_clone->setAmbientMaterial(*p_ambient_material);

    const std::unique_ptr<IFormFactor> P_ff_particle{ P_particle_clone->createFormFactor() };
    std::unique_ptr<IFormFactor> P_ff_framework;
    if (mp_multilayer->getNumberOfLayers()>1) {
        if (m_polarized)
            P_ff_framework.reset(new FormFactorDWBAPol(*P_ff_particle));
        else
            P_ff_framework.reset(new FormFactorDWBA(*P_ff_particle));
    } else
        P_ff_framework.reset(P_ff_particle->clone());

    return new FormFactorCoherentSum(P_ff_framework.release(), particle->getAbundance());
}
