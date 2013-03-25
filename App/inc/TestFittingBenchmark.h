// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFittingBenchmark.h 
//! @brief     Defines class TestFittingBenchmark.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTFITTINGBENCHMARK_H
#define TESTFITTINGBENCHMARK_H

#include "IFunctionalTest.h"

//! Test of minimizers with hard-to-minimize test functions

class TestFittingBenchmark : public IFunctionalTest
{
public:
    TestFittingBenchmark() {}
    virtual ~TestFittingBenchmark() {}
    virtual void execute();
};

#endif // TESTFITTINGBENCHMARK_H
