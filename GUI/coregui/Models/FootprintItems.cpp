// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FootprintItems.cpp
//! @brief     Implements FootprintItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FootprintItems.h"
#include "Core/Beam/FootprintFactorGaussian.h"
#include "Core/Beam/FootprintFactorSquare.h"

namespace
{
const QString footprint_value_name = "Width ratio";
const QString footprint_value_tooltip = "The ratio of beam and sample full widths";
} // namespace

// Base class
/* ------------------------------------------------ */

FootprintItem::FootprintItem(const QString& model_type) : SessionItem(model_type) {}

FootprintItem::~FootprintItem() = default;

// Footprint none
/* ------------------------------------------------ */

FootprintNoneItem::FootprintNoneItem() : FootprintItem("NoFootprint") {}

FootprintNoneItem::~FootprintNoneItem() = default;

std::unique_ptr<IFootprintFactor> FootprintNoneItem::createFootprint() const
{
    return {};
}

// Gaussian footprint
/* ------------------------------------------------ */

const QString FootprintGaussianItem::P_VALUE = footprint_value_name;

FootprintGaussianItem::FootprintGaussianItem() : FootprintItem("GaussianFootrpint")
{
    addProperty(P_VALUE, 0.0)
        ->setLimits(RealLimits::nonnegative())
        .setToolTip(footprint_value_tooltip);
}

FootprintGaussianItem::~FootprintGaussianItem() = default;

std::unique_ptr<IFootprintFactor> FootprintGaussianItem::createFootprint() const
{
    return std::make_unique<FootprintFactorGaussian>(getItemValue(P_VALUE).toDouble());
}

// Square footprint
/* ------------------------------------------------ */

const QString FootprintSquareItem::P_VALUE = footprint_value_name;

FootprintSquareItem::FootprintSquareItem() : FootprintItem("SquareFootprint")
{
    addProperty(P_VALUE, 0.0)
        ->setLimits(RealLimits::nonnegative())
        .setToolTip(footprint_value_tooltip);
}

FootprintSquareItem::~FootprintSquareItem() = default;

std::unique_ptr<IFootprintFactor> FootprintSquareItem::createFootprint() const
{
    return std::make_unique<FootprintFactorSquare>(getItemValue(P_VALUE).toDouble());
}
