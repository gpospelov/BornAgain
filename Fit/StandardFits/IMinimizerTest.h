// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/StandardFits/IMinimizerTest.h
//! @brief     Declares class IMinimizerTest.
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
#include <vector>
#include <memory>

class IMinimizer;
class FitSuite;
class ISample;
class GISASSimulation;

//! @class IMinimizerTest
//! @ingroup standard_samples
//! @brief Basic class for all minimizer functional tests

class BA_CORE_API_ IMinimizerTest : public IFunctionalTest
{
public:
    IMinimizerTest(const std::string &minimizer_name,
                             const std::string &minimizer_algorithm = std::string());
    virtual ~IMinimizerTest(){}

    void runTest();
    int analyseResults();

    class TestParameter
    {
    public:
        TestParameter(const std::string &name, double real_value, double start_value);
        std::string m_name;   //!< sample parameter name
        double m_real_value;  //!< real value to construct the sample
        double m_start_value; //!< starting value for the minimizer
        double m_found_value; //!< the value found during the fit
    };

    void setParameterTolerance(double value);

protected:
    virtual std::unique_ptr<FitSuite> createFitSuite();
    virtual std::unique_ptr<ISample> createSample();
    virtual std::unique_ptr<GISASSimulation> createSimulation();
    virtual std::unique_ptr<OutputData<double> > createOutputData(const GISASSimulation *simulation);

    std::vector<TestParameter> m_parameters;
    std::string m_minimizer_name;
    std::string m_minimizer_algorithm;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
    double m_parameter_tolerance;
};

#endif // IMINIMIZERTEST_H
