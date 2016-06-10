// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/FunctionalTests/TestPyCore/PySuite.cpp
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
#include "FunctionalTestRegistry.h"
#include "FunctionalMultiTest.h"
#include "PyScriptFunctionalTest.h"

//! Program PySuite, to run pyscript functional tests.

int main(int argc, char** argv)
{
    std::string test_name;
    if(argc > 1)
        test_name = std::string(argv[1]);

    const FunctionalTestInfo* info =
        FunctionalTestRegistry::instance().getItemOrExplain(test_name, "PySuite");
    if( !info )
        return 1;

    FutestSuite service(info, [] (const FutestSuite* s) -> IFunctionalTest* {
            return new PyScriptFunctionalTest(
                s->getTestName(), s->getTestDescription(),
                s->getSimulation(), s->getTestThreshold()); } );
    FunctionalMultiTest test(test_name, service);
    test.runTest();
    return test.analyseResults();
}
