// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BackgroundItems.cpp
//! @brief     Implements BackgroundItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/BackgroundItems.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "GUI/coregui/Models/item_constants.h"

BackgroundItem::BackgroundItem(const QString& model_type) : SessionItem(model_type) {}

// Background none
/* ------------------------------------------------ */

BackgroundNoneItem::BackgroundNoneItem() : BackgroundItem(Constants::BackgroundNoneType) {}

std::unique_ptr<IBackground> BackgroundNoneItem::createBackground() const
{
    return {};
}

// Constant background
/* ------------------------------------------------ */

namespace
{
const QString constant_background_value_tooltip = "Constant background value [counts/pixel]";
}

const QString ConstantBackgroundItem::P_VALUE = QString::fromStdString(BornAgain::BackgroundValue);

ConstantBackgroundItem::ConstantBackgroundItem() : BackgroundItem(Constants::ConstantBackgroundType)
{
    addProperty(P_VALUE, 0.0)
        ->setLimits(RealLimits::nonnegative())
        .setToolTip(constant_background_value_tooltip);
}

std::unique_ptr<IBackground> ConstantBackgroundItem::createBackground() const
{
    return std::make_unique<ConstantBackground>(getItemValue(P_VALUE).toDouble());
}

// Background consisting of Poisson noise
/* ------------------------------------------------ */

PoissonNoiseBackgroundItem::PoissonNoiseBackgroundItem()
    : BackgroundItem(Constants::PoissonNoiseBackgroundType)
{
}

std::unique_ptr<IBackground> PoissonNoiseBackgroundItem::createBackground() const
{
    return std::make_unique<PoissonNoiseBackground>();
}
