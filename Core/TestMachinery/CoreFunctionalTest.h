// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFunctionalTest.h
//! @brief     Declares class CoreFunctionalTest.
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
#include "IFunctionalTest.h"

class GISASSimulation;

//! @class CoreFunctionalTest
//! @ingroup standard_samples
//! @brief Core functional test  compares results of the standard simulation with
//! reference intensity data. Normally invoked by FunctionalMultiTest.

class BA_CORE_API_ CoreFunctionalTest : public IFunctionalTest
{
public:
    CoreFunctionalTest(const std::string &name, const std::string &description,
                       GISASSimulation *simulation, OutputData<double> *reference,
                       double threshold);
    virtual ~CoreFunctionalTest();

    virtual void runTest();
    virtual int analyseResults();
    virtual void printResults(std::ostream &ostr) const;

    void setSimulationResultsFileName(const std::string &file_name);

private:
    void saveSimulationResults() const;
    std::string getSimulationResultsFileNameAndPath() const;
    OutputData<double>* getIntensityData() const;

    GISASSimulation *m_simulation;
    OutputData<double> *m_reference;
    double m_threshold;
    double m_difference;
    //!< The name of file to save simulation results if test failed.
    std::string m_simulation_results_file_name;
};


#endif
