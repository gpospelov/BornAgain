// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPerformance2.h
//! @brief     Defines classe TestPerformance2 for logging performance changes
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPERFORMANCE2_H
#define TESTPERFORMANCE2_H

#include "IApplicationTest.h"
#include "INamed.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

class PerformanceTest;

//! Run standard tests to trace changes in the performance.

class TestPerformance2 : public IApplicationTest
{
public:
    TestPerformance2();
    virtual ~TestPerformance2();
    virtual void execute();
private:
    void write_results();
    void write_header(std::ofstream &file);
    void write_performance(std::ofstream &file);
    void set_sysinfo(PerformanceTest *test);
    std::vector<PerformanceTest *> m_tests;
};


//! class for performance measurements
class PerformanceTest : public IApplicationTest {
public:
    PerformanceTest(const std::string &name, int nrepetitions)
        : IApplicationTest(name)
        , m_nrepetitions(nrepetitions)
        , m_nthreads(0)
        , m_cpu_time(0)
        , m_real_time(0){}

    virtual ~PerformanceTest(){}

    virtual void execute();
    virtual void runTests();

    double m_nrepetitions;
    int m_nthreads;
    double m_cpu_time;
    double m_real_time;
    std::string m_datime;
    std::string m_hostname;
    std::string m_sysinfo;
};


//! custom test for specular matrix
class SpecularMatrixPerformanceTest : public PerformanceTest
{
public:
    SpecularMatrixPerformanceTest(const std::string &name, int nrepetitions)
        : PerformanceTest(name, nrepetitions){}
    virtual void runTests();
};

//! custom test for specular magnetic
class SpecularMagneticPerformanceTest : public PerformanceTest
{
public:
    SpecularMagneticPerformanceTest(const std::string &name, int nrepetitions)
        : PerformanceTest(name, nrepetitions){}
    virtual void runTests();
};


#endif
