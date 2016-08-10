// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest.cpp
//! @brief     Implements program GUIStandardTest to run gui functional tests
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

//! Provides a GUITest through a callback mechanism explained in IStandardTest.h.
class GUIStandardTest : public IStandardTest
{
public:
    GUIStandardTest() : IStandardTest("GUIStandardTest") {}
    IFunctionalTest* getTest() const { return new GUITest(
            getName(), getTestDescription(), getSimulation(), getTestThreshold()); }
};

//! Runs GUITest on a standard simulation indicated by argv[1].
int main(int argc, char** argv)
{
    return GUIStandardTest().execute(argc, argv) ? 0 : 1;
}
