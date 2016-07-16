// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/LayerStrategyBuilder.cpp
//! @brief     Implements classes LayerStrategyBuilder and
//!              FormFactorInfo
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTools.h"
#include "InterferenceFunctionStrategies.h"
#include "InterferenceFunctions.h"
#include "IParticle.h"
#include "ILayout.h"
#include "Layer.h"
#include "LayerSpecularInfo.h"
#include "Simulation.h"

LayerStrategyBuilder::LayerStrategyBuilder(
    const Layer& decorated_layer, const Simulation& simulation,
    const SimulationOptions& sim_params, size_t layout_index)
    : m_sim_params{sim_params}, mP_specular_info{nullptr}, m_layout_index{layout_index}
{
    mP_layer.reset(decorated_layer.clone());
    mP_simulation.reset(simulation.clone());
    assert(mP_layer->getNumberOfLayouts() > 0);
}

LayerStrategyBuilder::~LayerStrategyBuilder() {} // needs class declartions not present in .h

void LayerStrategyBuilder::setRTInfo(const LayerSpecularInfo& specular_info)
{
    mP_specular_info.reset(specular_info.clone());
}

IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy()
{
    collectFormFactorInfos();
    collectInterferenceFunction();
    IInterferenceFunctionStrategy* p_result(0);
    switch (mP_layer->getLayout(m_layout_index)->getApproximation())
    {
    case ILayout::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params);
        break;
    case ILayout::SSCA:
    {
        if (!mP_interference_function) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires an interference function");
        }
        double kappa = mP_interference_function->getKappa();
        if (kappa<=0.0) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires a strictly positive coupling value");
        }
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
    p_result->init(m_ff_infos, *mP_interference_function);
    p_result->setSpecularInfo(*mP_specular_info);
    return p_result;
}

bool LayerStrategyBuilder::requiresMatrixFFs() const
{
    return mP_simulation->getSample()->containsMagneticMaterial();
}

void LayerStrategyBuilder::collectFormFactorInfos()
{
    assert(mP_layer->getNumberOfLayouts()>0);
    m_ff_infos.clear();
    const ILayout* p_layout = mP_layer->getLayout(m_layout_index);
    const IMaterial* p_layer_material = mP_layer->getMaterial();
    double total_abundance = mP_layer->getTotalAbundance();
    if (total_abundance<=0.0) total_abundance = 1.0;
    SafePointerVector<const IParticle> iparticles = p_layout->getParticles();
    size_t number_of_particles = iparticles.size();
    for (size_t i = 0; i<number_of_particles; ++i) {
        FormFactorInfo* p_ff_info;
        p_ff_info = createFormFactorInfo(iparticles[i], p_layer_material);
        p_ff_info->m_abundance /= total_abundance;
        m_ff_infos.push_back(p_ff_info);
    }
    return;
}

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

FormFactorInfo* LayerStrategyBuilder::createFormFactorInfo(
    const IParticle* particle, const IMaterial* p_ambient_material) const
{
    FormFactorInfo* p_result = new FormFactorInfo;
    const std::unique_ptr<IParticle> P_particle_clone(particle->clone());
    P_particle_clone->setAmbientMaterial(*p_ambient_material);

    // formfactor
    const std::unique_ptr<IFormFactor> P_ff_particle(P_particle_clone->createFormFactor());
    IFormFactor* p_ff_framework;
    size_t n_layers = mP_layer->getNumberOfLayers();
    if (n_layers>1) {
        if (requiresMatrixFFs()) {
            p_ff_framework = FormFactorTools::createDWBAMatrixFormFactor(*P_ff_particle);
        }
        else {
            p_ff_framework = FormFactorTools::createDWBAScalarFormFactor(*P_ff_particle);
        }
    } else {
        p_ff_framework = P_ff_particle->clone();
    }
    p_result->mp_ff = p_ff_framework;
    // Other info (position and abundance)
    kvector_t position = P_particle_clone->getPosition();
    p_result->m_pos_x = position.x();
    p_result->m_pos_y = position.y();
    p_result->m_abundance = particle->getAbundance();
    return p_result;
}

// =============================================================================
// Implementation of FormFactorInfo
// =============================================================================

FormFactorInfo::~FormFactorInfo() { delete mp_ff; }

FormFactorInfo* FormFactorInfo::clone() const
{
    FormFactorInfo* p_result = new FormFactorInfo();
    p_result->m_abundance = m_abundance;
    p_result->m_pos_x = m_pos_x;
    p_result->m_pos_y = m_pos_y;
    p_result->mp_ff = mp_ff->clone();
    return p_result;
}
