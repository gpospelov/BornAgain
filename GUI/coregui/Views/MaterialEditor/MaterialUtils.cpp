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


std::unique_ptr<IMaterial> MaterialUtils::createDomainMaterial(const MaterialProperty &material_property)
{
    MaterialModel *model = MaterialEditor::getMaterialModel();
    Q_ASSERT(model);

    const MaterialItem *materialItem = model->getMaterial(material_property);
    Q_ASSERT(materialItem);

    const RefractiveIndexItem *refractiveIndexItem = dynamic_cast<const RefractiveIndexItem *>(materialItem->getSubItems()[MaterialItem::P_REFRACTIVE_INDEX]);
    double delta = refractiveIndexItem->getDelta();
    double beta = refractiveIndexItem->getBeta();

    if(materialItem->isHomogeneousMaterial()) {
        return GUIHelpers::make_unique<HomogeneousMaterial>(
                    materialItem->itemName().toStdString(), delta, beta);
    }
    else if(materialItem->isHomogeneousMagneticMaterial()) {
        const MagneticFieldItem *magneticField = dynamic_cast<const MagneticFieldItem *>(materialItem->getSubItems()[MaterialItem::P_MAGNETIC_FIELD]);
        Q_ASSERT(magneticField);
        double Bx = magneticField->getRegisteredProperty(MagneticFieldItem::P_BX).toDouble();
        double By = magneticField->getRegisteredProperty(MagneticFieldItem::P_BY).toDouble();
        double Bz = magneticField->getRegisteredProperty(MagneticFieldItem::P_BZ).toDouble();
        return GUIHelpers::make_unique<HomogeneousMagneticMaterial>(
                    materialItem->itemName().toStdString(),
                    delta, beta, kvector_t(Bx, By, Bz));
    }
    else {
        throw GUIHelpers::Error("MaterialUtils::createDomainMaterial() -> Error. Unknown material type.");
    }

    return nullptr;
}


