#include "IsGISAXS04.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"

#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "GISASExperiment.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS04::IsGISAXS04()
    : m_name("IsGISAXS04")
    , m_description("1D and 2D paracrystal")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS04::run()
{
    // ---------------------
    // building sample
    // ---------------------

        MultiLayer multi_layer_1DDL;
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        IInterferenceFunction *p_interference_function1D = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,7*Units::nanometer, 1e3*Units::nanometer);
        complex_t n_particle(1.0-6e-4, 2e-8);
        ParticleDecoration particle_decoration1D( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration1D.addInterferenceFunction(p_interference_function1D);

        LayerDecorator air_layer_decorator1D(air_layer, particle_decoration1D);

        multi_layer_1DDL.addLayer(air_layer_decorator1D);
        multi_layer_1DDL.addLayer(substrate_layer);

    // IsGISAXS4 functional test: cylinders with 2DDL structure factor

      //  MultiLayer multi_layer_2DDL;

     //   InterferenceFunction2DParaCrystal *p_interference_function2D = InterferenceFunction2DParaCrystal::createHexagonal(20.0*Units::nanometer, 0.0,
     //           20.0*Units::micrometer, 20.0*Units::micrometer);
     //   FTDistribution2DCauchy pdf(1.0*Units::nanometer, 1.0*Units::nanometer);
     //   p_interference_function2D->setProbabilityDistributions(pdf, pdf);
     //   ParticleDecoration particle_decoration2D( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
     //   particle_decoration2D.addInterferenceFunction(p_interference_function2D);
     //   LayerDecorator air_layer_decorator2D(air_layer, particle_decoration2D);

     //   multi_layer_2DDL.addLayer(air_layer_decorator2D);
     //   multi_layer_2DDL.addLayer(substrate_layer);

    // ---------------------
    // building experiment
    // ---------------------
        GISASExperiment experiment;
        experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

     // ---------------------
     // running experiment and copying data
     // ---------------------
     // 1DDL
        experiment.setSample(multi_layer_1DDL);
        experiment.runSimulation();
        //OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_1DDL.ima");
        m_result = experiment.getOutputDataClone();
     // 2DDL
       // experiment.setSample(multi_layer_2DDL);
       // experiment.runSimulation();
       // OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_2DDL.ima");
       // m_result = experiment.getOutputDataClone();
}

int FunctionalTests::IsGISAXS04::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data

     std::string filename1DDL = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS04/isgi_1DDL.ima.gz";
     OutputData<double > *reference1DDL = OutputDataIOFactory::getOutputData(filename1DDL);
     //OutputData<double > *m_result1DDL = OutputDataIOFactory::getOutputData("this_1DDL.ima");

   //  std::string filename2DDL = Utils::FileSystem::GetHomePath() + "/Tests/FunctionalTests/TestCore/IsGISAXS04/isgi_2DDLh.ima.gz";
    //  OutputData<double > *reference2DDL = OutputDataIOFactory::getOutputData(filename2DDL);
    // OutputData<double > *m_result2DDL = OutputDataIOFactory::getOutputData("this_2DDL.ima");


    // calculating average relative difference
       bool status_ok(true);
     //1DDL

      //*m_result1DDL -= *reference1DDL;
      //*m_result1DDL /= *reference1DDL;

       *m_result -= *reference1DDL;
       *m_result /= *reference1DDL;
      double diff1DDL(0);
      //for(OutputData<double>::const_iterator it=m_result1DDL->begin(); it!=m_result1DDL->end(); ++it) {
      for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
          diff1DDL+= std::fabs(*it);
      }
     // diff1DDL /= m_result1DDL->getAllocatedSize();
      diff1DDL /= m_result->getAllocatedSize();

      bool status_ok_1DDL(true);
     if( diff1DDL > threshold ) {status_ok_1DDL=false;
                                 status_ok=false;}
     std::cout << "1DDL" << (status_ok_1DDL ? "[OK]" : "[FAILED]") << std::endl;

     //2DDL
      //*m_result2DDL -= *reference2DDL;
    //  *m_result2DDL /= *reference2DDL;
    //  double diff2DDL(0);
    //  for(OutputData<double>::const_iterator it=m_result2DDL->begin(); it!=m_result2DDL->end(); ++it) {
    //      diff2DDL+= std::fabs(*it);
    // }
    //  diff2DDL /= m_result2DDL->getAllocatedSize();

    //  bool status_ok_2DDL(true);
    //  if( diff2DDL > threshold ) {status_ok_2DDL=false;
    //                                 status_ok=false;}
    //  std::cout << "2DDL" << (status_ok_2DDL ? "[OK]" : "[FAILED]") << std::endl;

     // std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
      return (int)status_ok;
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS04 test;
    test.run();

    return test.analyseResults();
}
#endif

