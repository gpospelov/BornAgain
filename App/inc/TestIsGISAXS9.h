// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/TestIsGISAXS9.h 
//! @brief     Defines class TestIsGISAXS9.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS9_H
#define TESTISGISAXS9_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"
//#include "SafePointerVector.h"


//- -------------------------------------------------------------------
//! @class TestIsGISAXS9
//! @brief Comparison with IsGISAXS ex-9: pyramids on top of substrate
//- -------------------------------------------------------------------
class TestIsGISAXS9 : public IFunctionalTest
{
public:
    TestIsGISAXS9();
     virtual ~TestIsGISAXS9() { }

    virtual void execute();
    virtual void finalise();

};


#endif // TESTISGISAXS9_H
