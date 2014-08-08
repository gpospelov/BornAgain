// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.h
//! @brief     Defines class IFunctionalTest.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef _IFUNCTIONALTEST_H
#define _IFUNCTIONALTEST_H


#include "Simulation.h"
#include <boost/shared_ptr.hpp>
#include <string>


//! @class IFunctionalTest
//! @ingroup standard_samples
//! @brief Interface to the functional tests

class BA_CORE_API_ IFunctionalTest
{
public:
    virtual ~IFunctionalTest() {}
    virtual void runTest() =0;
};


//! @class FunctionalTestInfo
//! @ingroup standard_samples
//! @brief Functional test info and description

class BA_CORE_API_ FunctionalTestInfo
{
public:
    FunctionalTestInfo()
        : m_threshold(0) {  }

    FunctionalTestInfo(const std::string &name, const std::string &description,
              const std::string &reference, double threshold, bool normalize = false )
        : m_name(name)
        , m_description(description)
        , m_reference_file(reference)
        , m_threshold(threshold)
        , m_normalize(normalize)
    {  }

    std::string m_name;
    std::string m_description;
    std::string m_reference_file;
    double m_threshold;
    bool m_normalize;
};


//! @class FunctionalTest
//! @ingroup standard_samples
//! @brief Basic functional test

class BA_CORE_API_ FunctionalTest : public IFunctionalTest
{
public:
    enum TestResult { SUCCESS, FAILED};

    FunctionalTest(const FunctionalTestInfo &info);
    ~FunctionalTest();

    Simulation *getSimulation() { return m_simulation; }
    const OutputData<double> *getResult() const { return m_simulation->getOutputData(); }
    const OutputData<double> *getReference() const { return m_reference; }
    std::string getName() const { return m_info.m_name; }
    std::string getDescription() const { return m_info.m_description; }
    void runTest();
    int analyseResults();

private:
    FunctionalTestInfo m_info;
    Simulation *m_simulation;
    OutputData<double> *m_reference;
};

typedef boost::shared_ptr<FunctionalTest> FunctionalTest_t;


#endif
