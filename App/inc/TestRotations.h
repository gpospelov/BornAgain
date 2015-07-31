// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestRotations.h
//! @brief     Defines class TestRotations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTROTATIONS_H
#define TESTROTATIONS_H

#include "IApplicationTest.h"
class MultiLayer;


//! Test rotated samples

class TestRotations : public IApplicationTest
{
public:
    TestRotations() : IApplicationTest("TestRotations") {}
    virtual ~TestRotations(){}

    virtual void execute();

private:
    MultiLayer *createComposition();
    MultiLayer *createReferenceSample();
};

#endif // TESTROTATIONS_H


