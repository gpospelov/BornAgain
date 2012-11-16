#include "LayerDecoratorDWBASimulation.h"
#include "LayerDecorator.h"
#include "FormFactorDWBAConstZ.h"
#include "FormFactorDecoratorFactor.h"
#include "Transform3D.h"
#include "FormFactorDecoratorTransformation.h"

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

void LayerDecoratorDWBASimulation::init(const Experiment& experiment)
{
    DWBASimulation::init(experiment);
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->init(experiment);
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
    std::vector<IFormFactor *> form_factors = createDWBAFormFactors();
    IInterferenceFunctionStrategy *p_strategy = mp_layer_decorator->createStrategy(form_factors);
    for (size_t i=0; i<form_factors.size(); ++i) {
        delete form_factors[i];
    }
    return p_strategy;
}

std::vector<IFormFactor *> LayerDecoratorDWBASimulation::createDWBAFormFactors() const
{
    std::vector<IFormFactor *> result;
    const ParticleDecoration *p_decoration = mp_layer_decorator->getDecoration();
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

void LayerDecoratorDWBASimulation::calculateCoherentIntensity(IInterferenceFunctionStrategy *p_strategy)
{
    //std::cout << "Calculating coherent scattering..." << std::endl;
    double wavelength = getWaveLength();
    double total_surface_density = mp_layer_decorator->getTotalParticleSurfaceDensity();

    DWBASimulation::iterator it_intensity = begin();
    while ( it_intensity != end() )
    {
        double phi_f = getDWBAIntensity().getValueOfAxis<double>("phi_f", it_intensity.getIndex());
        double alpha_f = getDWBAIntensity().getValueOfAxis<double>("alpha_f", it_intensity.getIndex());
        if (alpha_f<0) {
            ++it_intensity;
            continue;
        }
        cvector_t k_f;
        k_f.setLambdaAlphaPhi(wavelength, alpha_f, phi_f);
        k_f.setZ(mp_kz_function->evaluate(alpha_f));
        *it_intensity = p_strategy->evaluate(m_ki, k_f, -m_alpha_i, alpha_f)*total_surface_density;
        ++it_intensity;
    }
}

void LayerDecoratorDWBASimulation::calculateInCoherentIntensity()
{
    //std::cout << "Calculating incoherent scattering..." << std::endl;
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->setReflectionTransmissionFunction( *mp_RT_function);
        mp_diffuseDWBA->setKzFunction( *mp_kz_function);
        mp_diffuseDWBA->setThreadInfo(m_thread_info);
        mp_diffuseDWBA->run();
        addDWBAIntensity( mp_diffuseDWBA->getDWBAIntensity() );
    }
}
