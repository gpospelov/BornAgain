// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitObjectiveTest.h
//! @brief     Defines class FitObjectiveTest
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITOBJECTIVETEST_H
#define FITOBJECTIVETEST_H

#include "IFunctionalTest.h"

//! Collection of standalone tests for fitting library.

class FitObjectiveTest : public IFunctionalTest
{
public:
    FitObjectiveTest();

    bool runTest();

};

#endif // FITOBJECTIVETEST_H
