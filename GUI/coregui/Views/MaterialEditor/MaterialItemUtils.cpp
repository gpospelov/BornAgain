// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialItemUtils.cpp
//! @brief     Implements class MaterialItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialItemUtils.h"
#include "MaterialDataItem.h"
#include "ComboProperty.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "Material.h"
#include "MaterialModel.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include "MaterialEditorDialog.h"
#include "AppSvc.h"
#include "MaterialItem.h"


QColor MaterialItemUtils::suggestMaterialColor(const QString &name)
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


MaterialProperty MaterialItemUtils::defaultMaterialProperty()
{
    auto materials = AppSvc::materialModel()->topItems();
    return materials.isEmpty() ? MaterialProperty() :
                                 MaterialItemUtils::materialProperty(*materials.front());
}


ColorProperty MaterialItemUtils::suggestMaterialColorProperty(const QString &name)
{
    return ColorProperty(MaterialItemUtils::suggestMaterialColor(name));
}

std::unique_ptr<Material>
MaterialItemUtils::createDomainMaterial(const MaterialProperty &material_property)
{    
    MaterialItem *materialItem
        = AppSvc::materialModel()->materialFromIdentifier(material_property.getIdentifier());

    if(!materialItem)
        throw GUIHelpers::Error("MaterialUtils::createDomainMaterial() -> Error. Can't create "
                                "material with name '"+material_property.getName()+"'.");

    return materialItem->createMaterial();
}

//! Returns material tag for given item. Returns empty string, if item doesn't have materials.

QString MaterialItemUtils::materialTag(const SessionItem &item)
{
    QString result;
    if (item.modelType() == Constants::ParticleType) {
        result = ParticleItem::P_MATERIAL;
    } else if (item.modelType() == Constants::LayerType) {
        result = LayerItem::P_MATERIAL;
    }
    return result;
}

//! Returns list of model types which contains registered MaterialProperty.

QStringList MaterialItemUtils::materialRelatedModelTypes()
{
    return {Constants::ParticleType, Constants::LayerType};
}


MaterialProperty MaterialItemUtils::materialProperty(const SessionItem& materialItem)
{
    MaterialProperty result(materialItem.getItemValue(MaterialItem::P_IDENTIFIER).toString());

    ColorProperty colorProperty = materialItem.getItemValue(MaterialItem::P_COLOR).value<ColorProperty>();
    result.setColor(colorProperty.getColor());
    result.setName(materialItem.itemName());

    return result;
}

MaterialProperty MaterialItemUtils::selectMaterialProperty(const MaterialProperty& previousMaterial)
{
    MaterialEditorDialog dialog(AppSvc::materialModel());
    dialog.setMaterialProperty(previousMaterial);
    if(dialog.exec() == QDialog::Accepted) {
        return dialog.selectedMaterialProperty();
    }

    return MaterialProperty();
}

