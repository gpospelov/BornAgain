// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/IObsoleteMinimizerTest.h
//! @brief     Defines class IObsoleteMinimizerTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IOBSOLETEMINIMIZERTEST_H
#define IOBSOLETEMINIMIZERTEST_H

#include "IObsoleteFittingTest.h"

//! @class IMinimizerTest
//! @ingroup standard_samples
//! @brief Basic class for all minimizer functional tests

class IObsoleteMinimizerTest : public IObsoleteFittingTest
{
public:
    IObsoleteMinimizerTest(const std::string &minimizer_name,
                   const std::string &minimizer_algorithm = std::string());
    virtual ~IObsoleteMinimizerTest();

protected:
    void initParameterPlan() override;
};

#endif // IOBSOLETEMINIMIZERTEST_H
