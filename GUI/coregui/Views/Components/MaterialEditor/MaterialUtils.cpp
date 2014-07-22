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


//MaterialProperty MaterialUtils::getMaterialProperty(MaterialItem *material)
//{
//    return MaterialProperty(material->getIdentifier());
//}


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

//! Returns the name of the Material corresponding to given material property
//QString MaterialUtils::getMaterialName(const MaterialProperty &material_property)
//{
//    qDebug() << "MaterialUtils::getMaterialName()" << material_property;
//    MaterialItem *materialItem = MaterialEditor::getMaterialModel()->getMaterial(material_property);
//    if(materialItem) {
//        return materialItem->itemName();
//    } else {
//        return QString("Undefined");
//    }
//}

////! Returns color of the material corresponding to given material property
//QColor MaterialUtils::getMaterialColor(const MaterialProperty &material_property)
//{
//    qDebug() << "MaterialUtils::getMaterialColor()" << material_property;
//    MaterialItem *materialItem = MaterialEditor::getMaterialModel()->getMaterial(material_property);
//    if(materialItem) {
//        return materialItem->getColor();
//    } else {
//        return QColor(Qt::red);
//    }
//}


IMaterial *MaterialUtils::createDomainMaterial(const MaterialItem *item)
{
    Q_ASSERT(0);
//    if(item->getType() == MaterialItem::SubItem)
//        throw GUIHelpers::Error("MaterialUtils::createDomainMaterial() -> Error. Unapropriate material type");

//    MaterialItem *refractiveIndex = item->getSubItems()[MaterialProperties::RefractiveIndex];
//    Q_ASSERT(refractiveIndex);
//    double delta = refractiveIndex->property("delta").toString().toDouble();
//    double beta = refractiveIndex->property("beta").toString().toDouble();

//    IMaterial *result(0);
//    if(item->getType() == MaterialItem::HomogeneousMaterial) {
//        result = new HomogeneousMaterial(item->getName().toStdString(), delta, beta);

//    } else if(item->getType() == MaterialItem::HomogeneousMagneticMaterial) {
//        MaterialItem *magneticField = item->getSubItems()[MaterialProperties::MagneticField];
//        Q_ASSERT(magneticField);
//        double Bx = magneticField->property("Bx").toDouble();
//        double By = magneticField->property("By").toDouble();
//        double Bz = magneticField->property("Bz").toDouble();
//        result = new HomogeneousMagneticMaterial(item->getName().toStdString(), delta, beta, kvector_t(Bx, By, Bz));
//    }

//    return result;
}


IMaterial *MaterialUtils::createDomainMaterial(const QString &name)
{
    Q_ASSERT(0);
//    MaterialModel *model = MaterialEditor::getMaterialModel();
//    MaterialItem *materialItem = model->getMaterial(name);
//    Q_ASSERT(materialItem);
//    return createDomainMaterial(materialItem);
}





