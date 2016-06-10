// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/FunctionalTests/TestGUI/GUISuite/GUITestSuite.cpp
//! @brief     Implements program GUISuite to run gui functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FutestSuite.h"
#include "FunctionalTestRegistry.h"
#include "GUIFunctionalTest.h"

//! The main function of GUITestSuite to run functional tests
int main(int argc, char** argv)
{
    FutestSuite suite("GUISuite", [] (const FutestSuite* s) -> IFunctionalTest* {
            return new GUIFunctionalTest(
                s->getTestName(), s->getTestDescription(),
                s->getSimulation(), s->getTestThreshold()); } );
    return suite.execute(argc, argv);
}
