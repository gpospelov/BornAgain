#ifndef TESTPERFORMANCE_H
#define TESTPERFORMANCE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   TestPerformance.h
//! @brief  Definition of TestPerformance to run performance test for several predefined tasks
//! @author Scientific Computing Group at FRM II
//! @date   02.07.2012

#include "IFunctionalTest.h"
#include "ISample.h"
#include "GISASExperiment.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

//- -------------------------------------------------------------------
//! @class TestPerformance
//! @brief run standard tests to trace changes in the performance
//- -------------------------------------------------------------------
class TestPerformance : public IFunctionalTest
{
public:
    //! class to hold performance information over functional test
    class PerformanceTestInfo {
    public:
        PerformanceTestInfo(IFunctionalTest *test, int nrepetitions) : m_test(test), m_nrepetitions(nrepetitions), m_results(0){}
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
//! measurement of the performance in fresnel coefficients calculation
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
    PerfTest_Pyramid() : IFunctionalTest("Pyramid"), m_sample(0), m_experiment(0) {}
    virtual ~PerfTest_Pyramid() { delete m_experiment; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    GISASExperiment *m_experiment;
};

//! @class PerfTest_RotatedPyramid
//! measurement of the performance in pyramid formfactor and in rotation mechanism
class PerfTest_RotatedPyramid : public IFunctionalTest
{
public:
    PerfTest_RotatedPyramid() : IFunctionalTest("RotatedPyramid"), m_sample(0), m_experiment(0) {}
    virtual ~PerfTest_RotatedPyramid() { delete m_experiment; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    GISASExperiment *m_experiment;
};


//! @class PerfTest_MesoCrystal
//! measurement of the performance iof meso crystal
class PerfTest_MesoCrystal : public IFunctionalTest
{
public:
    PerfTest_MesoCrystal() : IFunctionalTest("MesoCrystal"), m_sample(0), m_experiment(0) {}
    virtual ~PerfTest_MesoCrystal() { delete m_experiment; }
    void initialise(ProgramOptions *p_options);
    void execute();
    ISample *m_sample;
    GISASExperiment *m_experiment;
};




#endif // TESTPERFORMANCE_H
