// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/FourierTransformationTest.h
//! @brief     Defines FourierTransformationTest class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FOURIERTRANSFORMATIONTEST_H
#define FOURIERTRANSFORMATIONTEST_H

#include "IFunctionalTest.h"

//! Transforms GISAS image and compares results against reference file.

class FourierTransformationTest : public IFunctionalTest {
protected:
    bool runTest();
};

#endif  // FOURIERTRANSFORMATIONTEST_H

