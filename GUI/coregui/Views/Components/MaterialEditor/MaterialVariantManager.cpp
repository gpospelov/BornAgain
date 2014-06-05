#include "MaterialVariantManager.h"


MaterialVariantManager::MaterialVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


int MaterialVariantManager::materialColorPropertyTypeId()
{
    int result = qMetaTypeId<MaterialColorProperty>();
    return result;
}


bool MaterialVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == materialColorPropertyTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


int MaterialVariantManager::valueType(int propertyType) const
{
    if (propertyType == materialColorPropertyTypeId())
        return materialColorPropertyTypeId();
    return QtVariantPropertyManager::valueType(propertyType);
}


QVariant MaterialVariantManager::value(const QtProperty *property) const
{
    if(m_MaterialColorValues.contains(property)) {
        QVariant v;
        v.setValue(m_MaterialColorValues[property]);
        return v;
    }
    return QtVariantPropertyManager::value(property);
}


QString MaterialVariantManager::valueText(const QtProperty *property) const
{
    if (m_MaterialColorValues.contains(property)) {
        return m_MaterialColorValues[property].getText();
    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon MaterialVariantManager::valueIcon(const QtProperty *property) const
{
    if (m_MaterialColorValues.contains(property)) {
        return QIcon(m_MaterialColorValues[property].getPixmap());
    }
    return QtVariantPropertyManager::valueIcon(property);
}


void MaterialVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    if (m_MaterialColorValues.contains(property)) {
        if( val.userType() != materialColorPropertyTypeId() ) return;
        MaterialColorProperty mat = val.value<MaterialColorProperty>();
        m_MaterialColorValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    QtVariantPropertyManager::setValue(property, val);
}


void MaterialVariantManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == materialColorPropertyTypeId()) {
        MaterialColorProperty m;
        m_MaterialColorValues[property] = m;
    }
    QtVariantPropertyManager::initializeProperty(property);
}


void MaterialVariantManager::uninitializeProperty(QtProperty *property)
{
    m_MaterialColorValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

