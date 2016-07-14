// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleBuilderFactory.h
//! @brief     Declares class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEBUILDERFACTORY_H
#define SAMPLEBUILDERFACTORY_H

#include "IFactory.h"
#include "ISampleBuilder.h"

//! @class SampleBuilderFactory
//! @ingroup standard_samples
//! @brief Factory to create standard pre-defined samples

class BA_CORE_API_ SampleBuilderFactory : public IFactory<std::string, ISampleBuilder>
{
public:
    SampleBuilderFactory();
    class ISample* createSample(const std::string& name);
};

#endif // SAMPLEBUILDERFACTORY_H
