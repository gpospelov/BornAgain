#include <iostream>
#include <set>
#include <typeinfo>
#include <exception>
#include "FormFactors.h"
#include "ICompositeSample.h"
#include "INamed.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "InterferenceFunctionNone.h"
#include "ISample.h"
#include "LabelSample.h"
#include "Materials.h"
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
   // ml->printSampleTree();

    std::cout << "\n\n\n\n";

    VisitSampleTree(*ml, visitor);
    visitor.genPyScript();
}

MultiLayer *TestPyGenerator::makeSample()
{
    MultiLayer *multi_layer = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0.0, 0.0);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    InterferenceFunction1DParaCrystal *p_interference_function =
            new InterferenceFunction1DParaCrystal(20.0, 1000.0);
    FTDistribution1DGauss pdf(7.0);
    p_interference_function->setProbabilityDistribution(pdf);
    FormFactorCylinder ff_cylinder(5.0, 10.0);

    ParticleLayout particle_layout( new Particle(
            particle_material, ff_cylinder ) );
    particle_layout.addInterferenceFunction(p_interference_function);

    air_layer.setLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}

