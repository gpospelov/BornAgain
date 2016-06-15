// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/TestMachinery/CoreFutest.h
//! @brief     Declares class CoreFutest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COREFUNCTIONALTEST_H
#define COREFUNCTIONALTEST_H

#include "WinDllMacros.h"
#include "OutputData.h"
#include "IFutest.h"

class GISASSimulation;

//! @class CoreFutest
//! @ingroup standard_samples
//! @brief Core functional test  compares results of the standard simulation with
//! reference intensity data. Normally invoked by FunctionalMultiTest.

class BA_CORE_API_ CoreFutest : public IFutest
{
public:
    CoreFutest(
        const std::string& name, const std::string& description, GISASSimulation* simulation,
        double threshold);
    virtual ~CoreFutest();

    virtual void runTest();
    virtual int analyseResults();
    virtual void printResults(std::ostream& ostr) const;

private:
    std::string getSimulationResultsFileNameAndPath() const;
    OutputData<double>* getIntensityData() const;

    GISASSimulation* m_simulation;
    double m_threshold;
    OutputData<double>* m_reference;
    double m_difference;
    std::string m_ref_filename;
    };

#endif
