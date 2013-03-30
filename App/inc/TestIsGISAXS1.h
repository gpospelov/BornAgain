// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS1.h 
//! @brief     Defines class TestIsGISAXS1.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS1_H_
#define TESTISGISAXS1_H_

#include "IFunctionalTest.h"

//! IsGISAXS ex#1: Mean formfactor cylinder and prism.

class TestIsGISAXS1 : public IFunctionalTest
{
 public:
    TestIsGISAXS1();
    virtual ~TestIsGISAXS1() { }

    virtual void execute();
    virtual void finalise();
};

#endif /* TESTISGISAXS1_H_ */
