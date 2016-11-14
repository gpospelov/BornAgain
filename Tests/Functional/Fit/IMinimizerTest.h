// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IMinimizerTest.h
//! @brief     Defines class IMinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMINIMIZERTEST_H
#define IMINIMIZERTEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "FitParameterPlan.h"
#include <memory>

class FitSuite;
class MultiLayer;
class GISASSimulation;

//! @class IMinimizerTest
//! @ingroup standard_samples
//! @brief Basic class for all minimizer functional tests

class IMinimizerTest : public IFunctionalTest
{
public:
    IMinimizerTest(const std::string &minimizer_name,
                   const std::string &minimizer_algorithm = std::string());
    virtual ~IMinimizerTest(){}

    bool runTest() final;

    void setParameterTolerance(double value) { m_parameter_tolerance = value; }

protected:
    virtual void initParameterPlan();
    virtual std::unique_ptr<FitSuite> createFitSuite();
    virtual std::unique_ptr<MultiLayer> createSample();
    virtual std::unique_ptr<GISASSimulation> createSimulation();
    virtual std::unique_ptr<OutputData<double>> createOutputData(const GISASSimulation* simulation);

    std::vector<FitParameterPlan> m_parameters;
    std::string m_minimizer_name;
    std::string m_minimizer_algorithm;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
    double m_parameter_tolerance;
};

#endif // IMINIMIZERTEST_H
