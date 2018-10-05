// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IObsoleteFittingTest.h
//! @brief     Defines class IObsoleteFittingTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IOBSOLETEFITTINGTEST_H_
#define IOBSOLETEFITTINGTEST_H_

#include "IFunctionalTest.h"
#include "FitParameterPlan.h"
#include <memory>

class FitSuite;
class MultiLayer;
template<class T> class OutputData;
class Simulation;


//! @class IFittingTest
//! @ingroup standard_samples
//! @brief Basic class for all fitting functional tests

class IObsoleteFittingTest : public IFunctionalTest
{
public:
    IObsoleteFittingTest(const std::string& minimizer_name, const std::string& minimizer_algorithm,
                 const std::string& simulation_name, const std::string& builder_name);
    virtual ~IObsoleteFittingTest();

    bool runTest() override;

protected:
    virtual void initParameterPlan() = 0;
    virtual std::unique_ptr<FitSuite> createFitSuite();
    virtual std::unique_ptr<MultiLayer> createSample();
    virtual std::unique_ptr<Simulation> createSimulation();
    virtual std::unique_ptr<OutputData<double>> createOutputData(const Simulation* simulation);

    bool analyzeResults(FitSuite& fit_suite) const;

    std::vector<std::unique_ptr<FitParameterPlan>> m_parplans;
    std::string m_minimizer_name;
    std::string m_minimizer_algorithm;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
};


#endif /* IOBSOLETEFITTINGTEST_H_ */
