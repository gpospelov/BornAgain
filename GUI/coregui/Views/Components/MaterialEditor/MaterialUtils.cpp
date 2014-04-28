#include "MaterialUtils.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "HomogeneousMaterial.h"
#include "HomogeneousMagneticMaterial.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include <QDebug>


QColor MaterialUtils::suggestMaterialColor(const QString &name)
{
    if(name == QStringLiteral("Air") ) {
        return QColor(176, 226, 255);
    } else if(name == QStringLiteral("Substrate") ) {
        return QColor(205,102,0);
    } else if ( name == QStringLiteral("Default") ) {
        return QColor(Qt::green);
    }
    return DesignerHelper::getRandomColor();
}


MaterialProperty MaterialUtils::getMaterialProperty(MaterialItem *material)
{
    Q_ASSERT(material);
    if(material->getType() == MaterialItem::SubItem)
        throw GUIHelpers::Error("MaterialUtils::getMaterialProperty() -> Error! It's a SubItem, not material.");

    QVariant v = material->property(MaterialProperties::Color);
    MaterialColorProperty colorProperty = v.value<MaterialColorProperty>();
    return MaterialProperty(material->getName(), colorProperty.getColor());
}


MaterialColorProperty MaterialUtils::suggestMaterialColorProperty(const QString &name)
{
    return MaterialColorProperty(MaterialUtils::suggestMaterialColor(name));
}


IMaterial *MaterialUtils::createDomainMaterial(const MaterialItem *item)
{
    if(item->getType() == MaterialItem::SubItem)
        throw GUIHelpers::Error("MaterialUtils::createDomainMaterial() -> Error. Unapropriate material type");

    MaterialItem *refractiveIndex = item->getSubItems()[MaterialProperties::RefractiveIndex];
    Q_ASSERT(refractiveIndex);
    double delta = refractiveIndex->property("delta").toString().toDouble();
    double beta = refractiveIndex->property("beta").toString().toDouble();

    IMaterial *result(0);
    if(item->getType() == MaterialItem::HomogeneousMaterial) {
        result = new HomogeneousMaterial(item->getName().toStdString(), delta, beta);

    } else if(item->getType() == MaterialItem::HomogeneousMagneticMaterial) {
        MaterialItem *magneticField = item->getSubItems()[MaterialProperties::MagneticField];
        Q_ASSERT(magneticField);
        double Bx = magneticField->property("Bx").toDouble();
        double By = magneticField->property("By").toDouble();
        double Bz = magneticField->property("Bz").toDouble();
        result = new HomogeneousMagneticMaterial(item->getName().toStdString(), delta, beta, kvector_t(Bx, By, Bz));
    }

    return result;
}


IMaterial *MaterialUtils::createDomainMaterial(const QString &name)
{
    MaterialModel *model = MaterialEditor::getMaterialModel();
    MaterialItem *materialItem = model->getMaterial(name);
    Q_ASSERT(materialItem);
    return createDomainMaterial(materialItem);
}

