// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      Algorithms/ISampleBuilder.h 
//! @brief     Defines class ISampleBuilder.
//
// ************************************************************************** //

#ifndef ISAMPLEBUILDER_H_
#define ISAMPLEBUILDER_H_

#include "IParameterized.h"
#include "ISample.h"
#include "Exceptions.h"

class ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder() { setName("SampleBuilder"); }
    virtual ~ISampleBuilder() {}

    virtual ISample *buildSample() const { throw NotImplementedException("ISampleBuilder::buildSample() -> Not implemented"); }
protected:
};

#endif /* ISAMPLEBUILDER_H_ */
