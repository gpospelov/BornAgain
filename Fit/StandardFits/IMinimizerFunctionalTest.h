// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardFits/IMinimizerFunctionalTest.h
//! @brief     Defines class IMinimizerFunctionalTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMINIMIZERFUNCTIONALTEST_H
#define IMINIMIZERFUNCTIONALTEST_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include <vector>

//! @class IMinimizerFunctionalTest
//! @ingroup standard_samples
//! @brief Basic class for all minimizer functional tests

class BA_CORE_API_ IMinimizerFunctionalTest : public IFunctionalTest
{
public:
        IMinimizerFunctionalTest(const std::string &minimizer_name, const std::string &minimizer_algorithm);

        void runTest();
        int analyseResults();

        class TestParameter {
        public:
            TestParameter(const std::string &name, double real_value, double start_value, double threshold=0.01);
            std::string m_name;   //!< sample parameter name
            double m_real_value;  //!< real value to construct the sample
            double m_start_value; //!< starting value for the minimizer
            double m_found_value; //!< the value found during the fit
            double m_threshold;   //!< threshold on difference between real and found parameter
        };

protected:
    std::vector<TestParameter> m_parameters;
    std::string m_minimizer_name;
    std::string m_minimizer_algorithm;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
};


#endif
