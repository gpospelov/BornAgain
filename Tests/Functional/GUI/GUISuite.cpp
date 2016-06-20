// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestGUI/GUISuite.cpp
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

#include "FunctionalTestSuite.h"
#include "GUITest.h"

class GUISuite : public FunctionalTestSuite
{
public:
    GUISuite() { setName("GUISuite"); }
    IFutest* getTest() const { return new GUITest(
            getTestName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! The main function of GUITestSuite, to run functional tests
int main(int argc, char** argv)
{
    return GUISuite().execute(argc, argv);
}
