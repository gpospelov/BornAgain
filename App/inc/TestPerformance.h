// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPerformance2.h
//! @brief     Defines classe TestPerformance2 for logging performance changes
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPERFORMANCE_H
#define TESTPERFORMANCE_H

#include "IApplicationTest.h"
#include "INamed.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

class PerformanceTest;

//! Run standard tests to trace changes in the performance.

class TestPerformance : public IApplicationTest
{
public:
    TestPerformance();
    virtual ~TestPerformance();
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
