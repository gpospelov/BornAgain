// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/IFunctionalTest.h
//! @brief     Defines class IFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ADVANCEDFUNCTIONALTEST_H
#define ADVANCEDFUNCTIONALTEST_H

#include "GISASSimulation.h"

//! @class IAdvancedFunctionalTest
//! @ingroup standard_samples
//! @brief Interface to the functional tests

class BA_CORE_API_ IAdvancedFunctionalTest
{
public:
    enum ETestResult { SUCCESS, FAILED};
    virtual ~IAdvancedFunctionalTest() {}
    virtual void runTest() = 0;
    virtual int analyseResults() = 0;
};


//! @class AdvancedFunctionalTest
//! @ingroup standard_samples
//! @brief Basic functional test

class BA_CORE_API_ AdvancedFunctionalTest : public IAdvancedFunctionalTest
{
public:

    AdvancedFunctionalTest(const std::string &name, GISASSimulation *simulation, OutputData<double> *reference, double threshold);
    ~AdvancedFunctionalTest();

    void runTest();
    int analyseResults();

private:
    std::string m_name;
    GISASSimulation *m_simulation;
    OutputData<double> *m_reference;
    double m_threshold;
};

//! @class AdvancedFunctionalMultiTest
//! @ingroup standard_samples
//! @brief Functional multi test constructs the collection of standard functional tests using component service,
//! runs them one-by-one, and then reports results in single table.

class BA_CORE_API_ AdvancedFunctionalMultiTest : public IAdvancedFunctionalTest
{
public:
    AdvancedFunctionalMultiTest();
    void runTest();
    int analyseResults();

private:
};

#endif
