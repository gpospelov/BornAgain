#include "StrategyBuilder.h"

#include <cmath>

LayerDecoratorStrategyBuilder::LayerDecoratorStrategyBuilder(
        const LayerDecorator &decorated_layer, const Experiment &experiment,
        const SimulationParameters &sim_params)
: mp_layer_decorator(decorated_layer.clone())
, mp_experiment(experiment.clone())
, m_sim_params(sim_params)
, mp_RT_function(0)
{
}

LayerDecoratorStrategyBuilder::~LayerDecoratorStrategyBuilder()
{
    delete mp_layer_decorator;
    delete mp_experiment;
    delete mp_RT_function;
}

void LayerDecoratorStrategyBuilder::setReflectionTransmissionFunction(
        const IDoubleToPairOfComplexMap& rt_map)
{
    if (mp_RT_function != &rt_map) {
        delete mp_RT_function;
        mp_RT_function = rt_map.clone();
    }
}

IInterferenceFunctionStrategy* LayerDecoratorStrategyBuilder::createStrategy()
{
    collectFormFactorInfos();
    collectInterferenceFunctions();
    size_t n_particles = m_ff_infos.size();
    size_t n_ifs = m_ifs.size();
    IInterferenceFunctionStrategy *p_result(0);
    switch (m_sim_params.me_if_approx)
    {
    case SimulationParameters::DA:
        p_result = new DecouplingApproximationStrategy();
        break;
    case SimulationParameters::LMA:
        p_result = new LocalMonodisperseApproximationStrategy();
        break;
    case SimulationParameters::SSCA:
        if (n_ifs<2) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires an interference function");
        }
        double kappa = m_ifs[0]->getKappa();
        if (kappa<=0.0) {
            throw Exceptions::ClassInitializationException(
                    "SSCA requires a strictly positive coupling value");
        }
        p_result = new SizeSpacingCorrelationApproximationStrategy(kappa);
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

void LayerDecoratorStrategyBuilder::collectFormFactorInfos()
{
    m_ff_infos.clear();
    const IDecoration *p_decoration = mp_layer_decorator->getDecoration();
    complex_t n_layer = mp_layer_decorator->getRefractiveIndex();
    double wavelength = getWavelength();
    complex_t wavevector_scattering_factor = M_PI/wavelength/wavelength;
    size_t number_of_particles = p_decoration->getNumberOfParticles();
    for (size_t particle_index=0; particle_index<number_of_particles; ++particle_index) {
        const ParticleInfo *p_particle_info = p_decoration->getParticleInfo(particle_index);
        FormFactorInfo *p_ff_info = createFormFactorInfo(p_particle_info, n_layer,
                wavevector_scattering_factor);
        m_ff_infos.push_back(p_ff_info);
    }
    return;
}

void LayerDecoratorStrategyBuilder::collectInterferenceFunctions()
{
    m_ifs.clear();
    if (mp_layer_decorator->getDecoration()->getNumberOfInterferenceFunctions()) {
        m_ifs = mp_layer_decorator->getDecoration()->getInterferenceFunctions();
    }
    else m_ifs.push_back(new InterferenceFunctionNone);
}

double LayerDecoratorStrategyBuilder::getWavelength()
{
    cvector_t ki = mp_experiment->getBeam().getCentralK();
    kvector_t ki_real(ki.x().real(), ki.y().real(), ki.z().real());
    return 2.0*M_PI/ki_real.mag();
}

FormFactorInfo *LayerDecoratorStrategyBuilder::createFormFactorInfo(
        const ParticleInfo *p_particle_info, complex_t n_ambient_refractive_index,
        complex_t factor) const
{
    FormFactorInfo *p_result = new FormFactorInfo;
    Particle *p_particle_clone = p_particle_info->getParticle()->clone();
    const Geometry::Transform3D *p_transform = p_particle_info->getTransform3D();

    // formfactor
    p_particle_clone->setAmbientRefractiveIndex(n_ambient_refractive_index);
    IFormFactor *ff_particle = p_particle_clone->createFormFactor();
    delete p_particle_clone;
    IFormFactor *ff_transformed(0);
    if(p_transform) {
        ff_transformed = new FormFactorDecoratorTransformation(ff_particle, new Geometry::Transform3D(*p_transform));
    } else{
        ff_transformed = ff_particle;
    }
    IFormFactor *p_ff_framework(0);
    switch (m_sim_params.me_framework)
    {
    case SimulationParameters::BA:    // Born Approximation
        p_ff_framework = ff_transformed;
        break;
    case SimulationParameters::DWBA:  // Distorted Wave Born Approximation
        if (mp_RT_function==0) {
            throw Exceptions::ClassInitializationException(
                    "R and T coefficients are necessary for DWBA");
        }
        double depth = p_particle_info->getDepth();
        FormFactorDWBAConstZ *p_dwba_ff = new FormFactorDWBAConstZ(ff_transformed, depth);
        p_dwba_ff->setReflectionTransmissionFunction(*mp_RT_function);
        p_ff_framework = p_dwba_ff;
        break;
    default:
        throw Exceptions::RuntimeErrorException("Framework must be BA or DWBA");
    }
    FormFactorDecoratorFactor *p_ff = new FormFactorDecoratorFactor(p_ff_framework, factor);
    p_result->mp_ff = p_ff;
    // Other info (position and abundance
    const PositionParticleInfo *p_pos_particle_info = dynamic_cast<const PositionParticleInfo *>(p_particle_info);
    if (p_pos_particle_info) {
        kvector_t position = p_pos_particle_info->getPosition();
        p_result->m_pos_x = position.x();
        p_result->m_pos_y = position.y();
    }
    p_result->m_abundance = p_particle_info->getAbundance();
    return p_result;
}

FormFactorInfo::FormFactorInfo()
: mp_ff(0)
, m_pos_x(0.0)
, m_pos_y(0.0)
, m_abundance(0.0)
{
}

FormFactorInfo::~FormFactorInfo()
{
    delete mp_ff;
}

FormFactorInfo* FormFactorInfo::clone() const
{
    FormFactorInfo *p_result = new FormFactorInfo();
    p_result->m_abundance = m_abundance;
    p_result->m_pos_x = m_pos_x;
    p_result->m_pos_y = m_pos_y;
    p_result->mp_ff = mp_ff->clone();
    return p_result;
}
