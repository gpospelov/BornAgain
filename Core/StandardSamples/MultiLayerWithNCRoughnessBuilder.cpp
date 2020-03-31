// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultiLayerWithRoughnessBuilder.cpp
//! @brief     Implement class MultiLayerWithRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiLayerWithNCRoughnessBuilder.h"
#include "MaterialFactoryFuncs.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "RealParameter.h"
#include "Units.h"
#include "BornAgainNamespace.h"

MultiLayerWithNCRoughnessBuilder::MultiLayerWithNCRoughnessBuilder()
{}

MultiLayer* MultiLayerWithNCRoughnessBuilder::buildSample() const
{
    auto multi_layer = MultiLayerWithRoughnessBuilder::buildSample();
    multi_layer->setRoughnessModel(RoughnessModel::NEVOT_CROCE);
    return multi_layer;
}
