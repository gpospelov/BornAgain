#include "SampleBuilder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "InterferenceFunctions.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "MaterialManager.h"
#include "MinimizerFactory.h"
#include "FormFactorPrism3.h"
#include "MathFunctions.h"
#include "Utils.h"

using namespace FunctionalTests;

// ----------------------------------------------------------------------------
// Sample builder to build mixture of cylinders and prisms on top of substrate
// 5 parameters
// ----------------------------------------------------------------------------
SampleBuilder::SampleBuilder()
    : m_cylinder_height(5.0*Units::nanometer)
    , m_cylinder_radius(5.0*Units::nanometer)
    , m_prism3_half_side(5.0*Units::nanometer)
    , m_prism3_height(5.0*Units::nanometer)
    , m_cylinder_ratio(0.2)
{
    init_parameters();
}

// registering parameters in parameter pool
void SampleBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("cylinder_height", &m_cylinder_height);
    registerParameter("cylinder_radius", &m_cylinder_radius);
    registerParameter("prism3_half_side", &m_prism3_half_side);
    registerParameter("prism3_height", &m_prism3_height);
    registerParameter("cylinder_ratio", &m_cylinder_ratio);
}

// build sample from registered parameters
ISample *SampleBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();
    const IMaterial *air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleDecoration particle_decoration;
    complex_t n_particle(1.0-6e-4, 2e-8);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(m_cylinder_height, m_cylinder_radius)),0.0, m_cylinder_ratio);
    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(m_prism3_height, m_prism3_half_side)), 0.0, 1.0 - m_cylinder_ratio);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

