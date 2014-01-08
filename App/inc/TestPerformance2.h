// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPerformance2.h
//! @brief     Defines classe TestPerformance2
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPERFORMANCE2_H
#define TESTPERFORMANCE2_H

#include "IApplicationTest.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>

//! Run standard tests to trace changes in the performance.

class TestPerformance2 : public IApplicationTest
{
public:
    TestPerformance2(){}
    virtual void execute();

};


#endif
