// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerRoughnessItems.cpp
//! @brief     Implements classes LayerRoughnessItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "LayerRoughnessItems.h"


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
    addProperty(P_HURST, 0.3)->setLimits(RealLimits::limited(0.0, 1.0));
    getItem(P_HURST)->setDecimals(3);
    addProperty(P_LATERAL_CORR_LENGTH, 5.0);
}
