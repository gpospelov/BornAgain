// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/LayerRoughnessItems.cpp
//! @brief     Implements classes LayerRoughnessItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LayerRoughnessItems.h"
#include "ScientificDoubleProperty.h"


LayerZeroRoughnessItem::LayerZeroRoughnessItem()
    : ParameterizedItem(Constants::LayerZeroRoughnessType)
{
}

const QString LayerBasicRoughnessItem::P_SIGMA = "Sigma";
const QString LayerBasicRoughnessItem::P_HURST = "Hurst parameter";
const QString LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH = "Lateral corr length";

LayerBasicRoughnessItem::LayerBasicRoughnessItem()
    : ParameterizedItem(Constants::LayerBasicRoughnessType)
{
    registerProperty(P_SIGMA, 1.0);
    registerProperty(P_HURST, 0.3).limited(0.0, 1.0).setDecimals(3);
    registerProperty(P_LATERAL_CORR_LENGTH, 5.0);
}
