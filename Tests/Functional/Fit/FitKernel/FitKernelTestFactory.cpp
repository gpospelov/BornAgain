// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/StandardFitsFactory.cpp
//! @brief     Implements class StandardFitsFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitKernelTestFactory.h"
#include "StandaloneFitTest.h"

FitKernelTestFactory::FitKernelTestFactory()
{
    registerItem(
        "StandaloneFit",
        create_new<StandaloneFitTest>,
                "Test of standalone fit of arbitrary functions");
}
