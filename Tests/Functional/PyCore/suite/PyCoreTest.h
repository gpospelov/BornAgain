// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/PyCoreTest.h
//! @brief     Declares class PyCoreTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSUITETEST_H
#define PYSUITETEST_H

#include "IFunctionalTest.h" // inheriting from
#include "OutputData.h"

//! @class PyCoreTest
//! @ingroup standard_samples
//! @brief A functional test of PyCore (the Python wrapper of BornAgain/Core).
//!   Performs a given standard simulation, both directly and from a Python dump.
//!   Invoked from PyCoreStandardTest.

class PyCoreTest : public IFunctionalTest
{
public:
    PyCoreTest(const std::string& name, const std::string& description,
                class GISASSimulation* reference_simulation, double threshold);
    virtual ~PyCoreTest();

    virtual void runTest();
    virtual int analyseResults();

    const OutputData<double>* getOutputData() const;

    double getDifference() const { return m_difference; }

    virtual void printResults(std::ostream& ostr) const;

private:
    std::string getPySuiteFileNameAndPath() const;

    class GISASSimulation* m_reference_simulation;
    class GISASSimulation* m_domain_simulation;
    double m_threshold;
    double m_difference;
    std::string m_pyscript_filename;
    std::string m_output_filename;
};

#endif // PYSUITETEST_H
