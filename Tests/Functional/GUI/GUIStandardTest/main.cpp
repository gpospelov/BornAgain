// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/main.cpp
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

#include "StandardTestService.h"
#include "GUIStandardTest.h"

//! Runs GUIStandardTest on a standard simulation indicated by argv[1].

int main(int argc, char** argv)
{
    return StandardTestService<GUIStandardTest>().execute(argc, argv) ? 0 : 1;
}
