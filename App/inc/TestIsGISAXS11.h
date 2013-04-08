// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS11.h
//! @brief     Defines class TestIsGISAXS11.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTISGISAXS11_H_
#define TESTISGISAXS11_H_

#include "IFunctionalTest.h"

//! IsGISAXS ex#11: ?.

class TestIsGISAXS11 : public IFunctionalTest
{
 public:
    TestIsGISAXS11();
    virtual ~TestIsGISAXS11(){ }

    virtual void execute();
    virtual void finalise();
};

#endif /* TESTISGISAXS11_H_ */


