#include "MagneticLayersBuilder.h"
#include "FormFactorFullSphere.h"
#include "HomogeneousMagneticMaterial.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "RealParameter.h"
#include "Units.h"


MagneticSubstrateZeroFieldBuilder::MagneticSubstrateZeroFieldBuilder()
    : m_sphere_radius(5*Units::nanometer)
{
    init_parameters();
}

MultiLayer*MagneticSubstrateZeroFieldBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t substr_field(0.0, 0.0, 0.0);
    kvector_t particle_field(0.1, 0.0, 0.0);
    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMagneticMaterial substrate_material("Substrate", 7e-6, 2e-8, substr_field);
    HomogeneousMagneticMaterial particle_material("MagParticle", 6e-4, 2e-8, particle_field);

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

void MagneticSubstrateZeroFieldBuilder::init_parameters()
{
    registerParameter("sphere_radius", &m_sphere_radius).setUnit("nm").setNonnegative();
}
