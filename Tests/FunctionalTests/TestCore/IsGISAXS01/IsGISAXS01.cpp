#include "IsGISAXS01.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Utils.h"
#include "Units.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS01::IsGISAXS01()
    : m_name("IsGISAXS01")
    , m_description("Mixture of cylinders and prisms without interference")
    , m_result(0)
{ }


void FunctionalTests::IsGISAXS01::run()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs01");

    Simulation simulation;
    simulation.setDetectorParameters(
        100,-1.0*Units::degree, 1.0*Units::degree, 100,
        0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // Run simulation
    simulation.setSample(*sample);
    simulation.runSimulation();

    // Copy results
    m_result = simulation.getOutputDataClone();

    delete sample;
}


int FunctionalTests::IsGISAXS01::analyseResults()
{
    const double threshold(1e-10);

    // Retrieve reference data.
    std::string filename =
        Utils::FileSystem::GetHomePath() +
        "/Tests/ReferenceData/BornAgain/isgisaxs01_reference.ima.gz";
    OutputData<double > *reference =
        OutputDataIOFactory::getOutputData(filename);

    // Calculating average relative difference.
    *m_result -= *reference;
    *m_result /= *reference;

    double diff(0);
    for(OutputData<double>::const_iterator it =
            m_result->begin(); it!=m_result->end(); ++it) {
        diff+= std::fabs(*it);
    }
    diff /= m_result->getAllocatedSize();

    // Assess result.
    bool status_ok(true);
    if( diff > threshold || std::isnan(diff) ) status_ok=false;

    std::cout << m_name << " " << m_description << " " <<
        (status_ok ? "[OK]" : "[FAILED]") << std::endl;

    delete reference;

    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
int main()
{
    //MSG::SetLevel(MSG::INFO);
    FunctionalTests::IsGISAXS01 test;
    test.run();

    return test.analyseResults();
}
#endif
