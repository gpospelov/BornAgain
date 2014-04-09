#include "PropertyVariantManager.h"
#include "DesignerHelper.h"
#include "MaterialBrowser.h"
#include "ParameterizedItem.h"
#include "FormFactorProperty.h"
#include <iostream>


PropertyVariantManager::PropertyVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


int PropertyVariantManager::materialTypeId()
{
    int result = qMetaTypeId<MaterialProperty>();
    return result;
}

int PropertyVariantManager::formFactorTypeId()
{
    int result = qMetaTypeId<FormFactorProperty>();
    return result;
}


bool PropertyVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == materialTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


int PropertyVariantManager::valueType(int propertyType) const
{
    if (propertyType == materialTypeId())
        return materialTypeId();
    return QtVariantPropertyManager::valueType(propertyType);
}


QVariant PropertyVariantManager::value(const QtProperty *property) const
{
    if (theMaterialValues.contains(property)) {
        QVariant v;
        v.setValue(theMaterialValues[property]);
        return v;
    }
    if (theFormFactorValues.contains(property)) {
        QVariant v;
        v.setValue(theFormFactorValues[property]);
        return v;
    }
    return QtVariantPropertyManager::value(property);
}


QString PropertyVariantManager::valueText(const QtProperty *property) const
{
    if (theMaterialValues.contains(property)) {
        return theMaterialValues[property].getName();
    }
    if (theFormFactorValues.contains(property)) {
        return theFormFactorValues[property].getFormFactorName();
    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon PropertyVariantManager::valueIcon(const QtProperty *property) const
{
    if (theMaterialValues.contains(property)) {
        return QIcon(theMaterialValues[property].getPixmap());
    }
    return QtVariantPropertyManager::valueIcon(property);
}


void PropertyVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    if (theMaterialValues.contains(property)) {
        if( val.userType() != materialTypeId() ) return;
        MaterialProperty mat = val.value<MaterialProperty>();
        theMaterialValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (theFormFactorValues.contains(property)) {
        if( val.userType() != formFactorTypeId() ) return;
        FormFactorProperty ff_prop = val.value<FormFactorProperty>();
        theFormFactorValues[property] = ff_prop;
        QVariant v2;
        v2.setValue(ff_prop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    QtVariantPropertyManager::setValue(property, val);
}


void PropertyVariantManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == materialTypeId()) {
        MaterialProperty m;
        theMaterialValues[property] = m;
    }
    if (propertyType(property) == formFactorTypeId()) {
        FormFactorProperty m;
        theFormFactorValues[property] = m;
    }
    QtVariantPropertyManager::initializeProperty(property);
}


void PropertyVariantManager::uninitializeProperty(QtProperty *property)
{
    theMaterialValues.remove(property);
    theFormFactorValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

