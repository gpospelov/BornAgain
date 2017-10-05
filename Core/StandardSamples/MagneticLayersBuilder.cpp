#include "MagneticLayersBuilder.h"
#include "BornAgainNamespace.h"
#include "FormFactorFullSphere.h"
#include "HomogeneousMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"


MagneticSubstrateZeroFieldBuilder::MagneticSubstrateZeroFieldBuilder()
    : m_sphere_radius(5*Units::nanometer)
{}

MultiLayer*MagneticSubstrateZeroFieldBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t substr_field(0.0, 0.0, 0.0);
    kvector_t particle_field(0.1, 0.0, 0.0);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 7e-6, 2e-8, substr_field);
    HomogeneousMaterial particle_material("MagParticle", 6e-4, 2e-8, particle_field);

    ParticleLayout particle_layout;
    kvector_t position(0.0, 0.0, -10.0*Units::nanometer);
    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    particle_layout.addParticle(particle, 1.0, position);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

MagneticRotationBuilder::MagneticRotationBuilder()
    : m_sphere_radius(5*Units::nanometer)
{}

MultiLayer* MagneticRotationBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t substr_field = kvector_t(0.0, 1e6, 0.0);
    kvector_t particle_field(1e6, 0.0, 0.0);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 7e-6, 2e-8, substr_field);
    HomogeneousMaterial particle_material("MagParticle", 6e-4, 2e-8, particle_field);

    ParticleLayout particle_layout;
    kvector_t position(0.0, 0.0, -10.0*Units::nanometer);
    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    RotationZ rot_z(90*Units::deg);
    particle_layout.addParticle(particle, 1.0, position, rot_z);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
