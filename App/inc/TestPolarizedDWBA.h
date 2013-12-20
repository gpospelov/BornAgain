// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPolarizedDWBA.h
//! @brief     Defines class TestPolarizedDWBA.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPOLARIZEDDWBA_H_
#define TESTPOLARIZEDDWBA_H_

#include "IApplicationTest.h"
#include "MultiLayer.h"

//! Functional test for polarized DWBA.

class TestPolarizedDWBA : public IApplicationTest
{
public:
    TestPolarizedDWBA();
    virtual ~TestPolarizedDWBA() { }

    virtual void execute();

private:
    MultiLayer *mp_sample; //!< pointer to multilayer sample
};



#endif /* TESTPOLARIZEDDWBA_H_ */
