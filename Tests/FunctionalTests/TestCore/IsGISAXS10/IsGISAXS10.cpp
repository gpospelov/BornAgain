#include "IsGISAXS10.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "MaterialManager.h"
#include "MultiLayer.h"
#include "OutputDataIOFactory.h"
#include "ParticleDecoration.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "MathFunctions.h"

#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS10::IsGISAXS10()
    : m_name("IsGISAXS10")
    , m_description("Cylinders with interference on top of substrate")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS10::run()
{
    // building sample
    MultiLayer multi_layer;
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air10", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate10", 5e-6, 2e-8);
    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    IInterferenceFunction *p_interference_function =
            new InterferenceFunction1DParaCrystal(20.0*Units::nanometer,
                    7*Units::nanometer, 1e7*Units::nanometer);
    const IMaterial *particle_material = MaterialManager::getHomogeneousMaterial("Particle", 5e-5, 2e-8);

    ParticleDecoration particle_decoration(new Particle(particle_material,
            new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setDecoration(particle_decoration);

    multi_layer.addLayer(air_layer);
    multi_layer.addLayer(substrate_layer);

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    simulation.setSample(multi_layer);

    // running simulation and copying data
    simulation.runSimulation();
    m_result = simulation.getIntensityData();
}


int FunctionalTests::IsGISAXS10::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);

    // retrieving reference data
    std::string filename = path_to_data + "isgisaxs10_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::readIntensityData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    delete reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin();
            it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold || MathFunctions::isnan(diff)) status_ok=false;

    std::cout << m_name << " " << m_description << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToData("../../../ReferenceData/BornAgain/", argv[0]);
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS10 test;
    test.run();
    return test.analyseResults(GetPathToData(argc, argv));
}
#endif

