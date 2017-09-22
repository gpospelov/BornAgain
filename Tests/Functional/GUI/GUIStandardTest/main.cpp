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

#include "TestService.h"
#include "GUIReferencedTest.h"

//! Runs GUITest on a standard simulation indicated by argv[1].

int main(int argc, char** argv)
{
    return TestService<GUIReferencedTest>().execute(argc, argv) ? 0 : 1;
}
