#include <iostream>
#include <set>
#include <typeinfo>
#include <exception>
#include "FormFactors.h"
#include "ICompositeSample.h"
#include "INamed.h"
#include "IMaterial.h"
#include "InterferenceFunctionNone.h"
#include "ISample.h"
#include "LabelSample.h"
#include "Materials.h"
#include "PyGenVisitor.h"
#include "Samples.h"
#include "Simulation.h"
#include "TestPyGenerator.h"

TestPyGenerator::TestPyGenerator()
{

}

void TestPyGenerator::execute()
{
    std::cout << "\n\n\n\n";

    //Simulation *sm = makeSimulation();
    MultiLayer *ml = makeSample();
    ml->printSampleTree();

    std::cout << "\n\n\n\n";
    PyGenVisitor visitor;

    VisitSampleTree(*ml, visitor);
    visitor.genPyScript();
}

/*  # defining materials
    m_air = HomogeneousMaterial("Air", 0.0, 0.0)
    m_substrate = HomogeneousMaterial("Substrate", 6e-6, 2e-8)
    m_particle = HomogeneousMaterial("Particle", 6e-4, 2e-8)

    # collection of particles
    cylinder_ff = FormFactorCylinder(5*nanometer, 5*nanometer)
    cylinder = Particle(m_particle, cylinder_ff)
    prism_ff = FormFactorPrism3(10*nanometer, 5*nanometer)
    prism = Particle(m_particle, prism_ff)
    particle_layout = ParticleLayout()
    particle_layout.addParticle(cylinder, 0.0, 0.5)
    particle_layout.addParticle(prism, 0.0, 0.5)
    interference = InterferenceFunctionNone()
    particle_layout.addInterferenceFunction(interference)

    # air layer with particles and substrate form multi layer
    air_layer = Layer(m_air)
    air_layer.setLayout(particle_layout)
    substrate_layer = Layer(m_substrate, 0)
    multi_layer = MultiLayer()
    multi_layer.addLayer(air_layer)
    multi_layer.addLayer(substrate_layer)
    return multi_layer
*/

MultiLayer *TestPyGenerator::makeSample()
{
    m_sample = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0., 0.);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    FormFactorCylinder ff_1(5.0,5.0);
    FormFactorBox ff_2(10.0,15.0,20.0);

    LayerRoughness roughness(1.0,0.3,5.0);
    Particle Particle1(particle_material, ff_1);
    Particle Particle2(particle_material, ff_2);

    particle_layout.addParticle(Particle1, 0.0, 0.5);
    particle_layout.addParticle(Particle2, 0.0, 0.5);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());

    air_layer.setLayout(particle_layout);

    m_sample->addLayerWithTopRoughness(substrate_layer, roughness);
    m_sample->addLayer(air_layer);
    m_sample->addLayerWithTopRoughness(substrate_layer, roughness);
    m_sample->addLayer(substrate_layer);
    m_sample->addLayerWithTopRoughness(substrate_layer, roughness);
    return m_sample;
}
