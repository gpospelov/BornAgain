// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultiLayerWithNCRoughnessBuilder.cpp
//! @brief     Implement class MultiLayerWithNCRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiLayerWithNCRoughnessBuilder.h"
#include "BornAgainNamespace.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "RealParameter.h"
#include "Units.h"

MultiLayerWithNCRoughnessBuilder::MultiLayerWithNCRoughnessBuilder() {}

MultiLayer* MultiLayerWithNCRoughnessBuilder::buildSample() const
{
    auto multi_layer = MultiLayerWithRoughnessBuilder::buildSample();
    multi_layer->setRoughnessModel(RoughnessModel::NEVOT_CROCE);
    return multi_layer;
}
