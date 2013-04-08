// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS14.h
//! @brief     Defines class TestIsGISAXS14.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTISGISAXS14_H
#define TESTISGISAXS14_H

#include "IFunctionalTest.h"

//! IsGISAXS ex#14: Multi layered sphere on graded interface.

class TestIsGISAXS14 : public IFunctionalTest
{
 public:
    TestIsGISAXS14();
    virtual ~TestIsGISAXS14() {}
    virtual void execute();
    virtual void finalise();
};

#endif // TESTISGISAXS14_H


