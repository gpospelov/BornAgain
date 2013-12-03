#include "IsGISAXS06L4.h"
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

FunctionalTests::IsGISAXS06L4::IsGISAXS06L4()
    : m_name("IsGISAXS06L4")
    , m_description("2D lattice variants")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS06L4::run(const std::string &path_to_data)
{
	IsGISAXS06Lattice4Builder builder;
    SimulationRegistry sim_registry;
    Simulation* simulation = sim_registry.createSimulation("isgisaxs06_lattice4");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs06_reference_variants.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    // running simulation and copying data
    OutputData<double> *p_total = simulation->getIntensityData();
    p_total->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticDoubleGate xg(xi_min, xi_max);
    StochasticSampledParameter xi(xg, nbins, xi_min, xi_max);
    for (size_t i=0; i<xi.getNbins(); ++i) {
        double xi_value = xi.getBinValue(i);
        double probability = xi.getNormalizedProbability(i);
        builder.setMatchedParametersValue("*xi",xi_value);
        MultiLayer *p_sample = dynamic_cast<MultiLayer *>(builder.buildSample());
        simulation->setSample(*p_sample);
        simulation->runSimulation();
        delete p_sample;
        OutputData<double> *p_single_output = simulation->getIntensityData();
        p_single_output->scaleAll(probability);
        *p_total += *p_single_output;
        delete p_single_output;
	}

    m_result = p_total;
    delete simulation;
}


int FunctionalTests::IsGISAXS06L4::analyseResults()
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
    FunctionalTests::IsGISAXS06L4 test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif

