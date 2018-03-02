// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/PolDWBAMagCylinders.h
//! @brief     Defines PolDWBAMagCylinders class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef POLDWBAMAGCYLINDERS_H
#define POLDWBAMAGCYLINDERS_H

#include "IFunctionalTest.h"

//! Special test for polarized materials.

class PolDWBAMagCylinders : public IFunctionalTest {
protected:
    bool runTest();
};

#endif

