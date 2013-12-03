#include "IsGISAXS06L1.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "FormFactorCylinder.h"
#include "Simulation.h"
#include "Units.h"
#include "MaterialManager.h"
#include "InterferenceFunction2DLattice.h"
#include "PositionParticleInfo.h"
#include "OutputDataIOFactory.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "Utils.h"
#include "SampleBuilderFactory.h"
#include "IsGISAXS06Builder.h"
#include "MathFunctions.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS06L1::IsGISAXS06L1()
    : m_name("IsGISAXS06L1")
    , m_description("2D lattice with different disorder")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS06L1::run(const std::string &path_to_data)
{

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs06_lattice1");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs06_reference_lattice.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int FunctionalTests::IsGISAXS06L1::analyseResults()
{
    const double threshold(2e-10);

    // Calculating average relative difference.
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    // Assess result.
	bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
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
    FunctionalTests::IsGISAXS06L1 test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif

