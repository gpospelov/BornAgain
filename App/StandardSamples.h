// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/StandardSamples.h
//! @brief     Defines namespace StandardSamples.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"

//! Collection of ISample* pointers to all standard examples.

namespace StandardSamples{

ISample *AirOnSubstrate();
ISample *SubstrateOnSubstrate();
ISample *SimpleMultilayer();
ISample *MultilayerOffspecTestcase1a();
ISample *MultilayerOffspecTestcase1b();
ISample *MultilayerOffspecTestcase2a();
ISample *MultilayerOffspecTestcase2b();
ISample *MultilayerSpecularMagneticTestCase();

}
#endif // STANDARDSAMPLES_H


