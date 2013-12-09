// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPerformance.h
//! @brief     Defines classes TestPerformance, PerfTest_SpecularMatrix,
//!            PerfTest_Pyramid, PerfTest_RotatedPyramid, PerfTest_MesoCrystal
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

#include "IApplicationTest.h"
#include "ISample.h"
#include "Simulation.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

//! Run standard tests to trace changes in the performance.

class TestPerformance : public IApplicationTest
{
public:
    //! class to hold performance information over functional test
    class PerformanceTestInfo {
    public:
        PerformanceTestInfo(IApplicationTest *test, int nrepetitions)
            : m_test(test), m_nrepetitions(nrepetitions), m_results(0){}
        virtual ~PerformanceTestInfo(){ delete m_test; }
        IApplicationTest *m_test;
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

    //! Returns delimeter between columns.
    std::string get_delimeter() { return std::string(" | "); }

    std::map<std::string, std::string > m_performance_info; //!< holds system information
    performance_tests_t m_tests; //!< list of tests for performance measurements

};


//! @class PerfTest_SpecularMatrix
//! measurement of the performance in specular matrix calculation
class PerfTest_SpecularMatrix : public IApplicationTest
{
public:
    PerfTest_SpecularMatrix() : IApplicationTest("SpecularMatrix"), m_sample(0){}
    virtual ~PerfTest_SpecularMatrix() { }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
};

//! @class PerfTest_Pyramid
//! measurement of the performance in pyramid form factor calculations
class PerfTest_Pyramid : public IApplicationTest
{
public:
    PerfTest_Pyramid()
        : IApplicationTest("Pyramid"), m_sample(0), m_simulation(0) {}
    virtual ~PerfTest_Pyramid() { delete m_simulation; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    Simulation *m_simulation;
};

//! @class PerfTest_RotatedPyramid
//! measurement of the performance in pyramid formfactor and in rotation mechanism
class PerfTest_RotatedPyramid : public IApplicationTest
{
public:
    PerfTest_RotatedPyramid()
        : IApplicationTest("RotatedPyramid"), m_sample(0), m_simulation(0) {}
    virtual ~PerfTest_RotatedPyramid() { delete m_simulation; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    Simulation *m_simulation;
};


//! @class PerfTest_MesoCrystal
//! measurement of the performance iof meso crystal
class PerfTest_MesoCrystal : public IApplicationTest
{
public:
    PerfTest_MesoCrystal()
        : IApplicationTest("MesoCrystal"), m_sample(0), m_simulation(0) {}
    virtual ~PerfTest_MesoCrystal() { delete m_simulation; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    Simulation *m_simulation;
};

#endif // TESTPERFORMANCE_H


