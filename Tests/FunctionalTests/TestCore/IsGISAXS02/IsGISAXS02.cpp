#include "IsGISAXS02.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunctionNone.h"
#include "LayerDecorator.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "OutputDataIOFactory.h"
#include "ParticleBuilder.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Units.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS02::IsGISAXS02()
    : m_name("IsGISAXS02")
    , m_description("Mixture cylinder particles with different size distribution")
    , m_result(0)
{ }

void FunctionalTests::IsGISAXS02::run()
{
    // ---------------------
    // building sample
    // ---------------------
    MultiLayer multi_layer;

    const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);

    ParticleDecoration particle_decoration;
    complex_t n_particle(1.0-6e-4, 2e-8);

    // preparing nano particles prototypes for seeding layer's particle_decoration
    double radius1 = 5*Units::nanometer;
    double radius2 = 10*Units::nanometer;
    double height1 = radius1;
    double height2 = radius2;

    FormFactorCylinder *p_ff_cylinder1 = new FormFactorCylinder(height1, radius1);
    Particle cylinder1(n_particle, p_ff_cylinder1 );

    FormFactorCylinder *p_ff_cylinder2 = new FormFactorCylinder(height2, radius2);
    Particle cylinder2(n_particle, p_ff_cylinder2 );

    // radius of nanoparticles will be sampled with gaussian probability
    int nbins=150;
    double sigma1 = radius1*0.2;
    double sigma2 = radius2*0.02;
    int nfwhm(3); // to have xmin=average-nfwhm*FWHM, xmax=average+nfwhm*FWHM (nfwhm = xR/2, where xR is what is defined in isgisaxs *.inp file)
    StochasticSampledParameter par1(StochasticDoubleGaussian(radius1, sigma1), nbins, nfwhm);
    StochasticSampledParameter par2(StochasticDoubleGaussian(radius2, sigma2), nbins, nfwhm);

    // building nano particles
    ParticleBuilder builder;
    builder.setPrototype(cylinder1,"/Particle/FormFactorCylinder/radius", par1, 0.95);
    builder.plantParticles(particle_decoration);

    builder.setPrototype(cylinder2,"/Particle/FormFactorCylinder/radius", par2, 0.05);
    builder.plantParticles(particle_decoration);

    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
    // making layer holding all whose nano particles
    LayerDecorator air_layer_decorator(air_layer, particle_decoration);
    multi_layer.addLayer(air_layer_decorator);

    // ---------------------
    // building simulation
    // ---------------------
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running simulation
    // ---------------------
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    // ---------------------
    // copying data
    // ---------------------
    m_result = simulation.getOutputDataClone();

}

int FunctionalTests::IsGISAXS02::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data
    std::string filename = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS02/isgisaxs02_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold ) status_ok=false;
    delete reference;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}

#ifdef STANDALONE

int main()
{
    FunctionalTests::IsGISAXS02 test;
    test.run();

    return test.analyseResults();
}
#endif
