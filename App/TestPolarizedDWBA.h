// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPolarizedDWBA.h
//! @brief     Defines class TestPolarizedDWBA.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
};



#endif /* TESTPOLARIZEDDWBA_H_ */
