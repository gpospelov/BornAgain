#include "MaterialVariantManager.h"

//#include "DesignerHelper.h"
//#include "MaterialBrowser.h"
//#include "ParameterizedItem.h"
//#include "FormFactorProperty.h"
//#include <iostream>


MaterialVariantManager::MaterialVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


int MaterialVariantManager::refractiveIndexTypeId()
{
    int result = qMetaTypeId<RefractiveIndexProperty>();
    return result;
}



bool MaterialVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == refractiveIndexTypeId())
        return true;
//    if (propertyType == formFactorTypeId())
//        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


int MaterialVariantManager::valueType(int propertyType) const
{
    if (propertyType == refractiveIndexTypeId())
        return refractiveIndexTypeId();
//    if (propertyType == formFactorTypeId())
//        return formFactorTypeId();
    return QtVariantPropertyManager::valueType(propertyType);
}


QVariant MaterialVariantManager::value(const QtProperty *property) const
{
    if(m_RefractiveIndexValues.contains(property)) {
        QVariant v;
        v.setValue(m_RefractiveIndexValues[property]);
        return v;
    }

//    if (theMaterialValues.contains(property)) {
//        QVariant v;
//        v.setValue(theMaterialValues[property]);
//        return v;
//    }
//    if (theFormFactorValues.contains(property)) {
//        QVariant v;
//        v.setValue(theFormFactorValues[property]);
//        return v;
//    }
    return QtVariantPropertyManager::value(property);
}


QString MaterialVariantManager::valueText(const QtProperty *property) const
{
    if (m_RefractiveIndexValues.contains(property)) {
        //return m_RefractiveIndexValues[property].getName();
        return QString("xxx");
    }
//    if (theMaterialValues.contains(property)) {
//        return theMaterialValues[property].getName();
//    }
//    if (theFormFactorValues.contains(property)) {
//        return theFormFactorValues[property].getFormFactorName();
//    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon MaterialVariantManager::valueIcon(const QtProperty *property) const
{
//    if (theMaterialValues.contains(property)) {
//        return QIcon(theMaterialValues[property].getPixmap());
//    }
    return QtVariantPropertyManager::valueIcon(property);
}


void MaterialVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    if (m_RefractiveIndexValues.contains(property)) {
        if( val.userType() != refractiveIndexTypeId() ) return;
        RefractiveIndexProperty mat = val.value<RefractiveIndexProperty>();
        m_RefractiveIndexValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }


//    if (theMaterialValues.contains(property)) {
//        if( val.userType() != materialTypeId() ) return;
//        MaterialProperty mat = val.value<MaterialProperty>();
//        theMaterialValues[property] = mat;
//        QVariant v2;
//        v2.setValue(mat);
//        emit propertyChanged(property);
//        emit valueChanged(property, v2);
//        return;
//    }
//    if (theFormFactorValues.contains(property)) {
//        if( val.userType() != formFactorTypeId() ) return;
//        FormFactorProperty ff_prop = val.value<FormFactorProperty>();
//        theFormFactorValues[property] = ff_prop;
//        QVariant v2;
//        v2.setValue(ff_prop);
//        emit propertyChanged(property);
//        emit valueChanged(property, v2);
//        return;
//    }
    QtVariantPropertyManager::setValue(property, val);
}


void MaterialVariantManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == refractiveIndexTypeId()) {
        RefractiveIndexProperty m;
        m_RefractiveIndexValues[property] = m;
    }

//    if (propertyType(property) == materialTypeId()) {
//        MaterialProperty m;
//        theMaterialValues[property] = m;
//    }
//    if (propertyType(property) == formFactorTypeId()) {
//        FormFactorProperty m;
//        theFormFactorValues[property] = m;
//    }
    QtVariantPropertyManager::initializeProperty(property);
}


void MaterialVariantManager::uninitializeProperty(QtProperty *property)
{
    m_RefractiveIndexValues.remove(property);
//    theFormFactorValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

