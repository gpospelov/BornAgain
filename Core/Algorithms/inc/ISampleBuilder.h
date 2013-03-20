// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/ISampleBuilder.h
//! @brief     Defines class ISampleBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef ISAMPLEBUILDER_H_
#define ISAMPLEBUILDER_H_

#include "ISample.h"

class ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder() { setName("SampleBuilder"); }
    virtual ~ISampleBuilder() {}

    virtual ISample *buildSample() const {
        throw NotImplementedException("ISampleBuilder::buildSample() -> Not implemented"); }
protected:
};

#endif /* ISAMPLEBUILDER_H_ */
