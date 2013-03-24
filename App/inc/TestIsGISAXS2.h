// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestIsGISAXS2.h 
//! @brief     Defines class TestIsGISAXS2.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS2_H
#define TESTISGISAXS2_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

#include <string>

//! IsGISAXS ex#2: Mean formfactors for particles with shape size distributions.

class TestIsGISAXS2 : public IFunctionalTest
{
public:
    TestIsGISAXS2();
    virtual ~TestIsGISAXS2(){}

    virtual void execute();
    virtual void finalise();
};

#endif // TESTISGISAXS2_H
