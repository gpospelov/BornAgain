#include "IsGISAXS03.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunctionNone.h"
#include "FormFactorCylinder.h"
#include "GISASExperiment.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS03::IsGISAXS03()
    : m_name("IsGISAXS03")
    , m_description("Cylinder formfactor in BA and DWBA")
    , m_result(0)
{
    m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS03/";
}

void FunctionalTests::IsGISAXS03::runDWBA()
{      MultiLayer multi_layer;
    // ---------------------
    // building sample
    // ---------------------
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        complex_t n_particle(1.0-6e-4, 2e-8);
        ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer.addLayer(air_layer_decorator);
        multi_layer.addLayer(substrate_layer);
    // ---------------------
    // building experiment
    // ---------------------
       GISASExperiment experiment;
       experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
             100, 0.0*Units::degree, 2.0*Units::degree, true);
       experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    // ---------------------
    // running experiment and copying data
    // ---------------------
      experiment.setSample(multi_layer);
      experiment.runSimulation();
      m_result = experiment.getOutputDataClone();
      OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),m_data_path+"this_cylinder_DWBA.ima");
}

void FunctionalTests::IsGISAXS03::runBA()
{    // IsGISAXS3 functional test: cylinder in the air
    // ---------------------
    // building sample
    // ---------------------
      MultiLayer multi_layer;
      const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
      const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
      Layer air_layer;
      air_layer.setMaterial(p_air_material);
      Layer substrate_layer;
      substrate_layer.setMaterial(p_substrate_material);
      complex_t n_particle(1.0-6e-4, 2e-8);
      ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
      particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
      LayerDecorator air_layer_decorator(air_layer, particle_decoration);

      multi_layer.addLayer(air_layer_decorator);

    // ---------------------
    // building experiment
    // ---------------------
       GISASExperiment experiment;
       experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
             100, 0.0*Units::degree, 2.0*Units::degree, true);
       experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    // ---------------------
    // running experiment and copying data
    // ---------------------
       experiment.setSample(multi_layer);
       experiment.runSimulation();
       m_result = experiment.getOutputDataClone();
       OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),m_data_path+"this_cylinder_BA.ima");
}

void FunctionalTests::IsGISAXS03::runBA_Size()
{   // IsGISAXS3 functional test: cylinder in the air with size distribution
    // ---------------------
    // building sample
    // ---------------------
           MultiLayer multi_layer;
           const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
           const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
           Layer air_layer;
           air_layer.setMaterial(p_air_material);
           Layer substrate_layer;
           substrate_layer.setMaterial(p_substrate_material);

           complex_t n_particle(1.0-6e-4, 2e-8);
           ParticleDecoration particle_decoration;

           // preparing prototype of nano particle
           double radius = 5*Units::nanometer;
           double sigma = 0.2*radius;
           FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( 5*Units::nanometer, radius);
           Particle nano_particle(n_particle, p_ff_cylinder);

           // radius of nanoparticles will be sampled with gaussian probability
           int nbins(100), nfwhm(2);
           StochasticSampledParameter par(StochasticDoubleGaussian(radius, sigma), nbins, nfwhm);

           ParticleBuilder builder;
           builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
           builder.plantParticles(particle_decoration);

           particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());

           LayerDecorator air_layer_decorator(air_layer, particle_decoration);
           multi_layer.addLayer(air_layer_decorator);

    // ---------------------
    // building experiment
    // ---------------------
       GISASExperiment experiment;
       experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
             100, 0.0*Units::degree, 2.0*Units::degree, true);
       experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    // ---------------------
    // running experiment and copying data
    // --------------------
       // cylinder in BA with size distribution
       experiment.setSample(multi_layer);
       experiment.runSimulation();
       m_result = experiment.getOutputDataClone();
       OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),m_data_path+"this_cylinder_BA_size.ima");
}

int FunctionalTests::IsGISAXS03::analyseResults()
{
    const double threshold(1e-10);
    std::vector< CompareStruct > tocompare;

    tocompare.push_back( CompareStruct("isgisaxs03_reference_BA.ima.gz",      "this_cylinder_BA.ima",
                "Cylinder BA Formfactor") );
    tocompare.push_back( CompareStruct("isgisaxs03_reference_BA_size.ima.gz", "this_cylinder_BA_size.ima",
                "Cylinder BA Formfactor with size distribution") );
    tocompare.push_back( CompareStruct("isgisaxs03_reference_DWBA.ima.gz",    "this_cylinder_DWBA.ima",
                "Cylinder DWBA Formfactor") );

    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i=0; i<tocompare.size(); ++i) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(tocompare[i].isginame);
        OutputData<double> *m_result = OutputDataIOFactory::getOutputData(tocompare[i].thisname);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();
    if( diff > threshold ) status_ok=false;
    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;
}

#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS03 test;
   // test.run();
    test.runDWBA();
    test.runBA();
    test.runBA_Size();
    return test.analyseResults();
}
#endif


