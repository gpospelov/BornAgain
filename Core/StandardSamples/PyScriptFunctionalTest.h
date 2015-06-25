// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/PyScriptFunctionalTest.h
//! @brief     Defines class PyScriptFunctionalTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIFUNCTIONALTEST_H
#define GUIFUNCTIONALTEST_H

#include "WinDllMacros.h"
#include "IFunctionalTest.h"
#include "OutputData.h"
#include <string>

class GISASSimulation;

//! @class PyScriptFunctionalTest
//! @ingroup standard_samples
//! @brief GUI functional test  compares results of the reference simulation with
//! the one obtained through domain->GUI->domain convertion. Normally invoked by
//! FunctionalMultiTest.

class BA_CORE_API_ PyScriptFunctionalTest : public IFunctionalTest
{
public:

    PyScriptFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *reference_simulation, double threshold);
    ~PyScriptFunctionalTest();

    void runTest();
    int analyseResults();

    const OutputData<double>* getOutputData() const;

    double getDifference() const { return m_difference;}

    void printResults(std::ostream &ostr) const;

private:
    void runPyScriptSimulation();

    GISASSimulation *m_reference_simulation;
    GISASSimulation *m_domain_simulation;
    double m_threshold;
    double m_difference;
};

#endif

