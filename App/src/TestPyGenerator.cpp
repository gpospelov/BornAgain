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
#include "Samples.h"
#include "Simulation.h"
#include "TestPyGenerator.h"
#include "StochasticSampledParameter.h"
#include "StochasticGaussian.h"
#include "MyParticleBuilder.h"

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
    m_sample = new MultiLayer();

    HomogeneousMaterial air_material("Air", 0., 0.);
    HomogeneousMaterial substrate_material("Substrate", 6e-6, 2e-8);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    ParticleLayout particle_layout;
    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

    double radius1 = 1.0;
    double sigma1_ratio = 0.2;
    FormFactorCylinder ff_1(radius1,2.0);
    FormFactorBox ff_2(3.0,4.0,5.0);

    LayerRoughness roughness(1.0,0.3,5.0);
    Particle Particle1(particle_material, ff_1);
    Particle Particle2(particle_material, ff_2);

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=150;
    double sigma1 = radius1*sigma1_ratio;
    int nfwhm(3); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    StochasticDoubleGaussian sg1(radius1, sigma1);
    StochasticSampledParameter par1(sg1, nbins, nfwhm);

    // building nano particles
    MyParticleBuilder builder;
    builder.setPrototype(Particle1,"/Particle/FormFactorCylinder/radius", par1, 0.95);
    builder.plantParticles(particle_layout,visitor.getLabelSample());

    //particle_layout.addParticle(Particle1, 0.0, 0.5);
    particle_layout.addParticle(Particle2, 0.0, 0.5);
    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());
    air_layer.setLayout(particle_layout);

    m_sample->addLayer(air_layer);
    m_sample->addLayerWithTopRoughness(substrate_layer, roughness);
    m_sample->addLayer(substrate_layer);
    return m_sample;
}

