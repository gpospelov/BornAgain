// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialUtils.cpp
//! @brief     Implements class MaterialUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialUtils.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "HomogeneousMaterial.h"
#include "HomogeneousMagneticMaterial.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "RefractiveIndexItem.h"
#include "MagneticFieldItem.h"
#include "ComboProperty.h"
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
    if(MaterialEditor::instance()) {
        return MaterialEditor::getDefaultMaterialProperty();
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
        = MaterialEditor::getMaterial(material_property);
    Q_ASSERT(materialItem);
    return materialItem->createMaterial();
}
