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
#include "MaterialSvc.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include "MaterialEditorDialog.h"
#include "AppSvc.h"


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


MaterialProperty MaterialItemUtils::getDefaultMaterialProperty()
{
    if(MaterialSvc::instance()) {
        return MaterialSvc::getDefaultMaterialProperty();
    }
    return MaterialProperty();
}


ColorProperty MaterialItemUtils::suggestMaterialColorProperty(const QString &name)
{
    return ColorProperty(MaterialItemUtils::suggestMaterialColor(name));
}

std::unique_ptr<Material>
MaterialItemUtils::createDomainMaterial(const MaterialProperty &material_property)
{
    MaterialItem *materialItem
        = MaterialSvc::getMaterial(material_property);

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

MaterialProperty MaterialItemUtils::materialProperty(const SessionItem& materialItem)
{
    MaterialProperty result(materialItem.getItemValue(MaterialItem::P_IDENTIFIER).toString());

    // TODO add handling of material name and color after MaterialSvc gone

    return result;
}

MaterialProperty MaterialItemUtils::selectMaterialProperty(const MaterialProperty& previousMaterial)
{
    MaterialEditorDialog dialog(AppSvc::materialModel());
    dialog.setInitialMaterialProperty(previousMaterial);
    if(dialog.exec() == QDialog::Accepted) {
        return dialog.getSelectedMaterialProperty();
    }

    return MaterialProperty();
}
