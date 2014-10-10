#include "SampleBuilder.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "InterferenceFunctions.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "Materials.h"
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
    , m_prism3_length(10.0*Units::nanometer)
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
    registerParameter("prism3_length", &m_prism3_length);
    registerParameter("prism3_height", &m_prism3_height);
    registerParameter("cylinder_ratio", &m_cylinder_ratio);
}

// build sample from registered parameters
ISample *SampleBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    complex_t n_particle(1.0-6e-4, 2e-8);
    HomogeneousMaterial particle_material("Particle", n_particle);

    FormFactorCylinder ff_cylinder(m_cylinder_radius, m_cylinder_height);
    FormFactorPrism3 ff_prism3(m_prism3_length, m_prism3_height);

    particle_layout.addParticle(new Particle(particle_material, ff_cylinder),0.0, m_cylinder_ratio);
    particle_layout.addParticle(new Particle(particle_material, ff_prism3), 0.0, 1.0 - m_cylinder_ratio);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

