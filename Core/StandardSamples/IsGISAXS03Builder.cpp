#include "IsGISAXS03Builder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "FormFactorCylinder.h"
#include "FormFactorPrism3.h"
#include "Units.h"
#include "InterferenceFunctionNone.h"
#include "StochasticSampledParameter.h"
#include "StochasticGaussian.h"
#include "ParticleBuilder.h"


// -----------------------------------------------------------------------------
// Cylinders in DWBA
// -----------------------------------------------------------------------------
IsGISAXS03DWBABuilder::IsGISAXS03DWBABuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS03DWBABuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}


ISample *IsGISAXS03DWBABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(m_height, m_radius)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// Cylinders in BA
// -----------------------------------------------------------------------------
IsGISAXS03BABuilder::IsGISAXS03BABuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS03BABuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}


ISample *IsGISAXS03BABuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(m_height, m_radius)));
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);
    multi_layer->addLayer(air_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
// Cylinders in BA with size distribution
// -----------------------------------------------------------------------------
IsGISAXS03BASizeBuilder::IsGISAXS03BASizeBuilder()
    : m_height(5*Units::nanometer)
    , m_radius(5*Units::nanometer)
{
    init_parameters();
}


void IsGISAXS03BASizeBuilder::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter("height", &m_height);
}


ISample *IsGISAXS03BASizeBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);
    complex_t n_particle(1.0-6e-4, 2e-8);
    ParticleDecoration particle_decoration;
    // preparing prototype of nano particle
    double sigma = 0.2*m_radius;
    FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( m_height, m_radius);
    Particle nano_particle(n_particle, p_ff_cylinder);
    // radius of nanoparticles will be sampled with gaussian probability
    int nbins(100), nfwhm(2);
    StochasticDoubleGaussian double_gaussian(m_radius, sigma);
    StochasticSampledParameter par(double_gaussian, nbins, nfwhm);
    ParticleBuilder builder;
    builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
    builder.plantParticles(particle_decoration);
    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);

    return multi_layer;
}
