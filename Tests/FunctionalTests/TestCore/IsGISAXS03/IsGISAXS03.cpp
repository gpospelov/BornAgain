#include "IsGISAXS03.h"
#include "Simulation.h"
#include "SampleBuilderFactory.h"
#include "Units.h"
#include "Utils.h"
#include <iostream>
#include <cmath>

#include "MultiLayer.h"
#include "Layer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "FormFactorCylinder.h"
#include "InterferenceFunctionNone.h"
#include "StochasticGaussian.h"
#include "LayerDecorator.h"
#include "StochasticSampledParameter.h"
#include "ParticleBuilder.h"
#include "OutputDataIOFactory.h"


FunctionalTests::IsGISAXS03::IsGISAXS03()
    : m_name("IsGISAXS03")
    , m_description("Cylinder formfactor in BA and DWBA")
    , m_path(Utils::FileSystem::GetHomePath()+std::string("Tests/ReferenceData/BornAgain/"))
{
    m_results.resize(kNumberOfTests, 0);
}

FunctionalTests::IsGISAXS03::~IsGISAXS03()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) delete (*it);
}


// IsGISAXS3 functional test: cylinder on the substrate
void FunctionalTests::IsGISAXS03::runDWBA()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs03_dwba");

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(*sample);
    simulation.runSimulation();
    m_results[kTest_DWBA] = simulation.getOutputDataClone();

    delete sample;
}


// IsGISAXS3 functional test: cylinder in the air
void FunctionalTests::IsGISAXS03::runBA()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs03_ba");

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(*sample);
    simulation.runSimulation();
    m_results[kTest_BA] = simulation.getOutputDataClone();

    delete sample;
}


// IsGISAXS3 functional test: cylinder in the air with size distribution
void FunctionalTests::IsGISAXS03::runBA_Size()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs03_basize");

    // building simulation
    Simulation simulation;
    simulation.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                     100, 0.0*Units::degree, 2.0*Units::degree, true);
    simulation.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // running simulation and copying data
    simulation.setSample(*sample);
    simulation.runSimulation();
    m_results[kTest_BASize] = simulation.getOutputDataClone();

    delete sample;
}


int FunctionalTests::IsGISAXS03::analyseResults()
{
    const double threshold(1e-10);
    const char *reference_files[kNumberOfTests] = {"isgisaxs03_reference_DWBA.ima.gz", "isgisaxs03_reference_BA.ima.gz", "isgisaxs03_reference_BA_size.ima.gz"};
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference = OutputDataIOFactory::getOutputData(m_path + reference_files[i_test]);
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
        if( diff > threshold || std::isnan(diff)) status_ok=false;

    }

    std::cout << m_name << " " << m_description << " " << (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
int main()
{
    FunctionalTests::IsGISAXS03 test;
    test.runDWBA();
    test.runBA();
    test.runBA_Size();
    return test.analyseResults();
}
#endif


