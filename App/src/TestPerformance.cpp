// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPerformance.cpp 
//! @brief     Implements class TestPerformance.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "TestPerformance.h"
#include "Types.h"
#include "Units.h"
#include "Utils.h"
#include "Exceptions.h"
#include "MultiLayer.h"
#include "MaterialManager.h"
#include "OpticalFresnel.h"
#include "SampleFactory.h"

#include "TSystem.h"
#include "TDatime.h"
#include "TBenchmark.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>

TestPerformance::TestPerformance()
{
    // preparing performance tests to run
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_FresnelCoeff(), 200000) );
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_Pyramid(), 20) );
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_RotatedPyramid(), 20) );
    m_tests.push_back( new PerformanceTestInfo(new PerfTest_MesoCrystal(), 2) );

    std::cout << "TestPerformance::TestPerformance() -> Info. Preparing to run " << m_tests.size() << " performance tests."  << std::endl;

}


TestPerformance::~TestPerformance()
{
    for(performance_tests_t::iterator it=m_tests.begin(); it!= m_tests.end(); ++it) {
        delete (*it);
    }

}

/* ************************************************************************* */
// running performance tests
/* ************************************************************************* */
void TestPerformance::execute()
{
    // getting system information
    get_sysinfo();

    clock_t clock1 = clock();
    //clock_t gt_clock1 = clock_get_time();
    std::cout << "1.1 " << clock1 << std::endl;

    // run tests
    TBenchmark mb;
    for(performance_tests_t::iterator it=m_tests.begin(); it!= m_tests.end(); ++it) {
        PerformanceTestInfo *test_info = (*it);
        std::string test_name = test_info->m_test->getName();

        std::cout << "Running test: " << std::setw(20) << std::left << test_name << " ... ";
        std::cout.flush();
        test_info->m_test->initialise(mp_options);
        mb.Start( test_name.c_str() );
        for(int i=0; i<test_info->m_nrepetitions; i++){
            test_info->m_test->execute();
        }
        mb.Stop( test_name.c_str() );

        // printing results
        double result = mb.GetCpuTime( test_name.c_str() );
        double fhz = double(test_info->m_nrepetitions)/result;
        std::cout << std::setw(6) << std::left << result << " sec, "
                  << std::setw(8) << std::left << fhz << " Hz ("
                  << std::setw(4) << std::left << test_info->m_nrepetitions << " repetitions )"<< std::endl;
        // saving results
        std::ostringstream os;
        os << std::setprecision(6)  << fhz;
        m_performance_info[test_name] = os.str();
    }

    write_performance();

    clock_t clock2 = clock();
    std::cout << "1.2 " << clock2 << std::endl;
    std::cout << "1.3 " << clock2-clock1 << std::endl;

}


/* ************************************************************************* */
// save performance information
/* ************************************************************************* */
void TestPerformance::write_performance()
{
    // appending performance information to the file
    std::string filename = Utils::FileSystem::GetHomePath() +
        "./dev-tools/log/perf_history.txt";

    std::ofstream file;
    file.open(filename.c_str(), std::ios_base::app);
    if( !file.is_open() ) {
        throw FileNotIsOpenException("TestPerformance::execute() -> Error. Can't open file '"+filename+"' for writing.");
    }

    file << m_performance_info["datime"] << get_delimeter();
    file << std::left << Utils::AdjustStringLength(m_performance_info["hostname"],10) << get_delimeter();
    file << std::left << Utils::AdjustStringLength(m_performance_info["sysinfo"],23) << get_delimeter();
    for(performance_tests_t::iterator it=m_tests.begin(); it!= m_tests.end(); ++it) {
        std::string test_name = (*it)->m_test->getName();
        file << std::left << Utils::AdjustStringLength(m_performance_info[test_name],7) << get_delimeter();
    }
    file<<std::endl;

    file.close();

    std::cout << "TestPerformance::write_performance() -> Info. File '" << filename << "' is updated." << std::endl;
}


/* ************************************************************************* */
// fill system information
/* ************************************************************************* */
void TestPerformance::get_sysinfo()
{
    // saving date and time
    TDatime td;
    m_performance_info["datime"] = std::string(td.AsSQLString());

    // saving host name
    std::string hostname(gSystem->HostName());
    // stripping host name after first '.' (somehost.jcns.frm2 -> somehost)
    std::string::size_type pos = hostname.find_first_of('.');
    if(pos != std::string::npos) {
        hostname.erase(pos,hostname.size()-pos);
    }
    m_performance_info["hostname"] = hostname;

    // saving hardware information
    //std::string sysinfo;
    SysInfo_t sys_info;
    int status = gSystem->GetSysInfo(&sys_info);
    if( status == -1) {
        std::cout << "TestPerformance::get_sysinfo() -> Warning! Can't get system info." << std::endl;
        m_performance_info["sysinfo"] = std::string("failed");
    }else{
        std::ostringstream os;
        os << std::string(gSystem->GetBuildArch()) << ", "<< sys_info.fCpuSpeed << " MHz";

        //os << ", " << 	sys_info.fL2Cache << " Kb";
        m_performance_info["sysinfo"] = os.str();
    }
}


/* ************************************************************************* */
// our test starts here:  PerfTest_FresnelCoeff
/* ************************************************************************* */
void PerfTest_FresnelCoeff::initialise(ProgramOptions *p_options)
{
    IFunctionalTest::initialise(p_options);
    if(m_sample) delete m_sample;
    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("SimpleMultilayer"));
}

void PerfTest_FresnelCoeff::execute()
{
    static double alpha_i = -0.3;
    kvector_t kvec;
    kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);
    OpticalFresnel::MultiLayerCoeff_t coeffs;
    OpticalFresnel fresnelCalculator;
    MultiLayer *ml = dynamic_cast<MultiLayer *>(m_sample);
    fresnelCalculator.execute(*ml, kvec, coeffs);
}


/* ************************************************************************* */
// our test starts here:  PerfTest_Pyramid
/* ************************************************************************* */
void PerfTest_Pyramid::initialise(ProgramOptions *p_options)
{
    IFunctionalTest::initialise(p_options);
    // sample
    if(m_sample) delete m_sample;
    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("IsGISAXS9_Pyramid"));

    // simulation
    if(m_simulation) delete m_simulation;
    m_simulation = new Simulation(mp_options);
    m_simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    m_simulation->setSample(*m_sample);
}

void PerfTest_Pyramid::execute()
{
    m_simulation->runSimulation();
}


/* ************************************************************************* */
// our test starts here:  PerfTest_RotatedPyramid
/* ************************************************************************* */
void PerfTest_RotatedPyramid::initialise(ProgramOptions *p_options)
{
    IFunctionalTest::initialise(p_options);
    // sample
    if(m_sample) delete m_sample;
    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("IsGISAXS9_RotatedPyramid"));

    // simulation
    if(m_simulation) delete m_simulation;
    m_simulation = new Simulation(p_options);
    m_simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    m_simulation->setSample(*m_sample);
}

void PerfTest_RotatedPyramid::execute()
{
    m_simulation->runSimulation();

}

/* ************************************************************************* */
// our test starts here:  PerfTest_MesoCrystal
/* ************************************************************************* */
void PerfTest_MesoCrystal::initialise(ProgramOptions *p_options)
{
    IFunctionalTest::initialise(p_options);
    // sample
    if(m_sample) delete m_sample;
    m_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample("MesoCrystal1"));

    // simulation
    m_simulation = new Simulation(p_options);
    m_simulation->setSample(*m_sample);
    m_simulation->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    m_simulation->setBeamParameters(0.77*Units::angstrom, -0.4*Units::degree, 0.0*Units::degree);

}

void PerfTest_MesoCrystal::execute()
{
    m_simulation->runSimulation();
}
