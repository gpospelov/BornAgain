#include "IsGISAXS08.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "LayerDecorator.h"
#include "ParticleBuilder.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "GISASExperiment.h"
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
{ }

void FunctionalTests::IsGISAXS08::run()
{   // ---------------------
    // building sample
    // ---------------------
        //IsGISAXS8_2DDL_lattice
            complex_t n_particle(1.0-6e-4, 2e-8);
            const IMaterial *p_air_material = MaterialManager::instance().addHomogeneousMaterial("Air", 1.0, 0.0);
            const IMaterial *p_substrate_material = MaterialManager::instance().addHomogeneousMaterial("Substrate", 1.0-6e-6, 2e-8);
            Layer air_layer;
            air_layer.setMaterial(p_air_material);
            Layer substrate_layer;
            substrate_layer.setMaterial(p_substrate_material);

            MultiLayer multi_layer_2DDL;
            InterferenceFunction2DParaCrystal *p_interference_function1 = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
            p_interference_function1->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
            FTDistribution2DCauchy pdf1_1(0.5*Units::nanometer, 2.0*Units::nanometer);
            FTDistribution2DCauchy pdf2_1(0.5*Units::nanometer, 2.0*Units::nanometer);
            p_interference_function1->setProbabilityDistributions(pdf1_1, pdf2_1);
            ParticleDecoration particle_decoration1( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
            particle_decoration1.addInterferenceFunction(p_interference_function1);
            LayerDecorator air_layer_decorator1(air_layer, particle_decoration1);

            multi_layer_2DDL.addLayer(air_layer_decorator1);
            multi_layer_2DDL.addLayer(substrate_layer);

        // IsGISAXS8 functional test: 2D paracrystal lattice with isotropic pdfs
            MultiLayer multi_layer_2DDL2;
            InterferenceFunction2DParaCrystal *p_interference_function2 = new InterferenceFunction2DParaCrystal(10.0*Units::nanometer, 10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
            p_interference_function2->setDomainSizes(20.0*Units::micrometer, 20.0*Units::micrometer);
            FTDistribution2DCauchy pdf1_2(0.5*Units::nanometer, 0.5*Units::nanometer);
            FTDistribution2DCauchy pdf2_2(0.5*Units::nanometer, 0.5*Units::nanometer);
            p_interference_function2->setProbabilityDistributions(pdf1_2, pdf2_2);
            ParticleDecoration particle_decoration2( new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
            particle_decoration2.addInterferenceFunction(p_interference_function2);
            LayerDecorator air_layer_decorator2(air_layer, particle_decoration2);

            multi_layer_2DDL2.addLayer(air_layer_decorator2);
            multi_layer_2DDL2.addLayer(substrate_layer);

    // ---------------------
    // building experiment
    // ---------------------
     GISASExperiment experiment;
     experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
     experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // ---------------------
    // running experiment and copying data
    // ---------------------
    // cylinder DWBA
    experiment.setSample(multi_layer_2DDL);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_2DDL_lattice.ima");

    // cylinder in the air
    experiment.setSample(multi_layer_2DDL2);
    experiment.runExperiment();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputData(),"this_2DDL_lattice2.ima");

}
int FunctionalTests::IsGISAXS08::analyseResults()
{
    const double threshold(1e-10);

    std::vector< CompareStruct > tocompare;
    m_data_path = Utils::FileSystem::GetHomePath()+"Tests/FunctionalTests/TestCore/IsGISAXS08/";

    tocompare.push_back( CompareStruct("isgi_2DDL_lattice.ima.gz", "this_2DDL_lattice.ima", "Cylinder 2DDL lattice") );
    tocompare.push_back( CompareStruct("isgi_2DDL_lattice2.ima.gz", "this_2DDL_lattice2.ima", "Cylinder 2DDL lattice with isotropic pdfs") );

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

    std::cout << descript << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (int)status_ok;

}

#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS08 test;
    test.run();

    return test.analyseResults();
}
#endif



