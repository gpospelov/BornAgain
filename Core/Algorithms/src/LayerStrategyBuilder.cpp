// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/StrategyBuilder.cpp
//! @brief     Implements classes LayerDecoratorStrategyBuilder and
//!              FormFactorInfo
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerStrategyBuilder.h"
#include "Layer.h"
#include "Simulation.h"
#include "IDoubleToComplexFunction.h"
#include "MagneticCoefficientsMap.h"
#include "InterferenceFunctions.h"
#include "InterferenceFunctionStrategies.h"
#include "FormFactors.h"
#include "PositionParticleInfo.h"

#include <cmath>
#include <boost/scoped_ptr.hpp>

LayerStrategyBuilder::LayerStrategyBuilder(
        const Layer& decorated_layer, const Simulation& simulation,
        const SimulationParameters& sim_params)
: mp_layer(decorated_layer.clone())
, mp_simulation(simulation.clone())
, m_sim_params(sim_params)
, mp_RT_function(0)
, mp_magnetic_coeff_map(0)
{
    assert(mp_layer->getDecoration());
}

LayerStrategyBuilder::~LayerStrategyBuilder()
{
    delete mp_layer;
    delete mp_simulation;
    delete mp_RT_function;
    delete mp_magnetic_coeff_map;
}


void LayerStrategyBuilder::setRTInfo(
        const IDoubleToPairOfComplexMap& rt_map)
{
    if (mp_RT_function != &rt_map) {
        delete mp_RT_function;
        mp_RT_function = rt_map.clone();
    }
    delete mp_magnetic_coeff_map;
    mp_magnetic_coeff_map = 0;
}

void LayerStrategyBuilder::setRTInfo(
        const MagneticCoefficientsMap& magnetic_coeff_map)
{
    if (mp_magnetic_coeff_map != &magnetic_coeff_map) {
        delete mp_magnetic_coeff_map;
        mp_magnetic_coeff_map = magnetic_coeff_map.clone();
    }
    delete mp_RT_function;
    mp_RT_function = 0;
}

IInterferenceFunctionStrategy* LayerStrategyBuilder::createStrategy()
{
    collectFormFactorInfos();
    collectInterferenceFunctions();
    size_t n_ifs = m_ifs.size();
    IInterferenceFunctionStrategy *p_result(0);
    switch (m_sim_params.me_if_approx)
    {
    case SimulationParameters::DA:
        p_result = new DecouplingApproximationStrategy(m_sim_params);
        break;
    case SimulationParameters::LMA:
        p_result = new LocalMonodisperseApproximationStrategy(m_sim_params);
        break;
    case SimulationParameters::SSCA:
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
    case SimulationParameters::ISGISAXSMOR:
        p_result = new IsGISAXSMorphologyFileStrategy(m_sim_params);
        break;
    default:
        throw Exceptions::ClassInitializationException(
                "Unknown interference function approximation");
    }
    if (!p_result) {
        throw Exceptions::ClassInitializationException(
                "Could not create appropriate strategy");
    }
    p_result->init(m_ff_infos, m_ifs);
    return p_result;
}

void LayerStrategyBuilder::collectFormFactorInfos()
{
    assert(mp_layer->getDecoration());
    m_ff_infos.clear();
    const IDecoration *p_decoration = mp_layer->getDecoration();
    const IMaterial *p_layer_material = mp_layer->getMaterial();
    double wavelength = getWavelength();
    complex_t wavevector_scattering_factor = M_PI/wavelength/wavelength;
    size_t number_of_particles = p_decoration->getNumberOfParticles();
    for (size_t particle_index =
             0; particle_index<number_of_particles; ++particle_index) {
        const ParticleInfo *p_particle_info =
            p_decoration->getParticleInfo(particle_index);
        FormFactorInfo *p_ff_info;
        if (mp_magnetic_coeff_map) {
            p_ff_info = createFormFactorInfoPol(p_particle_info,
                    p_layer_material, wavevector_scattering_factor);
        }
        else {
            p_ff_info = createFormFactorInfo(p_particle_info, p_layer_material,
                    wavevector_scattering_factor);
        }
        p_ff_info->m_abundance =
            p_decoration->getAbundanceFractionOfParticle(particle_index);
        m_ff_infos.push_back(p_ff_info);
    }
    return;
}

void LayerStrategyBuilder::collectInterferenceFunctions()
{
    assert(mp_layer->getDecoration());
    m_ifs.clear();
    if (mp_layer->getDecoration()->getNumberOfInterferenceFunctions()) {
        m_ifs = mp_layer->getDecoration()->getInterferenceFunctions();
    }
    else m_ifs.push_back(new InterferenceFunctionNone);
}

double LayerStrategyBuilder::getWavelength()
{
    cvector_t ki = mp_simulation->getInstrument().getBeam().getCentralK();
    kvector_t ki_real(ki.x().real(), ki.y().real(), ki.z().real());
    return 2*M_PI/ki_real.mag();
}

FormFactorInfo *LayerStrategyBuilder::createFormFactorInfo(
        const ParticleInfo *p_particle_info,
        const IMaterial *p_ambient_material,
        complex_t factor) const
{
    FormFactorInfo *p_result = new FormFactorInfo;
    boost::scoped_ptr<Particle> P_particle_clone(p_particle_info->getParticle()->clone());
    const Geometry::PTransform3D transform =
        p_particle_info->getPTransform3D();

    // formfactor
    P_particle_clone->setAmbientMaterial(p_ambient_material);
    IFormFactor *ff_particle = P_particle_clone->createFormFactor();
    IFormFactor *ff_transformed(ff_particle);
    if(transform) {
        ff_transformed = new FormFactorDecoratorTransformation(ff_particle, transform);
    }
    IFormFactor *p_ff_framework(ff_transformed);
    switch (m_sim_params.me_framework)
    {
    case SimulationParameters::BA:    // Born Approximation
        break;
    case SimulationParameters::DWBA:  // Distorted Wave Born Approximation
    {
        if (mp_RT_function==0) {
            throw Exceptions::ClassInitializationException(
                    "R and T coefficients are necessary for DWBA");
        }
        double depth = p_particle_info->getDepth();
        FormFactorDWBAConstZ *p_dwba_ff =
            new FormFactorDWBAConstZ(ff_transformed, depth);
        p_dwba_ff->setRTInfo(*mp_RT_function);
        p_ff_framework = p_dwba_ff;
        break;
    }
    default:
        throw Exceptions::RuntimeErrorException("Framework must be BA or DWBA");
    }
    IFormFactor *p_ff(p_ff_framework);
    if ( factor != complex_t(1.0, 0.0) ) {
        p_ff = new FormFactorDecoratorFactor(p_ff_framework, factor);
    }
    p_result->mp_ff = p_ff;
    // Other info (position and abundance
    const PositionParticleInfo *p_pos_particle_info =
        dynamic_cast<const PositionParticleInfo *>(p_particle_info);
    if (p_pos_particle_info) {
        kvector_t position = p_pos_particle_info->getPosition();
        p_result->m_pos_x = position.x();
        p_result->m_pos_y = position.y();
    }
    p_result->m_abundance = p_particle_info->getAbundance();
    return p_result;
}

FormFactorInfo* LayerStrategyBuilder::createFormFactorInfoPol(
        const ParticleInfo* p_particle_info,
        const IMaterial* p_ambient_material, complex_t factor) const
{
    FormFactorInfo *p_result = new FormFactorInfo;
    boost::scoped_ptr<Particle> P_particle_clone(p_particle_info->
            getParticle()->clone());
    const Geometry::PTransform3D transform = p_particle_info->getPTransform3D();
    const IMaterial *p_material = P_particle_clone->getMaterial();

    // formfactor
    IFormFactor *ff_particle = P_particle_clone->getSimpleFormFactor()->clone();
    IFormFactor *ff_particle_factor(ff_particle);
    if ( factor!=complex_t(1.0,0.0) ) {
        ff_particle_factor = new FormFactorDecoratorFactor(ff_particle, factor);
    }
    IFormFactor *ff_transformed(ff_particle_factor);
    if(transform) {
        ff_transformed = new FormFactorDecoratorTransformation(
                ff_particle_factor, transform);
    }
    IFormFactor *p_ff_framework(ff_transformed);
    switch (m_sim_params.me_framework)
    {
    case SimulationParameters::BA:    // Born Approximation
    {
        if (!mp_magnetic_coeff_map) {
            throw Exceptions::ClassInitializationException(
                    "Magnetic coefficients are necessary for DWBA");
        }
        FormFactorPol *p_ff_pol = new FormFactorPol(ff_transformed);
        p_ff_pol->setRTInfo(*mp_magnetic_coeff_map);
        p_ff_pol->setMaterial(p_material);
        p_ff_pol->setAmbientMaterial(p_ambient_material);
        p_ff_framework = p_ff_pol;
        break;
    }
    case SimulationParameters::DWBA:  // Distorted Wave Born Approximation
    {
        if (!mp_magnetic_coeff_map) {
            throw Exceptions::ClassInitializationException(
                    "Magnetic coefficients are necessary for DWBA");
        }
        FormFactorDWBAPol *p_dwba_ff_pol = new FormFactorDWBAPol(ff_transformed);
        p_dwba_ff_pol->setRTInfo(*mp_magnetic_coeff_map);
        p_dwba_ff_pol->setMaterial(p_material);
        p_dwba_ff_pol->setAmbientMaterial(p_ambient_material);
        p_ff_framework = p_dwba_ff_pol;
        break;
    }
    default:
        throw Exceptions::RuntimeErrorException("Framework must be BA or DWBA");
    }
    p_result->mp_ff = p_ff_framework;
    // Other info (position and abundance)
    const PositionParticleInfo *p_pos_particle_info =
        dynamic_cast<const PositionParticleInfo *>(p_particle_info);
    if (p_pos_particle_info) {
        kvector_t position = p_pos_particle_info->getPosition();
        p_result->m_pos_x = position.x();
        p_result->m_pos_y = position.y();
    }
    p_result->m_abundance = p_particle_info->getAbundance();
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

