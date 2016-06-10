// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/core_functional_test.h
//! @brief     Implements program CoreSuite, to run core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FutestSuite.h"
#include "FutestRegistry.h"
#include "CoreFutest.h"

//! Program CoreSuite, to run core functional tests.
int main(int argc, char** argv)
{
    FutestSuite suite("CoreSuite", [] (const FutestSuite* s) -> IFutest* {
            return new CoreFutest(
        s->getTestName(), s->getTestDescription(), s->getSimulation(),
        s->getReferenceData(), s->getTestThreshold(), s->getReferenceFileName()); } );
    return suite.execute(argc, argv);
}
