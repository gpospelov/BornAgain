// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialProperty.cpp
//! @brief     Implements class MaterialProperty
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
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "MaterialProperty.h"

QString MaterialProperty::getName() const
{
    MaterialProperty property(getIdentifier());
    MaterialItem *materialItem = MaterialSvc::getMaterial(property);
    if(materialItem) {
        return materialItem->itemName();
    } else {
        return QString("Undefined");
    }
}


QColor MaterialProperty::getColor() const
{
    MaterialProperty property(getIdentifier());
    MaterialItem *materialItem = MaterialSvc::getMaterial(property);
    if(materialItem) {
        return materialItem->getColor();
    } else {
        return QColor(Qt::red);
    }

}


QPixmap MaterialProperty::getPixmap() const
{
    QPixmap pixmap(10,10);
    pixmap.fill(getColor());
    return pixmap;
}

bool MaterialProperty::isDefined() const
{
    return !m_identifier.isEmpty();
}
