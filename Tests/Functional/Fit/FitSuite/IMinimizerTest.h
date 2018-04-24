// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IMinimizerTest.h
//! @brief     Defines class IMinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMINIMIZERTEST_H
#define IMINIMIZERTEST_H

#include "IFittingTest.h"

//! @class IMinimizerTest
//! @ingroup standard_samples
//! @brief Basic class for all minimizer functional tests

class IMinimizerTest : public IFittingTest
{
public:
    IMinimizerTest(const std::string &minimizer_name,
                   const std::string &minimizer_algorithm = std::string());
    virtual ~IMinimizerTest();

protected:
    void initParameterPlan() override;
};

#endif // IMINIMIZERTEST_H
