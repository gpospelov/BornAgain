// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerDecoratorDWBASimulation.cpp
//! @brief     Implements class LayerDecoratorDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "LayerDecoratorDWBASimulation.h"
#include "LayerDecorator.h"
#include "FormFactors.h"
#include "MessageService.h"

LayerDecoratorDWBASimulation::LayerDecoratorDWBASimulation(
        const LayerDecorator *p_layer_decorator)
{
    mp_layer_decorator = p_layer_decorator->clone();
    mp_diffuseDWBA = mp_layer_decorator->createDiffuseDWBASimulation();
}

LayerDecoratorDWBASimulation::~LayerDecoratorDWBASimulation()
{
    delete mp_layer_decorator;
    delete mp_diffuseDWBA;
}

void LayerDecoratorDWBASimulation::init(const Simulation& simulation)
{
    DWBASimulation::init(simulation);
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->init(simulation);
    }
}

void LayerDecoratorDWBASimulation::run()
{
    IInterferenceFunctionStrategy *p_strategy = createAndInitStrategy();

    calculateCoherentIntensity(p_strategy);
    calculateInCoherentIntensity();

    delete p_strategy;
}

IInterferenceFunctionStrategy *LayerDecoratorDWBASimulation::createAndInitStrategy() const
{
    LayerDecoratorStrategyBuilder builder(*mp_layer_decorator, *mp_simulation, m_sim_params);
    if (mp_RT_function) builder.setReflectionTransmissionFunction(*mp_RT_function);
    IInterferenceFunctionStrategy *p_strategy = builder.createStrategy();
    return p_strategy;
}

std::vector<IFormFactor *> LayerDecoratorDWBASimulation::createDWBAFormFactors() const
{
    std::vector<IFormFactor *> result;
    const IDecoration *p_decoration = mp_layer_decorator->getDecoration();
    complex_t n_layer = mp_layer_decorator->getRefractiveIndex();
    size_t number_of_particles = p_decoration->getNumberOfParticles();
    for (size_t particle_index=0; particle_index<number_of_particles; ++particle_index) {
        Particle *p_particle = p_decoration->getParticleInfo(particle_index)->getParticle()->clone();
        double depth = p_decoration->getParticleInfo(particle_index)->getDepth();
        const Geometry::Transform3D *transform = p_decoration->getParticleInfo(particle_index)->getTransform3D();

        p_particle->setAmbientRefractiveIndex(n_layer);
        complex_t wavevector_scattering_factor = M_PI/getWaveLength()/getWaveLength();

        IFormFactor *ff_particle = p_particle->createFormFactor();
        IFormFactor  *ff_transformed(0);
        if(transform) {
            ff_transformed = new FormFactorDecoratorTransformation(ff_particle, new Geometry::Transform3D(*transform));
        } else{
            ff_transformed = ff_particle;
        }

        FormFactorDWBAConstZ dwba_z(ff_transformed, depth);
        dwba_z.setReflectionTransmissionFunction(*mp_RT_function);
        FormFactorDecoratorFactor *p_ff = new FormFactorDecoratorFactor(dwba_z.clone(), wavevector_scattering_factor);
        result.push_back(p_ff);
        delete p_particle;
    }
    return result;
}

void LayerDecoratorDWBASimulation::calculateCoherentIntensity(const IInterferenceFunctionStrategy *p_strategy)
{
    msglog(MSG::DEBUG) << "Calculating coherent scattering...";
    double wavelength = getWaveLength();
    double total_surface_density = mp_layer_decorator->getTotalParticleSurfaceDensity();

    cvector_t k_ij = m_ki;
    k_ij.setZ(-mp_kz_function->evaluate(-m_alpha_i));

    DWBASimulation::iterator it_intensity = begin();
    while ( it_intensity != end() )
    {
        Bin1D phi_bin = getDWBAIntensity().getBinOfAxis(
            "phi_f", it_intensity.getIndex());
        Bin1D alpha_bin = getDWBAIntensity().getBinOfAxis(
            "alpha_f", it_intensity.getIndex());
        double alpha_f = alpha_bin.getMidPoint();
        if (std::abs(mp_RT_function->evaluate(alpha_f).first)!=0.0 && alpha_f<0) {
            ++it_intensity;
            continue;
        }
        Bin1DCVector k_f_bin = getKfBin(wavelength, alpha_bin, phi_bin);
        *it_intensity = p_strategy->evaluate(k_ij, k_f_bin, -m_alpha_i, alpha_f)*total_surface_density;
        ++it_intensity;
    }
}

void LayerDecoratorDWBASimulation::calculateInCoherentIntensity()
{
    msglog(MSG::DEBUG) << "Calculating incoherent scattering...";
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->setReflectionTransmissionFunction( *mp_RT_function);
        mp_diffuseDWBA->setKzFunction( *mp_kz_function);
        mp_diffuseDWBA->setThreadInfo(m_thread_info);
        mp_diffuseDWBA->run();
        addDWBAIntensity( mp_diffuseDWBA->getDWBAIntensity() );
    }
}
