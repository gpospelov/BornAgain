// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSuite.cpp
//! @brief     Implements program CoreSuite, to run core functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "CoreTest.h"

class CoreTestSuite : public IStandardTest
{
public:
    CoreTestSuite() : IStandardTest("CoreTestSuite") {}
    IFunctionalTest* getTest() const { return new CoreTest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold() ); }
};

//! The main function of CoreTestSuite, to run functional tests
int main(int argc, char** argv)
{
    return CoreTestSuite().execute(argc, argv);
}
