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
#include "WeightedFormFactor.h"
#include "FormFactorDWBA.h"
#include "FormFactorDWBAPol.h"
#include "ILayout.h"
#include "IParticle.h"
#include "InterferenceFunctionNone.h"
#include "MultiLayer.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "DecouplingApproximationStrategy.h"
#include "SizeSpacingCorrelationApproximationStrategy.h"

LayerStrategyBuilder::LayerStrategyBuilder(
    const Layer& decorated_layer, const MultiLayer& sample,
    const SimulationOptions& sim_params, size_t layout_index,
    const LayerSpecularInfo* specular_info)
    : m_sim_params{sim_params}, mP_specular_info{nullptr}, m_layout_index{layout_index}
{
    mP_layer.reset(decorated_layer.clone());
    assert(mP_layer->getNumberOfLayouts() > 0);
    mP_sample.reset(sample.clone());
    assert(specular_info);
    mP_specular_info.reset(specular_info->clone());
}

LayerStrategyBuilder::~LayerStrategyBuilder()
{} // cannot be moved to .h, needs definitions of classes that are forward declared in .h

//! Returns a new strategy object that is able to calculate the scattering for fixed k_f.
IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy()
{
    collectWeightedFormFactors();
    collectInterferenceFunction();
    IInterferenceFunctionStrategy* p_result = nullptr;
    switch (mP_layer->getLayout(m_layout_index)->getApproximation())
    {
    case ILayout::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params);
        break;
    case ILayout::SSCA:
    {
        if (!mP_interference_function)
            throw Exceptions::ClassInitializationException(
                "SSCA requires an interference function");
        double kappa = mP_interference_function->getKappa();
        if (kappa<=0.0)
            throw Exceptions::ClassInitializationException(
                "SSCA requires a strictly positive coupling value");
        p_result = new SizeSpacingCorrelationApproximationStrategy(m_sim_params, kappa);
        break;
    }
    default:
        throw Exceptions::ClassInitializationException(
            "Unknown interference function approximation");
    }
    if (!p_result)
        throw Exceptions::ClassInitializationException(
            "Could not create appropriate strategy");
    p_result->init(m_weighted_ffs, *mP_interference_function);
    p_result->setSpecularInfo(*mP_specular_info);
    return p_result;
}

//! Sets m_weighted_ffs, the list of weighted form factors.
void LayerStrategyBuilder::collectWeightedFormFactors()
{
    assert(mP_layer->getNumberOfLayouts()>0);
    m_weighted_ffs.clear();
    const ILayout* p_layout = mP_layer->getLayout(m_layout_index);
    const IMaterial* p_layer_material = mP_layer->getMaterial();
    double total_abundance = mP_layer->getTotalAbundance();
    if (total_abundance<=0.0) // TODO: why this can happen? why not throw error?
        total_abundance = 1.0;
    for (const IParticle* particle: p_layout->getParticles()) {
        WeightedFormFactor* p_weighted_ff;
        p_weighted_ff = createWeightedFormFactor(particle, p_layer_material);
        p_weighted_ff->m_abundance /= total_abundance;
        m_weighted_ffs.push_back(p_weighted_ff);
    }
}

//! Sets mP_interference_function.
void LayerStrategyBuilder::collectInterferenceFunction()
{
    assert(mP_layer->getNumberOfLayouts()>0);
    const IInterferenceFunction* p_iff =
        mP_layer->getLayout(m_layout_index)->getInterferenceFunction();
    if (p_iff)
        mP_interference_function.reset(p_iff->clone());
    else
        mP_interference_function.reset( new InterferenceFunctionNone() );
}

//! Returns a new weighted formfactor for a given particle in given ambient material.
WeightedFormFactor* LayerStrategyBuilder::createWeightedFormFactor(
    const IParticle* particle, const IMaterial* p_ambient_material) const
{
    const std::unique_ptr<IParticle> P_particle_clone(particle->clone());
    P_particle_clone->setAmbientMaterial(*p_ambient_material);

    // formfactor
    const std::unique_ptr<IFormFactor> P_ff_particle(P_particle_clone->createFormFactor());
    IFormFactor* p_ff_framework;
    if (mP_layer->getNumberOfLayers()>1) {
        if (mP_sample->containsMagneticMaterial())
            p_ff_framework = new FormFactorDWBAPol(*P_ff_particle);
        else
            p_ff_framework = new FormFactorDWBA(*P_ff_particle);
    } else
        p_ff_framework = P_ff_particle->clone();

    return new WeightedFormFactor(p_ff_framework, particle->getAbundance());
}
