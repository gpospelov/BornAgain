// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.cpp
//! @brief     Implements CoreSpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreSpecialTestFactory.h"
#include "BatchSimulation.h"
#include "PolDWBAMagCylinders.h"
#include "CoreIOTest.h"

CoreSpecialTestFactory::CoreSpecialTestFactory()
{
    registerItem("BatchSimulation",
                 create_new<BatchSimulation>,
                 "Running GISASSimulation in batch mode");

    registerItem("PolDWBAMagCylinders",
                 create_new<PolDWBAMagCylinders>,
                 "Special test for polarized materials");

    registerItem("CoreIO",
                 create_new<CoreIOTest>,
                 "Input/output of heavy files");
}
