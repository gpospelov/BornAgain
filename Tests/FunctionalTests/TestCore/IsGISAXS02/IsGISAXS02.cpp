#include "IsGISAXS02.h"
#include "OutputDataIOFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "SampleBuilderFactory.h"
#include "MathFunctions.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS02::IsGISAXS02()
    : m_name("IsGISAXS02")
    , m_description("Mixture cylinder particles with different size distribution")
    , m_result(0)
{
}


void FunctionalTests::IsGISAXS02::run()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs02");

    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree,
            2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    simulation.setSample(*sample);
    simulation.runSimulation();

    m_result = simulation.getIntensityData();

    delete sample;
}


int FunctionalTests::IsGISAXS02::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);

    // retrieving reference data
    std::string filename = path_to_data + "isgisaxs02_reference.ima.gz";
    OutputData<double > *reference = OutputDataIOFactory::readIntensityData(filename);

    // calculating average relative difference
    *m_result -= *reference;
    *m_result /= *reference;
    delete reference;

    double diff(0);
    for(OutputData<double>::const_iterator it=m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    bool status_ok(true);
    if( diff > threshold || MathFunctions::isnan(diff)) status_ok=false;

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;

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
    FunctionalTests::IsGISAXS02 test;
    test.run();

    return test.analyseResults(GetPathToData(argc, argv));
}
#endif
