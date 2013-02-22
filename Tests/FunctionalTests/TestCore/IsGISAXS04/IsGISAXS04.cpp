#include "IsGISAXS04.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
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
{
    m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS04/";
}

void FunctionalTests::IsGISAXS04::run1DDL()
{ // IsGISAXS4 functional test: cylinders with 1DDL structure factor
    // ---------------------
    // building sample
    // ---------------------
        MultiLayer multi_layer;
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        IInterferenceFunction *p_interference_function = new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,7*Units::nanometer, 1e3*Units::nanometer);
        ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration.addInterferenceFunction(p_interference_function);
        LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer.addLayer(air_layer_decorator);
        multi_layer.addLayer(substrate_layer);

    // ---------------------
    // building simulation
    // ---------------------
        gsl_set_error_handler_off();

        Simulation simulation;
        simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

     // ---------------------
     // running simulation and copying data
     // ---------------------
        simulation.setSample(multi_layer);
        simulation.runSimulation();
        m_result = simulation.getOutputDataClone();
        OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_1DDL.ima");
}


void FunctionalTests::IsGISAXS04::run2DDL()
{ // IsGISAXS4 functional test: cylinders with 2DDL structure factor
    // ---------------------
    // building sample
    // ---------------------
        MultiLayer multi_layer;
        complex_t n_particle(1.0-6e-4, 2e-8);
        const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
        const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
        Layer air_layer;
        air_layer.setMaterial(p_air_material);
        Layer substrate_layer;
        substrate_layer.setMaterial(p_substrate_material);

        InterferenceFunction2DParaCrystal *p_interference_function = InterferenceFunction2DParaCrystal::createHexagonal(20.0*Units::nanometer, 0.0,
                20.0*Units::micrometer, 20.0*Units::micrometer);
        FTDistribution2DCauchy pdf(1.0*Units::nanometer, 1.0*Units::nanometer);
        p_interference_function->setProbabilityDistributions(pdf, pdf);
        ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
        particle_decoration.addInterferenceFunction(p_interference_function);
       LayerDecorator air_layer_decorator(air_layer, particle_decoration);

        multi_layer.addLayer(air_layer_decorator);
        multi_layer.addLayer(substrate_layer);
    // ---------------------
    // building simulation
    // ---------------------
        gsl_set_error_handler_off();

        Simulation simulation;
        simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
        simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

     // ---------------------
     // running simulation and copying data
     // ---------------------
        simulation.setSample(multi_layer);
        simulation.runSimulation();
        m_result = simulation.getOutputDataClone();
        OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_2DDLh.ima");
}

int FunctionalTests::IsGISAXS04::analyseResults()
{
    const double threshold(1e-10);

    // retrieving reference data and generated examples
     std::vector< CompareStruct > tocompare;
     tocompare.push_back( CompareStruct("isgisaxs04_reference_1DDL.ima.gz",  "this_1DDL.ima", "Cylinder 1DDL") );
     tocompare.push_back( CompareStruct("isgisaxs04_reference_2DDLh.ima.gz", "this_2DDLh.ima", "Cylinder 2DDL") );

       bool status_ok(true);

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
    FunctionalTests::IsGISAXS04 test;
    //test.run();
    test.run1DDL();
    test.run2DDL();
    return test.analyseResults();

}
#endif

