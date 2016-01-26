// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestMiscellaneous.h
//! @brief     Defines class TestMiscellaneous.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTMISCELLANEOUS_H
#define TESTMISCELLANEOUS_H

#include "IApplicationTest.h"

//! Collection of functional tests for miscellaneous issues.

class TestMiscellaneous : public IApplicationTest
{
public:
    TestMiscellaneous();
    virtual ~TestMiscellaneous(){}

    virtual void execute();

    //! form factor as a function of qx,qy,qz
    void test_Tiff();
};

#endif // TESTMISCELLANEOUS_H


