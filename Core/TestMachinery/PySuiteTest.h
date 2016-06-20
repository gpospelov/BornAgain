// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/PySuiteTest.h
//! @brief     Declares class PySuiteTest
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
#include "IFutest.h"
#include "OutputData.h"
#include <string>

class GISASSimulation;

//! @class PySuiteTest
//! @ingroup standard_samples
//! @brief Test whether Python dumps yields the same image as a direct computation.

class BA_CORE_API_ PySuiteTest : public IFutest
{
public:
    PySuiteTest(const std::string& name, const std::string& description,
                   GISASSimulation* reference_simulation, double threshold);
    virtual ~PySuiteTest();

    virtual void runTest();
    virtual int analyseResults();

    const OutputData<double>* getOutputData() const;

    double getDifference() const { return m_difference;}

    virtual void printResults(std::ostream& ostr) const;

private:
    std::string getPySuiteFileNameAndPath() const;

    GISASSimulation* m_reference_simulation;
    GISASSimulation* m_domain_simulation;
    double m_threshold;
    double m_difference;
    std::string m_pyscript_filename;
    std::string m_output_filename;
};

#endif
