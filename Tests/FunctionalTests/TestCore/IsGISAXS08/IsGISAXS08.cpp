#include "IsGISAXS08.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "Units.h"
#include "MaterialManager.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS08::IsGISAXS08()
    : m_name("IsGISAXS08")
    , m_description("2DDL paracrystal")
    , m_result(0)
{
      m_data_path = std::string(Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS08/");
}

void FunctionalTests::IsGISAXS08::run2DDL()
{   // ---------------------
    // building sample
    // ---------------------
        //IsGISAXS8_2DDL_lattice
            MultiLayer multi_layer;
            complex_t n_particle(1.0-6e-4, 2e-8);
            const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
            const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
            Layer air_layer;
            air_layer.setMaterial(p_air_material);
            Layer substrate_layer;
            substrate_layer.setMaterial(p_substrate_material);

            InterferenceFunction2DParaCrystal *p_interference_function = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
            p_interference_function->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
            FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 2.0*Units::nanometer);
            FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 2.0*Units::nanometer);
            p_interference_function->setProbabilityDistributions(pdf1, pdf2);
            ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
            particle_decoration.addInterferenceFunction(p_interference_function);
            LayerDecorator air_layer_decorator(air_layer, particle_decoration);

            multi_layer.addLayer(air_layer_decorator);
            multi_layer.addLayer(substrate_layer);

    // ---------------------
    // building simulation
    // ---------------------
     Simulation simulation;
     simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
     simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    // ---------------------
    // running simulation and copying data
    // ---------------------

    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_result = simulation.getOutputDataClone();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_2DDL_lattice.ima");
}

void FunctionalTests::IsGISAXS08::run2DDL2()
{   // IsGISAXS8 functional test: 2D paracrystal lattice with isotropic pdfs
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

            InterferenceFunction2DParaCrystal *p_interference_function = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
            p_interference_function->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
            FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 0.5*Units::nanometer);
            FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 0.5*Units::nanometer);
            p_interference_function->setProbabilityDistributions(pdf1, pdf2);
            ParticleDecoration particle_decoration( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
            particle_decoration.addInterferenceFunction(p_interference_function);
            LayerDecorator air_layer_decorator(air_layer, particle_decoration);

            multi_layer.addLayer(air_layer_decorator);
            multi_layer.addLayer(substrate_layer);

    // ---------------------
    // building simulation
    // ---------------------
     Simulation simulation;
     simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
     simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running simulation and copying data
    // ---------------------
    // cylinder in the air
    simulation.setSample(multi_layer);
    simulation.runSimulation();
    m_result = simulation.getOutputDataClone();
    OutputDataIOFactory::writeOutputData(*simulation.getOutputData(),m_data_path+"this_2DDL_lattice2.ima");
}


int FunctionalTests::IsGISAXS08::analyseResults()
{
    const double threshold(1e-10);

    std::vector< CompareStruct > tocompare;
    tocompare.push_back( CompareStruct("isgisaxs08_reference_2DDL_lattice.ima.gz", "this_2DDL_lattice.ima", "Cylinder 2DDL lattice") );
    tocompare.push_back( CompareStruct("isgisaxs08_reference_2DDL_lattice2.ima.gz", "this_2DDL_lattice2.ima", "Cylinder 2DDL lattice with isotropic pdfs") );

    bool status_ok(true);

    // retrieving reference data and generated examples
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

    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;

}

#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS08 test;
    //test.run();
    test.run2DDL();
    test.run2DDL2();
    return test.analyseResults();
}
#endif



