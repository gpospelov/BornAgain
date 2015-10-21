// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestBessel.h
//! @brief     Defines class TestBessel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTBESSEL_H
#define TESTBESSEL_H

#include "IApplicationTest.h"
#include "Numeric.h"

class TestBessel : public IApplicationTest
{
public:

    class Data {
    public:
        Data() : x(0), b_gsl(0), b_root(0), b_boost(0) {}
        double x;
        double b_gsl;
        double b_root;
        double b_boost;
    };

    TestBessel(){}
    ~TestBessel(){}
    virtual void execute();
    void run_benchmark();
};

#endif // TESTBESSEL_H

