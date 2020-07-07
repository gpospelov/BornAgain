// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTestFactory.h
//! @brief     Defines class MinimizerTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_MINIMIZERTESTFACTORY_H
#define BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_MINIMIZERTESTFACTORY_H

#include "Tests/Functional/TestMachinery/FunctionalTestFactory.h"

//! Factory to generate standalone fit tests.

class MinimizerTestFactory : public FunctionalTestFactory
{
public:
    MinimizerTestFactory();
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_MINIMIZERTESTFACTORY_H
