// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITestSuite.cpp
//! @brief     Implements program GUITestSuite to run gui functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IStandardTest.h"
#include "GUITest.h"

class GUITestSuite : public IStandardTest
{
public:
    GUITestSuite() : IStandardTest("GUITestSuite") {}
    IFunctionalTest* getTest() const { return new GUITest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! The main function of GUITestTestSuite, to run functional tests
int main(int argc, char** argv)
{
    return GUITestSuite().execute(argc, argv);
}
