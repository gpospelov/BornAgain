// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BackgroundItem.cpp
//! @brief     Implements class BackgroundItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "BackgroundItem.h"
#include "BornAgainNamespace.h"
#include "ConstantBackground.h"
#include "item_constants.h"

namespace {
const QString background_value_tooltip =
        "Constant background value that will be added to each detector pixel";
}

const QString BackgroundItem::P_VALUE = QString::fromStdString(BornAgain::BackgroundValue);


BackgroundItem::BackgroundItem() : SessionItem(Constants::BackgroundType)
{
    addProperty(P_VALUE, 0.0)->setLimits(RealLimits::nonnegative())
            .setToolTip(background_value_tooltip)
            .setEditorType(Constants::ScientificEditorType);
}

BackgroundItem::~BackgroundItem() {}

double BackgroundItem::getBackgroundValue() const
{
    return getItemValue(P_VALUE).toDouble();
}

void BackgroundItem::setBackgroundValue(double value)
{
    setItemValue(P_VALUE, value);
}

std::unique_ptr<IBackground> BackgroundItem::createBackground() const
{
    return std::make_unique<ConstantBackground>(getBackgroundValue());
}
