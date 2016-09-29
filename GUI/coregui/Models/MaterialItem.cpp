// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.cpp
//! @brief     Implements class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialItem.h"
#include "GUIHelpers.h"
#include "HomogeneousMaterial.h"
#include "MaterialUtils.h"
#include "RefractiveIndexItem.h"


const QString MaterialItem::P_COLOR = "Color";
const QString MaterialItem::P_REFRACTIVE_INDEX = "Refractive index";
const QString MaterialItem::P_IDENTIFIER = "Identifier";

MaterialItem::MaterialItem()
    : SessionItem(Constants::MaterialType)
{
    setItemName(Constants::MaterialType);

    ColorProperty color;
    addProperty(P_COLOR, color.getVariant());
    addGroupProperty(P_REFRACTIVE_INDEX, Constants::RefractiveIndexType);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid());
    getItem(P_IDENTIFIER)->setVisible(false);
}

QString MaterialItem::getIdentifier() const
{
    return getItemValue(P_IDENTIFIER).toString();
}

QColor MaterialItem::getColor() const
{
    ColorProperty property = getItemValue(P_COLOR).value<ColorProperty>();
    return property.getColor();
}

std::unique_ptr<IMaterial> MaterialItem::createMaterial() const
{
    const RefractiveIndexItem *refractiveIndexItem
        = dynamic_cast<const RefractiveIndexItem *>(
            getItem(MaterialItem::P_REFRACTIVE_INDEX));

    Q_ASSERT(refractiveIndexItem);

    double delta = refractiveIndexItem->getDelta();
    double beta = refractiveIndexItem->getBeta();

    return GUIHelpers::make_unique<HomogeneousMaterial>(
                itemName().toStdString(), delta, beta);
}
