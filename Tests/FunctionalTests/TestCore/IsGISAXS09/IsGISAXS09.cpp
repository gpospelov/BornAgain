#include "IsGISAXS09.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include <iostream>
#include <cmath>


FunctionalTests::IsGISAXS09::IsGISAXS09()
    : m_name("IsGISAXS09")
    , m_description("Pyramids, rotated pyramids on top of substrate")
{
    m_results.resize(kNumberOfTests, 0);
}


FunctionalTests::IsGISAXS09::~IsGISAXS09()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it)
        delete (*it);
}


// IsGISAXS example #9a: pyramid
void FunctionalTests::IsGISAXS09::runpyramidZ0()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs09");

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.setSample(*sample);

    // running simulation
    simulation.runSimulation();
    m_results[kTest_Z0] = simulation.getOutputDataClone();

    delete sample;
}


// IsGISAXS example #9b: rotated pyramid
void FunctionalTests::IsGISAXS09::runpyramidZ45()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs09_rotated");

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(
        1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    simulation.setSample(*sample);

    // running simulation
    simulation.runSimulation();
    m_results[kTest_Z45] = simulation.getOutputDataClone();

    delete sample;
}


int FunctionalTests::IsGISAXS09::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);
    const char *reference_files[kNumberOfTests] =
        {"isgisaxs09_reference_pyramid_Z0.ima.gz",
         "isgisaxs09_reference_pyramid_Z45.ima.gz"};
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference =
                OutputDataIOFactory::getOutputData(path_to_data +
                                               reference_files[i_test]);
        OutputData<double> *result = m_results[i_test];

        // calculating average relative difference
        *result -= *reference;
        *result /= *reference;
        delete reference;

        double diff(0);
        for(OutputData<double>::const_iterator it =
                result->begin(); it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= result->getAllocatedSize();
        if( diff > threshold || std::isnan(diff)) status_ok=false;
    }

    std::cout << m_name << " " << m_description << " " <<
        (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToExecutable(argv[0]) + "../../../ReferenceData/BornAgain/";
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS09 test;
    test.runpyramidZ0();
    test.runpyramidZ45();
    return test.analyseResults(GetPathToData(argc, argv));
}
#endif
