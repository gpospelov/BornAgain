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
    : SessionItem(Constants::LayerZeroRoughnessType)
{
}

const QString LayerBasicRoughnessItem::P_SIGMA = "Sigma";
const QString LayerBasicRoughnessItem::P_HURST = "Hurst parameter";
const QString LayerBasicRoughnessItem::P_LATERAL_CORR_LENGTH = "Lateral corr length";

LayerBasicRoughnessItem::LayerBasicRoughnessItem()
    : SessionItem(Constants::LayerBasicRoughnessType)
{
    addProperty(P_SIGMA, 1.0);
    addProperty(P_HURST, 0.3)->setLimits(AttLimits::limited(0.0, 1.0));
    getItem(P_HURST)->setDecimals(3);
    addProperty(P_LATERAL_CORR_LENGTH, 5.0);
}
