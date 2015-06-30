// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPerformance.cpp
//! @brief     Implements TestPerformance
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestPerformance.h"
#include "SimulationRegistry.h"
#include "Utils.h"
#include "ProgramOptions.h"
#include "Units.h"
#include "SpecularMatrix.h"
#include "SampleFactory.h"
#include "SpecularMagnetic.h"

#include "TDatime.h"
#include "TSystem.h"
#include "TBenchmark.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <boost/format.hpp>



TestPerformance::TestPerformance()
{
    m_tests.push_back(new PerformanceTest("isgisaxs02",1));    // TwoTypesCylindersDistributionBuilder
    m_tests.push_back(new PerformanceTest("isgisaxs06a",50)); //SquareLatticeBuilder
    m_tests.push_back(new PerformanceTest("isgisaxs09b",50)); // RotatedPyramidsBuilder
    m_tests.push_back(new PerformanceTest("isgisaxs11",50)); // CoreShellParticleBuilder
    m_tests.push_back(new PerformanceTest("isgisaxs15",20)); // ParticlesInSSCABuilder
    m_tests.push_back(new PerformanceTest("mesocrystal01",1)); // MesoCrystalBuilder
    m_tests.push_back(new SpecularMatrixPerformanceTest("specmatrix", 500000));
    m_tests.push_back(new SpecularMagneticPerformanceTest("specmagnetic", 500000));
    m_tests.push_back(new PerformanceTest("polmagcylinders2",50));
    std::cout << "TestPerformance::TestPerformance() -> Info. Preparing to run " << m_tests.size() << " performance tests."  << std::endl;
}


TestPerformance::~TestPerformance()
{
    for(size_t i=0; i<m_tests.size(); ++i) delete m_tests[i];
}





void TestPerformance::execute()
{
    for(size_t i=0; i<m_tests.size(); ++i) {
        PerformanceTest *test = m_tests[i];
        set_sysinfo(test);

        std::cout << "Running test: " << std::setw(20) << std::left << test->getName() << " ... ";
        std::cout.flush();
        test->execute();
        std::cout << boost::format("OK: %-6.3f (real sec), %-6.3f (cpu sec) ") % test->m_real_time % test->m_cpu_time << std::endl;
    }

    write_results();
}



void TestPerformance::write_results()
{
    std::string filename("perf_history.txt");
    std::ofstream file;
    file.open(filename.c_str(), std::ios_base::app);
    if( !file.is_open() ) {
        throw FileNotIsOpenException("TestPerformance::execute() -> Error. Can't open file '"+filename+"' for writing.");
    }

    write_header(file);
    write_performance(file);

    file.close();

    std::cout << "TestPerformance::write_performance() -> Info. File '" << filename << "' is updated." << std::endl;
}


//! write header in file
void TestPerformance::write_header(std::ofstream &file)
{
    file << std::endl;
    file << boost::format("| %-19s | %-10s | %-13s | %2s | %-8s |") %  "date " % "hostname" % "sysinfo" % "tr" % "total";
    for(size_t i=0; i<m_tests.size(); ++i) {
        file  << boost::format(" %-12s |") %  Utils::AdjustStringLength(m_tests[i]->getName(),12);
    }
    file << std::endl;
}

//! write results of performance measurements
void TestPerformance::write_performance(std::ofstream &file)
{
    PerformanceTest *test0 = m_tests[0];
    file << boost::format("| %-19s | %-10s | %-13s | %-2d |") %  test0->m_datime % test0->m_hostname % test0->m_sysinfo % test0->m_nthreads;
    double sum_real(0), sum_cpu(0);
    for(size_t i=0; i<m_tests.size(); ++i) {
        sum_real += m_tests[i]->m_real_time;
        sum_cpu += m_tests[i]->m_cpu_time;
    }
    file  << boost::format(" %-8.3f |") %  sum_real;

    for(size_t i=0; i<m_tests.size(); ++i) {
        file  << boost::format(" %-12.3f |") %  m_tests[i]->m_real_time;
    }
    file << std::endl;
}


//! read sustem information and store it in the test
void TestPerformance::set_sysinfo(PerformanceTest *test)
{
    test->initialise(mp_options);

    // saving date and time
    TDatime td;
    test->m_datime = std::string(td.AsSQLString());

    // saving host name
    std::string hostname(gSystem->HostName());
    // stripping host name after first '.' (somehost.jcns.frm2 -> somehost)
    std::string::size_type pos = hostname.find_first_of('.');
    if(pos != std::string::npos) {
        hostname.erase(pos,hostname.size()-pos);
    }
    test->m_hostname = hostname;

    // saving hardware information
    SysInfo_t sys_info;
    int status = gSystem->GetSysInfo(&sys_info);
    if( status == -1) {
        test->m_sysinfo = std::string("Unknown hardware");
    }else{
        std::ostringstream os;
        os << std::string(gSystem->GetBuildArch());
        //os << std::string(gSystem->GetBuildArch()) << ", "<< sys_info.fCpuSpeed << " MHz";
        //os << ", " << 	sys_info.fL2Cache << " Kb";
        test->m_sysinfo = os.str();
    }

    if (mp_options->find("threads")) {
        test->m_nthreads = (*mp_options)["threads"].as<int>();
    }
}


// -----------------------------------------------------------------------------
// General PerformanceTest
// -----------------------------------------------------------------------------

//! run performance measurements
void PerformanceTest::execute()
{
    TBenchmark mb;
    mb.Start( getName().c_str() );

    runTests();

    mb.Stop( getName().c_str() );

    m_cpu_time = mb.GetCpuTime(getName().c_str());
    m_real_time = mb.GetRealTime(getName().c_str());
}


//! run standard simulation
void PerformanceTest::runTests()
{
    SimulationRegistry registry;
    Simulation *simulation = registry.createSimulation(getName());
    simulation->setProgramOptions(mp_options);
    for(int i=0; i<m_nrepetitions; i++){
        simulation->runSimulation();
    }
    delete simulation;
}

// -----------------------------------------------------------------------------
// custom PerformanceTest's
// -----------------------------------------------------------------------------

void SpecularMatrixPerformanceTest::runTests()
{
    MultiLayer *ml = dynamic_cast<MultiLayer *>(SampleFactory::createSample("SimpleMultilayer"));

    for(int i=0; i<m_nrepetitions; i++){
        static double alpha_i = -0.3;
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
        SpecularMatrix::MultiLayerCoeff_t coeffs;
        SpecularMatrix matrixCalculator;
        matrixCalculator.execute(*ml, kvec, coeffs);
    }
    delete ml;
}

void SpecularMagneticPerformanceTest::runTests()
{
    MultiLayer *ml = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MultilayerSpecularMagneticTestCase"));

    for(int i=0; i<m_nrepetitions; i++){
        static double alpha_i = -0.3;
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
        SpecularMagnetic::MultiLayerCoeff_t coeffs;
        SpecularMagnetic magneticCalculator;
        magneticCalculator.execute(*ml, kvec, coeffs);
    }
    delete ml;
}


