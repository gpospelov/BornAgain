// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandaloneFitTest.h
//! @brief     Declares class StandaloneFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef STANDALONEFITTEST_H
#define STANDALONEFITTEST_H

#include "IFunctionalTest.h"
#include "StandaloneFitPlan.h"

//! @class StandaloneFitTest
//! @ingroup standard_samples
//! @brief Collection of standalone tests for fitting library.

class StandaloneFitTest : public IFunctionalTest
{
public:
    StandaloneFitTest();

    bool runTest();

    template<typename T>
    void addTest(const std::string &minimizerName, const std::string &algorithmName);

private:
    bool runPlan(std::shared_ptr<StandaloneFitPlan> plan);

    std::vector<std::shared_ptr<StandaloneFitPlan>> m_plans;
};

template<typename T>
void StandaloneFitTest::addTest(const std::string &minimizerName, const std::string &algorithmName)
{
    m_plans.push_back(
        std::shared_ptr<StandaloneFitPlan>(new StandaloneFitPlan(minimizerName, algorithmName, new T()))
    );
}

#endif // STANDALONEFITTEST_H
