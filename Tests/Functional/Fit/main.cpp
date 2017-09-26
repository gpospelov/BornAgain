// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/main.cpp
//! @brief     Implements program FitTest to run fit functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestService.h"
#include "StandardFitsFactory.h"

//! Runs functional tests.

int main(int argc, char **argv)
{
    return TestService<StandardFitsFactory>().execute(argc, argv) ? 0 : 1;
}
