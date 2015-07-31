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
#include "SampleBuilderFactory.h"
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



// -----------------------------------------------------------------------

TestPerformance::TestPerformance()
{
    add("MultiLayer",         "MaxiGISAS",    "MultiLayerWithRoughnessBuilder", 1);
    add("CylindersInDWBA",    "MaxiGISAS",    "CylindersInDWBABuilder", 10);
    add("RotatedPyramids",    "MaxiGISAS",    "RotatedPyramidsBuilder", 10);
    add("CoreShell",          "MaxiGISAS",    "CoreShellParticleBuilder", 10);
    add("SquareLattice",      "MaxiGISAS",    "SquareLatticeBuilder", 10);
    add("RadialParaCrystal",  "MaxiGISAS",    "RadialParaCrystalBuilder", 10);
    add("HexParaCrystal",     "BasicGISAS",   "HexParaCrystalBuilder", 1);
    add("SSCA",               "MaxiGISAS",    "SizeDistributionSSCAModelBuilder", 10);
    add("Mesocrystal",        "MaxiGISAS",    "MesoCrystalBuilder", 2);
    add("PolMagCyl",          "MaxiGISAS00",  "MagneticCylindersBuilder", 10);
    std::cout << "TestPerformance::TestPerformance() -> Info. Preparing to run "
              << m_tests.size() << " performance tests."  << std::endl;
}


TestPerformance::~TestPerformance()
{
}


void TestPerformance::add(const std::string &name, const std::string &simulation_name,
                          const std::string &sample_builder, size_t nrepetitions)
{
    m_tests.push_back(PerfTest(name, simulation_name, sample_builder, nrepetitions));
}




void TestPerformance::execute()
{

    init_sysinfo();
    for(size_t i=0; i<m_tests.size(); ++i) {
        PerfTest *test = &m_tests[i];
        runTest(test);
    }

    write_results();
}


void TestPerformance::runTest(PerfTest *test)
{
    SimulationRegistry simulationRegistry;
    SampleBuilderFactory sampleFactory;

    std::cout << "Running test: " << std::setw(20) << std::left << test->m_test_name << " ... ";
    std::cout.flush();

    boost::scoped_ptr<Simulation> simulation(simulationRegistry.createSimulation(test->m_simulation_name));
    SampleBuilder_t sample = sampleFactory.createBuilder(test->m_sample_builder_name);

    TBenchmark mb;
    mb.Start("test");

    for(size_t i=0; i<test->m_nrepetitions; ++i) {
        simulation->setSampleBuilder(sample);
        simulation->runSimulation();
    }

    mb.Stop("test");
    test->m_cpu_time = mb.GetCpuTime("test");
    test->m_real_time = mb.GetRealTime("test");

    std::cout << boost::format("OK: %-6.3f (real sec), %-6.3f (cpu sec) ") % test->m_real_time % test->m_cpu_time << std::endl;
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
        file  << boost::format(" %-12s |") %  Utils::AdjustStringLength(m_tests[i].m_test_name, 12);
    }
    file << std::endl;
}

//! write results of performance measurements
void TestPerformance::write_performance(std::ofstream &file)
{
    file << boost::format("| %-19s | %-10s | %-13s | %-2d |") %  m_datime % m_hostname % m_sysinfo % 0;
    double sum_real(0), sum_cpu(0);
    for(size_t i=0; i<m_tests.size(); ++i) {
        sum_real += m_tests[i].m_real_time;
        sum_cpu += m_tests[i].m_cpu_time;
    }
    file  << boost::format(" %-8.3f |") %  sum_real;

    for(size_t i=0; i<m_tests.size(); ++i) {
        file  << boost::format(" %-12.3f |") %  m_tests[i].m_real_time;
    }
    file << std::endl;
}


//! read sustem information and store it in the test
void TestPerformance::init_sysinfo()
{
    // saving date and time
    TDatime td;
    m_datime = std::string(td.AsSQLString());

    // saving host name
    std::string hostname(gSystem->HostName());
    // stripping host name after first '.' (somehost.jcns.frm2 -> somehost)
    std::string::size_type pos = hostname.find_first_of('.');
    if(pos != std::string::npos) {
        hostname.erase(pos,hostname.size()-pos);
    }
    m_hostname = hostname;

    // saving hardware information
    SysInfo_t sys_info;
    int status = gSystem->GetSysInfo(&sys_info);
    if( status == -1) {
        m_sysinfo = std::string("Unknown hardware");
    }else{
        std::ostringstream os;
        os << std::string(gSystem->GetBuildArch());
        //os << std::string(gSystem->GetBuildArch()) << ", "<< sys_info.fCpuSpeed << " MHz";
        //os << ", " << 	sys_info.fL2Cache << " Kb";
        m_sysinfo = os.str();
    }
}


// -----------------------------------------------------------------------------
// General PerformanceTest
// -----------------------------------------------------------------------------

//! run performance measurements
//void PerformanceTest::execute()
//{
//    TBenchmark mb;
//    mb.Start( getName().c_str() );

//    runTests();

//    mb.Stop( getName().c_str() );

//    m_cpu_time = mb.GetCpuTime(getName().c_str());
//    m_real_time = mb.GetRealTime(getName().c_str());
//}


////! run standard simulation
//void PerformanceTest::runTests()
//{
//    SimulationRegistry registry;
//    Simulation *simulation = registry.createSimulation(getName());
//    simulation->setProgramOptions(mp_options);
//    for(int i=0; i<m_nrepetitions; i++){
//        simulation->runSimulation();
//    }
//    delete simulation;
//}

//// -----------------------------------------------------------------------------
//// custom PerformanceTest's
//// -----------------------------------------------------------------------------

//void SpecularMatrixPerformanceTest::runTests()
//{
//    MultiLayer *ml = dynamic_cast<MultiLayer *>(SampleFactory::createSample("SimpleMultilayer"));

//    for(int i=0; i<m_nrepetitions; i++){
//        static double alpha_i = -0.3;
//        kvector_t kvec;
//        kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
//        SpecularMatrix::MultiLayerCoeff_t coeffs;
//        SpecularMatrix matrixCalculator;
//        matrixCalculator.execute(*ml, kvec, coeffs);
//    }
//    delete ml;
//}

//void SpecularMagneticPerformanceTest::runTests()
//{
//    MultiLayer *ml = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MultilayerSpecularMagneticTestCase"));

//    for(int i=0; i<m_nrepetitions; i++){
//        static double alpha_i = -0.3;
//        kvector_t kvec;
//        kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
//        SpecularMagnetic::MultiLayerCoeff_t coeffs;
//        SpecularMagnetic magneticCalculator;
//        magneticCalculator.execute(*ml, kvec, coeffs);
//    }
//    delete ml;
//}


