// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/MinimizerTestFactory.h
//! @brief     Implements class MinimizerTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerTestFactory.h"
#include "MinimizerTestCases.h"

MinimizerTestFactory::MinimizerTestFactory()
{
    registerItem("MinuitTestV1", create_new<MinuitTestV1>, "Minuit + Migrad + Rosenbrock");
}
