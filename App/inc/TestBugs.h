// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestBugs.h
//! @brief     Defines class TestBugs
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTBUGS_H
#define TESTBUGS_H

#include "IApplicationTest.h"


class TestBugs : public IApplicationTest
{
public:
    TestBugs();
    virtual ~TestBugs(){}

    virtual void execute();

    void test_item339();

};

#endif // TESTBUGS_H
