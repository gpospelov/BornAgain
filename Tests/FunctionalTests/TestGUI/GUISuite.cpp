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
#include "FunctionalMultiTest.h"

//! The main function of GUITestSuite to run functional tests
int main(int argc, char** argv)
{
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);

    const FunctionalTestInfo* info =
        FunctionalTestRegistry::instance().getItemOrExplain(test_name, "GUISuite");
    if( !info )
        return 1;

    FutestSuite service(info, [] (const FutestSuite* s) -> IFunctionalTest* {
            return new GUIFunctionalTest(
                s->getTestName(), s->getTestDescription(),
                s->getSimulation(), s->getTestThreshold()); } );
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
