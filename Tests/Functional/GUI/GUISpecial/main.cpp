// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/main.cpp
//! @brief     Implements main to run GUI special tests.
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
#include "GUISpecialTestFactory.h"

//! Runs PyEmbedded functional test.
int main(int argc, char** argv)
{
    return TestService<GUISpecialTestFactory>().execute(argc, argv) ? 0 : 1;
}
