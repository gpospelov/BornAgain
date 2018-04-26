// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitKernelTestFactory.h
//! @brief     Defines class FitKernelTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITKERNELTESTFACTORY_H
#define FITKERNELTESTFACTORY_H

#include "FunctionalTestFactory.h"

//! Factory to generate standalone fit tests.

class FitKernelTestFactory : public FunctionalTestFactory
{
public:
    FitKernelTestFactory();
};

#endif // FITKERNELTESTFACTORY_H
