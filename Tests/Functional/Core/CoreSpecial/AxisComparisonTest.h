// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/AxisComparisonTest.h
//! @brief     Defines class AxisComparisonTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef AXISCOMPARISONTEST_H
#define AXISCOMPARISONTEST_H

#include "IFunctionalTest.h"
#include <memory>

class IAxis;
class Simulation;

class AxisComparisonTest : public IFunctionalTest
{
public:
    AxisComparisonTest();
    ~AxisComparisonTest() override;
    static std::unique_ptr<Simulation> createSimulation(const IAxis& axis);

private:
    bool runTest() override;
};

#endif // AXISCOMPARISONTEST_H
