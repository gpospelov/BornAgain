#include "IsGISAXS04.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include <iostream>
#include <cmath>
#include <gsl/gsl_errno.h>


FunctionalTests::IsGISAXS04::IsGISAXS04()
    : m_name("IsGISAXS04")
    , m_description("1D and 2D paracrystal")
{
    m_results.resize(kNumberOfTests, 0);
    gsl_set_error_handler_off();
}


FunctionalTests::IsGISAXS04::~IsGISAXS04()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) {
        delete (*it);
    }
}


// IsGISAXS4 functional test: cylinders with 1DDL structure factor
void FunctionalTests::IsGISAXS04::run1DDL()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs04_1DDL");

    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    simulation.setSample(*sample);
    simulation.runSimulation();
    m_results[kTest_1DDL] = simulation.getOutputDataClone();

    delete sample;
}


// IsGISAXS4 functional test: cylinders with 2DDL structure factor
void FunctionalTests::IsGISAXS04::run2DDL()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs04_2DDL");

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);
    simulation.setSample(*sample);
    simulation.runSimulation();
    m_results[kTest_2DDL] = simulation.getOutputDataClone();

    delete sample;
}


int FunctionalTests::IsGISAXS04::analyseResults(const std::string &path_to_data)
{
    const double threshold(2e-10);
    const char *reference_files[kNumberOfTests] = {"isgisaxs04_reference_1DDL.ima.gz", "isgisaxs04_reference_2DDLh.ima.gz"};
    bool status_ok(true);

    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(path_to_data + reference_files[i_test]);
        OutputData<double> *result = m_results[i_test];

        // calculating average relative difference
        *result -= *reference;
        *result /= *reference;
        delete reference;

        double diff(0);
        for(OutputData<double>::const_iterator it=result->begin(); it!=result->end(); ++it) {
            diff+= std::fabs(*it);
        }
        diff /= result->getAllocatedSize();
        if( diff > threshold || std::isnan(diff) ) status_ok=false;
    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);

}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToData(argv[0], "../../../ReferenceData/BornAgain/");
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS04 test;
    test.run1DDL();
    test.run2DDL();
    return test.analyseResults(GetPathToData(argc, argv));
}
#endif

