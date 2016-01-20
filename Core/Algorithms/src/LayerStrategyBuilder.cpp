// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerStrategyBuilder.cpp
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

#include "LayerStrategyBuilder.h"
#include "Layer.h"
#include "Simulation.h"
#include "InterferenceFunctions.h"
#include "InterferenceFunctionStrategies.h"
#include "FormFactors.h"
#include "FormFactorTools.h"

#include <cmath>
#include <boost/scoped_ptr.hpp>

LayerStrategyBuilder::LayerStrategyBuilder(
        const Layer& decorated_layer, const Simulation& simulation,
        const SimulationParameters& sim_params, size_t layout_index)
: mp_layer(decorated_layer.clone())
, mp_simulation(simulation.clone())
, m_sim_params(sim_params)
, mp_specular_info(0)
, m_layout_index(layout_index)
{
    assert(mp_layer->getNumberOfLayouts()>0);
}

LayerStrategyBuilder::~LayerStrategyBuilder()
{
    delete mp_layer;
    delete mp_simulation;
    delete mp_specular_info;
}


void LayerStrategyBuilder::setRTInfo(const LayerSpecularInfo& specular_info)
{
    if (mp_specular_info != &specular_info) {
        delete mp_specular_info;
        mp_specular_info = specular_info.clone();
    }
}

IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy()
{
    collectFormFactorInfos();
    collectInterferenceFunctions();
    size_t n_ifs = m_ifs.size();
    IInterferenceFunctionStrategy *p_result(0);
    switch (mp_layer->getLayout(m_layout_index)->getApproximation())
    {
    case ILayout::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params);
        break;
    case ILayout::SSCA:
    {
        if (n_ifs<1) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires an interference function");
        }
        double kappa = m_ifs[0]->getKappa();
        if (kappa<=0.0) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires a strictly positive coupling value");
        }
        p_result = new SizeSpacingCorrelationApproximationStrategy(
            m_sim_params, kappa);
        break;
    }
    default:
        throw Exceptions::ClassInitializationException(
                "Unknown interference function approximation");
    }
    if (!p_result) {
        throw Exceptions::ClassInitializationException(
                "Could not create appropriate strategy");
    }
    p_result->init(m_ff_infos, m_ifs);
    p_result->setSpecularInfo(*mp_specular_info);
    return p_result;
}

bool LayerStrategyBuilder::requiresMatrixFFs() const
{
    return mp_simulation->getSample()->containsMagneticMaterial();
}

void LayerStrategyBuilder::collectFormFactorInfos()
{
    assert(mp_layer->getNumberOfLayouts()>0);
    m_ff_infos.clear();
    const ILayout *p_layout = mp_layer->getLayout(m_layout_index);
    const IMaterial *p_layer_material = mp_layer->getMaterial();
    double wavelength = getWavelength();
    double total_abundance = mp_layer->getTotalAbundance();
    if (total_abundance<=0.0) total_abundance = 1.0;
    complex_t wavevector_scattering_factor = Units::PI/wavelength/wavelength;
    SafePointerVector<const IParticle> iparticles = p_layout->getParticles();
    size_t number_of_particles = iparticles.size();
    for (size_t i = 0; i<number_of_particles; ++i) {
        FormFactorInfo *p_ff_info;
        p_ff_info = createFormFactorInfo(iparticles[i], p_layer_material,
                                         wavevector_scattering_factor);
        p_ff_info->m_abundance /= total_abundance;
        m_ff_infos.push_back(p_ff_info);
    }
    return;
}

void LayerStrategyBuilder::collectInterferenceFunctions()
{
    assert(mp_layer->getNumberOfLayouts()>0);
    m_ifs.clear();
    if (mp_layer->getLayout(m_layout_index)->getNumberOfInterferenceFunctions()) {
        m_ifs = mp_layer->getLayout(m_layout_index)->getInterferenceFunctions();
    }
    else m_ifs.push_back( new InterferenceFunctionNone() );
}

double LayerStrategyBuilder::getWavelength()
{
    return mp_simulation->getWavelength();
}

FormFactorInfo *LayerStrategyBuilder::createFormFactorInfo(
        const IParticle *particle, const IMaterial *p_ambient_material, complex_t factor) const
{
    FormFactorInfo *p_result = new FormFactorInfo;
    boost::scoped_ptr<IParticle> P_particle_clone(particle->clone());
    P_particle_clone->setAmbientMaterial(*p_ambient_material);

    // formfactor
    boost::scoped_ptr<IFormFactor> P_ff_particle(P_particle_clone->createFormFactor(factor));
    IFormFactor *p_ff_framework;
    size_t n_layers = mp_layer->getNumberOfLayers();
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
    FormFactorInfo *p_result = new FormFactorInfo();
    p_result->m_abundance = m_abundance;
    p_result->m_pos_x = m_pos_x;
    p_result->m_pos_y = m_pos_y;
    p_result->mp_ff = mp_ff->clone();
    return p_result;
}
