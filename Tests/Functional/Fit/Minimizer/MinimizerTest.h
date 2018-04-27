// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTest.h
//! @brief     Defines class MinimizerTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MINIMIZERTEST_H
#define MINIMIZERTEST_H

#include "IFunctionalTest.h"
#include <string>

//! Collection of standalone tests for fitting library.

class MinimizerTest : public IFunctionalTest
{
public:
    MinimizerTest(const std::string& minimizer_name, const std::string& algorithm_name,
                  const std::string& fit_plan_name);

    bool runTest();

protected:
    std::string m_minimizer_name;
    std::string m_algorithm_name;
    std::string m_fit_plan_name;
};

#endif // MINIMIZERTEST_H
