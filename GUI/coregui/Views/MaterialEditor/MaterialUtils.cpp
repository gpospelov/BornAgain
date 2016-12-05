// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialUtils.cpp
//! @brief     Implements class MaterialUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialUtils.h"
#include "ComboProperty.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "HomogeneousMagneticMaterial.h"
#include "HomogeneousMaterial.h"
#include "MagneticFieldItem.h"
#include "MaterialModel.h"
#include "MaterialSvc.h"
#include "RefractiveIndexItem.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include <QDebug>


QColor MaterialUtils::suggestMaterialColor(const QString &name)
{
    if(name.contains("Air") ) {
        return QColor(179, 242, 255);
    }
    else if(name.contains("Substrate") ) {
        return QColor(205,102,0);
    }
    else if ( name.contains("Default") ) {
        return QColor(Qt::green);
    }
    else if ( name.contains("Particle") ) {
        return QColor(146, 198, 255);
    }
    else {
        return DesignerHelper::getRandomColor();
    }
}


MaterialProperty MaterialUtils::getDefaultMaterialProperty()
{
    if(MaterialSvc::instance()) {
        return MaterialSvc::getDefaultMaterialProperty();
    }
    return MaterialProperty();
}


ColorProperty MaterialUtils::suggestMaterialColorProperty(const QString &name)
{
    return ColorProperty(MaterialUtils::suggestMaterialColor(name));
}

std::unique_ptr<IMaterial>
MaterialUtils::createDomainMaterial(const MaterialProperty &material_property)
{
    MaterialItem *materialItem
        = MaterialSvc::getMaterial(material_property);

    if(!materialItem)
        throw GUIHelpers::Error("MaterialUtils::createDomainMaterial() -> Error. Can't create "
                                "material with name '"+material_property.getName()+"'.");

    return materialItem->createMaterial();
}

//! Returns material tag for given item. Returns empty string, if item doesn't have materials.

QString MaterialUtils::materialTag(const SessionItem &item)
{
    QString result;
    if (item.modelType() == Constants::ParticleType) {
        result = ParticleItem::P_MATERIAL;
    } else if (item.modelType() == Constants::LayerType) {
        result = LayerItem::P_MATERIAL;
    }
    return result;
}
