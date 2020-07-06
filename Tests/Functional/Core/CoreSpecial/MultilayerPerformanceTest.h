// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/MultilayerPerformanceTest.h
//! @brief     Defines class MultilayerPerformanceTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYERPERFORMANCETEST_H
#define MULTILAYERPERFORMANCETEST_H

#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! Functional test for measuring simulation performance on samples with different number of layers.

class MultilayerPerformanceTest : public IFunctionalTest
{
public:
    ~MultilayerPerformanceTest() override;

private:
    bool runTest() override;
};

#endif // MULTILAYERPERFORMANCETEST_H
