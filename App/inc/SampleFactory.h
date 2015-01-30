// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/SampleFactory.h
//! @brief     Defines class SampleFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEFACTORY_H
#define SAMPLEFACTORY_H

#include "ISingleton.h"
#include "IFactory.h"
#include "ISample.h"

//! Factory to create standard pre-defined samples

//! Samples itself are defined in StandardSamples.{h, cxx}
//!
class SampleFactory : public ISingleton<SampleFactory>,
                      public IFactory<std::string, ISample>
{
public:
    SampleFactory();

    static ISample *createSample(const std::string& sample_name)
    { return instance().createItem(sample_name); }
};

#endif // SAMPLEFACTORY_H



