#include "IsGISAXS04.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Experiment.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>
#include <gsl/gsl_errno.h>

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
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        MultiLayer multi_layer_1DDL;
        IInterferenceFunction *p_interference_function1D = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,7*Units::nanometer, 1e3*Units::nanometer);
        ParticleDecoration particle_decoration1D( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration1D.addInterferenceFunction(p_interference_function1D);
        LayerDecorator air_layer_decorator1D(air_layer, particle_decoration1D);

        multi_layer_1DDL.addLayer(air_layer_decorator1D);
        multi_layer_1DDL.addLayer(substrate_layer);

    // IsGISAXS4 functional test: cylinders with 2DDL structure factor
        MultiLayer multi_layer_2DDL;
        InterferenceFunction2DParaCrystal *p_interference_function2D = InterferenceFunction2DParaCrystal::createHexagonal(20.0*Units::nanometer, 0.0,
                20.0*Units::micrometer, 20.0*Units::micrometer);
        FTDistribution2DCauchy pdf(1.0*Units::nanometer, 1.0*Units::nanometer);
        p_interference_function2D->setProbabilityDistributions(pdf, pdf);
        ParticleDecoration particle_decoration2D( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration2D.addInterferenceFunction(p_interference_function2D);
        LayerDecorator air_layer_decorator2D(air_layer, particle_decoration2D);

        multi_layer_2DDL.addLayer(air_layer_decorator2D);
        multi_layer_2DDL.addLayer(substrate_layer);
    // ---------------------
    // building experiment
    // ---------------------
        gsl_set_error_handler_off();

        Experiment experiment;
        experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

     // ---------------------
     // running experiment and copying data
     // ---------------------
     // 1DDL
        experiment.setSample(multi_layer_1DDL);
        experiment.runExperiment();
        OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_1DDL.ima");

     // 2DDL
        experiment.setSample(multi_layer_2DDL);
        experiment.runExperiment();
        OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_2DDLh.ima");
}

int FunctionalTests::IsGISAXS04::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data and generated examples
     std::vector< CompareStruct > tocompare;
     m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS04/";

     tocompare.push_back( CompareStruct("isgi_1DDL.ima.gz",  "this_1DDL.ima", "Cylinder 1DDL") );
     tocompare.push_back( CompareStruct("isgi_2DDLh.ima.gz", "this_2DDLh.ima", "Cylinder 2DDL") );

       bool status_ok(true);

       for(size_t i=0; i<tocompare.size(); ++i) {
           OutputData<double> *reference = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].isginame);
           OutputData<double> *m_result = OutputDataIOFactory::getOutputData(m_data_path+tocompare[i].thisname);
           std::string descript  = tocompare[i].descr;

       // calculating average relative difference
       *m_result -= *reference;
       *m_result /= *reference;
       double diff(0);
       for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
           diff+= std::fabs(*it);
       }
       diff /= m_result->getAllocatedSize();
       if( diff > threshold ) status_ok=false;

       std::cout << descript << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
       }

       std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
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

