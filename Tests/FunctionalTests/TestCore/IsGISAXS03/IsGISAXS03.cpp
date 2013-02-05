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
{ }

void FunctionalTests::IsGISAXS03::run()
{
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

        MultiLayer multi_layer_CylinderDWBA;
        multi_layer_CylinderDWBA.addLayer(air_layer_decorator);
        multi_layer_CylinderDWBA.addLayer(substrate_layer);

    // IsGISAXS3 functional test: cylinder in the air

     //   MultiLayer multi_layer_CylinderBA;
     //   multi_layer_CylinderBA.addLayer(air_layer_decorator);

    // IsGISAXS3 functional test: cylinder in the air with size distribution

      //  MultiLayer multi_layer_CylinderBA_size;
     //   ParticleDecoration particle_decoration_CylinderBA_size;

        // preparing prototype of nano particle
      //  double radius = 5*Units::nanometer;
      //  double sigma = 0.2*radius;
      //  FormFactorCylinder *p_ff_cylinder = new FormFactorCylinder( 5*Units::nanometer, radius);
      //  Particle nano_particle(n_particle, p_ff_cylinder);

        // radius of nanoparticles will be sampled with gaussian probability
      //  int nbins(100), nfwhm(2);
      //  StochasticSampledParameter par(StochasticDoubleGaussian(radius, sigma), nbins, nfwhm);

      //  ParticleBuilder builder;
     //   builder.setPrototype(nano_particle,"/Particle/FormFactorCylinder/radius", par);
     //   builder.plantParticles(particle_decoration_CylinderBA_size);

      //  particle_decoration_CylinderBA_size.addInterferenceFunction(new InterferenceFunctionNone());

     //   LayerDecorator air_layer_decorator_CylinderBA_size(air_layer, particle_decoration_CylinderBA_size);
     //   multi_layer_CylinderBA_size.addLayer(air_layer_decorator_CylinderBA_size);

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
    // cylinder DWBA
    experiment.setSample(multi_layer_CylinderDWBA);
    experiment.runSimulation();
    m_result = experiment.getOutputDataClone();
  // OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_cylinder_DWBA.ima");

    // cylinder in the air
  //  experiment.setSample(multi_layer_CylinderBA);
   // experiment.runSimulation();
   // m_result = experiment.getOutputDataClone();
  //  OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_cylinder_BA.ima");


    // cylinder in BA with size distribution
   // experiment.setSample(multi_layer_CylinderBA_size);
   // experiment.runSimulation();
   // m_result = experiment.getOutputDataClone();
  //  OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_cylinder_BA_size.ima");

}
int FunctionalTests::IsGISAXS03::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data

   // std::string filenameBA = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS03/isgi_cylinder_BA.ima.gz";
   // OutputData<double > *reference = OutputDataIOFactory::getOutputData(filenameBA);
  //  OutputData<double > *referenceBA = OutputDataIOFactory::getOutputData(filenameBA);
  //  OutputData<double > *m_resultBA = OutputDataIOFactory::getOutputData("this_cylinder_BA.ima");

  //  std::string filenameBA_size = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS03/isgi_cylinder_BA_size.ima.gz";
  //  OutputData<double > *reference = OutputDataIOFactory::getOutputData(filenameBA_size);
  //  OutputData<double > *referenceBA_size = OutputDataIOFactory::getOutputData(filenameBA_size);
  //  OutputData<double > *m_resultBA_size = OutputDataIOFactory::getOutputData("this_cylinder_BA_size.ima");

    std::string filenameDWBA = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS03/isgi_cylinder_DWBA.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::getOutputData(filenameDWBA);
  //  OutputData<double > *referenceDWBA = OutputDataIOFactory::getOutputData(filenameDWBA);
   // OutputData<double > *m_resultDWBA = OutputDataIOFactory::getOutputData("this_cylinder_DWBA.ima");

    ////////////////////////
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

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;

  /////////////////////////
    // calculating average relative difference

   // bool status_ok(true);

    // BA
  //  *m_resultBA -= *referenceBA;
  //  *m_resultBA /= *referenceBA;
  //  double diffBA(0);
  //  for(OutputData<double>::const_iterator it=m_resultBA->begin(); it!=m_resultBA->end(); ++it) {
  //      diffBA+= std::fabs(*it);
  //  }
  //  diffBA /= m_resultBA->getAllocatedSize();

   //bool status_ok_BA(true);
   //if( diffBA > threshold ) {status_ok_BA=false;
   //                          status_ok=false;}
  // std::cout << "BA" << (status_ok_BA ? "[OK]" : "[FAILED]") << std::endl;

    // BA_Size
 //   *m_resultBA_size -= *referenceBA_size;
  //  *m_resultBA_size /= *referenceBA_size;
 //   double diffBA_size(0);
 //   for(OutputData<double>::const_iterator it=m_resultBA_size->begin(); it!=m_resultBA_size->end(); ++it) {
 //       diffBA_size+= std::fabs(*it);
//   }
 //   diffBA_size /= m_resultBA_size->getAllocatedSize();

  //  bool status_ok_BA_size(true);
 //   if( diffBA_size > threshold ) {status_ok_BA_size=false;
 //                                  status_ok=false;}
  //  std::cout << "BA_Size" << (status_ok_BA_size ? "[OK]" : "[FAILED]") << std::endl;

    // DWBA
  //  *m_resultDWBA -= *referenceDWBA;
 //   *m_resultDWBA /= *referenceDWBA;
 //   double diffDWBA(0);
 //   for(OutputData<double>::const_iterator it=m_resultDWBA->begin(); it!=m_resultDWBA->end(); ++it) {
 //       diffDWBA+= std::fabs(*it);
 //  }
 //  diffDWBA /= m_resultDWBA->getAllocatedSize();
 //   bool status_ok_DWBA(true);
 //   if( diffDWBA > threshold ) {status_ok_DWBA=false;
  //                              status_ok=false;}
  //  std::cout << "DWBA" << (status_ok_DWBA ? "[OK]" : "[FAILED]") << std::endl;

    // Total  
  //  std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
 //   return (int)status_ok;
}

#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS03 test;
    test.run();

    return test.analyseResults();
}
#endif


