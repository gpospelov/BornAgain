// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPerformance2.h
//! @brief     Defines classe TestPerformance2 for logging performance changes
//!
//! @homepage  http://www.bornagainproject.org
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


//! Run standard tests to trace changes in the performance.

class TestPerformance : public IApplicationTest
{
public:
    class PerfTest {
    public:
        PerfTest(const std::string &name, const std::string &simulation_name,
                 const std::string &sample_builder, size_t nrepetitions)
            : m_test_name(name), m_simulation_name(simulation_name)
            , m_sample_builder_name(sample_builder)
            , m_nrepetitions(nrepetitions)
            , m_cpu_time(0.0), m_real_time(0) {}
        std::string m_test_name;
        std::string m_simulation_name;
        std::string m_sample_builder_name;
        size_t m_nrepetitions;
        double m_cpu_time;
        double m_real_time;
    };

    TestPerformance();
    virtual ~TestPerformance();
    virtual void execute();

private:
    void add(const std::string &name, const std::string &simulation_name,
             const std::string &sample_builder, size_t nrepetitions);

    void runTest(PerfTest *test);

    void write_results();
    void write_header(std::ofstream &file);
    void write_performance(std::ofstream &file);
    void init_sysinfo();
    std::vector<PerfTest> m_tests;
    std::string m_datime;
    std::string m_hostname;
    std::string m_sysinfo;
};


#endif
