// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/MesoCrystalPerformanceTest.h
//! @brief     Defines MesoCrystalPerformanceTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_MESOCRYSTALPERFORMANCETEST_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_MESOCRYSTALPERFORMANCETEST_H

#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! Runs heavy mesocrystal simulation to investigate where it spends time.

class MesoCrystalPerformanceTest : public IFunctionalTest
{
protected:
    bool runTest();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_MESOCRYSTALPERFORMANCETEST_H
