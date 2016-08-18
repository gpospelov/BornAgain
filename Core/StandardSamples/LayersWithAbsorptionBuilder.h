// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LayersWithAbsorptionBuilder.h
//! @brief     Defines class LayersWithAbsorptionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LAYERSWITHABSORPTIONBUILDER_H
#define LAYERSWITHABSORPTIONBUILDER_H

#include "IMultiLayerBuilder.h"

//! The LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with
//! absorption (refractive index has imaginary part).
//! @ingroup standard_samples

//! The middle layer is populated with particles.
//! Requires IComponentService which generates form factors, used for bulk form factors testing.

class BA_CORE_API_ LayersWithAbsorptionBuilder : public IMultiLayerBuilder
{
public:
    LayersWithAbsorptionBuilder() {}
    virtual ~LayersWithAbsorptionBuilder() {}
    virtual MultiLayer* buildSample() const;
};

#endif // LAYERSWITHABSORPTIONBUILDER_H
