// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPerformance.h 
//! @brief     Defines classes TestPerformance, PerfTest_FresnelCoeff.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTPERFORMANCE_H
#define TESTPERFORMANCE_H

#include "IFunctionalTest.h"
#include "ISample.h"
#include "Simulation.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

//! Run standard tests to trace changes in the performance.

class TestPerformance : public IFunctionalTest
{
public:
    //! class to hold performance information over functional test
    class PerformanceTestInfo {
    public:
        PerformanceTestInfo(IFunctionalTest *test, int nrepetitions)
            : m_test(test), m_nrepetitions(nrepetitions), m_results(0){}
        virtual ~PerformanceTestInfo(){ delete m_test; }
        IFunctionalTest *m_test;
        double m_nrepetitions;
        double m_results;
    };

    typedef std::vector<PerformanceTestInfo *> performance_tests_t;

    TestPerformance();
    virtual ~TestPerformance();

    virtual void execute();
private:
    //! fill system information
    void get_sysinfo();

    //! save performance information on disk
    void write_performance();

    //! return delimeter between columns
    std::string get_delimeter() { return std::string(" | "); }

    std::map<std::string, std::string > m_performance_info; //!< holds system information
    performance_tests_t m_tests; //!< list of tests for performance measurements

};


//! @class PerfTest_FresnelCoeff
//! measurement of the performance in Fresnel coefficients calculation
class PerfTest_FresnelCoeff : public IFunctionalTest
{
public:
    PerfTest_FresnelCoeff() : IFunctionalTest("Fresnel"), m_sample(0){}
    virtual ~PerfTest_FresnelCoeff() { }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
};

//! @class PerfTest_Pyramid
//! measurement of the performance in pyramid form factor calculations
class PerfTest_Pyramid : public IFunctionalTest
{
public:
    PerfTest_Pyramid()
        : IFunctionalTest("Pyramid"), m_sample(0), m_simulation(0) {}
    virtual ~PerfTest_Pyramid() { delete m_simulation; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    Simulation *m_simulation;
};

//! @class PerfTest_RotatedPyramid
//! measurement of the performance in pyramid formfactor and in rotation mechanism
class PerfTest_RotatedPyramid : public IFunctionalTest
{
public:
    PerfTest_RotatedPyramid()
        : IFunctionalTest("RotatedPyramid"), m_sample(0), m_simulation(0) {}
    virtual ~PerfTest_RotatedPyramid() { delete m_simulation; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    Simulation *m_simulation;
};


//! @class PerfTest_MesoCrystal
//! measurement of the performance iof meso crystal
class PerfTest_MesoCrystal : public IFunctionalTest
{
public:
    PerfTest_MesoCrystal()
        : IFunctionalTest("MesoCrystal"), m_sample(0), m_simulation(0) {}
    virtual ~PerfTest_MesoCrystal() { delete m_simulation; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    Simulation *m_simulation;
};

#endif // TESTPERFORMANCE_H
