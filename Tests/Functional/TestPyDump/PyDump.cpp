// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Futests/TestPyCore/PySuite.cpp
//! @brief     Implements program PySuite, to run pyscript functional tests
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
#include "PyScriptFutest.h"

//! Program PySuite, to run pyscript functional tests.

int main(int argc, char** argv)
{
    FutestSuite suite("PySuite", [] (const FutestSuite* s) -> IFutest* {
            return new PyScriptFutest(
                s->getTestName(), s->getTestDescription(),
                s->getSimulation(), s->getTestThreshold()); } );
    return suite.execute(argc, argv);
}
