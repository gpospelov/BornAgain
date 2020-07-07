// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/BatchSimulation.h
//! @brief     Defines BatchSimulation class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_BATCHSIMULATION_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_BATCHSIMULATION_H

#include "Tests/Functional/TestMachinery/IFunctionalTest.h"

//! Special test for simulation running in batch mode.

class BatchSimulation : public IFunctionalTest
{
protected:
    bool runTest();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_CORESPECIAL_BATCHSIMULATION_H
