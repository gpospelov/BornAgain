// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS7.h 
//! @brief     Defines class TestIsGISAXS7.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS7_H_
#define TESTISGISAXS7_H_

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

#include <string>

//! IsGISAXS ex#7: Morphology file.

//! This functional test will generate an output that is quite different
//! from the one originating from IsGISAXS. There are 4 reasons for this:
//! 1) IsGISAXS uses a polarization factor for x-rays, which is not yet
//!    implemented in our framework
//! 2) IsGISAXS neglects the scattering length density in case of a
//!    morphology file with 'morif' option in input file
//! 3) IsGISAXS outputs only the coherent part in the *.ima file
//!    The diffuse part can be seen in the windows version, but contains
//!    bugs (compare the commented diffuse calculation in
//!    IsGISAXSMorphologyFileStrategy.cpp with our actual implementation)
//! 4) The morphology file contains 10 particles, yet it says "Number of partic
//!    This causes only nine particle descriptions to be read in IsGISASXS
//!
//! The last three of these can be considered IsGISAXS bugs
//!
class TestIsGISAXS7 : public IFunctionalTest
{
 public:
    TestIsGISAXS7();
    virtual ~TestIsGISAXS7(){}
    virtual void execute();
    virtual void finalise();
};

#endif /* TESTISGISAXS7_H_ */
