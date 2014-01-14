// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestBessel.h
//! @brief     Defines class TestBessel.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
        Data() : x(0), b1(0), b2(0) {}
        double x;
        double b1;
        double b2;
    };

    TestBessel(){}
    ~TestBessel(){}
    virtual void execute();
    void run_benchmark();

    // (x1-x2)/x2
    double rel_diff(double x1, double x2)
    {
        double ratio(0);
        double diff = x1 - x2;
        if( std::abs(diff) <= Numeric::double_epsilon && std::abs(x2) <= Numeric::double_epsilon) {
            ratio = 0.0;
        } else if(std::abs(x2) <= Numeric::double_epsilon) {
            ratio = diff/Numeric::double_epsilon;
        } else {
            ratio = diff/x2;
        }
        return ratio;
    }

};

#endif // TESTBESSEL_H

