// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS10.h
//! @brief     Defines class TestIsGISAXS10.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTISGISAXS10_H_
#define TESTISGISAXS10_H_

#include "IApplicationTest.h"

//! IsGISAXS ex#10: Cylinder with interference on top of substrate.

class TestIsGISAXS10 : public IApplicationTest
{
public:
    TestIsGISAXS10();
    virtual ~TestIsGISAXS10(){}

    virtual void execute();
    virtual void finalise();
};

#endif /* TESTISGISAXS10_H_ */


