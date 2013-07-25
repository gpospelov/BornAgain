#include "IsGISAXS06.h"
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

#include <iostream>
#include <cmath>

FunctionalTests::IsGISAXS06::IsGISAXS06()
    : m_name("IsGISAXS06")
    , m_description("2D lattice with different disorder")
{
    m_results.resize(kNumberOfTests, 0);

    m_simulation.setDetectorParameters(
        100, 0.0*Units::degree, 2.0*Units::degree,
        100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation.setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree,
            0.0*Units::degree);

    SimulationParameters sim_params;
    sim_params.me_framework = SimulationParameters::DWBA;
    sim_params.me_if_approx = SimulationParameters::LMA;
    sim_params.me_lattice_type = SimulationParameters::LATTICE;
    m_simulation.setSimulationParameters(sim_params);

}


FunctionalTests::IsGISAXS06::~IsGISAXS06()
{
    for(results_t::iterator it = m_results.begin(); it!=m_results.end(); ++it) {
        delete (*it);
    }
}


// IsGISAXS6_lattice()
void FunctionalTests::IsGISAXS06::runlattice()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs06_lattice1");

    // running simulation and copying data
    m_simulation.setSample(*sample);
    m_simulation.runSimulation();
    m_results[kTest_Lattice] = m_simulation.getOutputDataClone();

    delete sample;
}


// IsGISAXS6 functional test: cylinders lattice centered
void FunctionalTests::IsGISAXS06::runcentered()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs06_lattice2");

    // running simulation and copying data
    m_simulation.setSample(*sample);
    m_simulation.runSimulation();
    m_results[kTest_Centered] = m_simulation.getOutputDataClone();

    delete sample;
}


// IsGISAXS6 functional test: cylinders lattice rotated
void FunctionalTests::IsGISAXS06::runrotated()
{
    SampleBuilderFactory factory;
    ISample *sample = factory.createSample("isgisaxs06_lattice3");

    // running simulation and copying data
    m_simulation.setSample(*sample);
    m_simulation.runSimulation();
    m_results[kTest_Rotated] = m_simulation.getOutputDataClone();
}


// lattice variants
void FunctionalTests::IsGISAXS06::runvariants()
{
    IsGISAXS06Lattice4Builder builder;

    // running simulation and copying data
    OutputData<double> *p_total = m_simulation.getOutputDataClone();
    p_total->setAllTo(0.0);
    int nbins = 3;
    double xi_min = 0.0*Units::degree;
    double xi_max = 240.0*Units::degree;
    StochasticDoubleGate xg(xi_min, xi_max);
    StochasticSampledParameter xi(xg, nbins, xi_min, xi_max);
    for (size_t i=0; i<xi.getNbins(); ++i) {
        double xi_value = xi.getBinValue(i);
        double probability = xi.getNormalizedProbability(i);
        builder.setParameterValue("xi",xi_value);
        MultiLayer *p_sample = dynamic_cast<MultiLayer *>(builder.buildSample());
        m_simulation.setSample(*p_sample);
        m_simulation.runSimulation();
        delete p_sample;
        OutputData<double> *p_single_output = m_simulation.getOutputDataClone();
        p_single_output->scaleAll(probability);
        *p_total += *p_single_output;
        delete p_single_output;
    }

    m_results[kTest_Variants] = p_total;
}


int FunctionalTests::IsGISAXS06::analyseResults(
        const std::string &path_to_executable)
{
    const double threshold(2e-10);
    const char *reference_files[kNumberOfTests] = {
        "isgisaxs06_reference_lattice.ima.gz",
        "isgisaxs06_reference_centered.ima.gz",
        "isgisaxs06_reference_rotated.ima.gz",
        "isgisaxs06_reference_variants.ima.gz"
    };
    bool status_ok(true);

    // retrieving reference data and generated examples
    for(size_t i_test=0; i_test<kNumberOfTests; ++i_test) {
        OutputData<double> *reference =
            OutputDataIOFactory::getOutputData(path_to_executable
                    + reference_files[i_test]);
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
    return Utils::FileSystem::GetPathToExecutable(argv[0]) +
            "../../../ReferenceData/BornAgain/";
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS06 test;
    test.runlattice();
    test.runcentered();
    test.runrotated();
    test.runvariants();

    return test.analyseResults(GetPathToData(argc, argv));
}
#endif

