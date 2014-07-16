#include "PropertyVariantManager.h"
#include "DesignerHelper.h"
#include "ParameterizedItem.h"


PropertyVariantManager::PropertyVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


int PropertyVariantManager::materialTypeId()
{
    int result = qMetaTypeId<MaterialProperty>();
    return result;
}

int PropertyVariantManager::groupTypeId()
{
    int result = qMetaTypeId<GroupProperty>();
    return result;
}

int PropertyVariantManager::colorPropertyTypeId()
{
    int result = qMetaTypeId<ColorProperty>();
    return result;
}

int PropertyVariantManager::scientificDoubleTypeId()
{
    int result = qMetaTypeId<ScientificDoubleProperty>();
    return result;
}

bool PropertyVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == materialTypeId())
        return true;
    if (propertyType == groupTypeId())
        return true;
    if (propertyType == colorPropertyTypeId())
        return true;
    if (propertyType == scientificDoubleTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


int PropertyVariantManager::valueType(int propertyType) const
{
    if (propertyType == materialTypeId())
        return materialTypeId();
    if (propertyType == groupTypeId())
        return groupTypeId();
    if (propertyType == colorPropertyTypeId())
        return colorPropertyTypeId();
    if (propertyType == scientificDoubleTypeId())
        return scientificDoubleTypeId();
    return QtVariantPropertyManager::valueType(propertyType);
}


QVariant PropertyVariantManager::value(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        QVariant v;
        v.setValue(m_theMaterialValues[property]);
        return v;
    }
    if (m_theGroupValues.contains(property)) {
        QVariant v;
        v.setValue(m_theGroupValues[property]);
        return v;
    }
    if(m_theColorValues.contains(property)) {
        QVariant v;
        v.setValue(m_theColorValues[property]);
        return v;
    }
    if(m_theScientificDoubleValues.contains(property)) {
        QVariant v;
        v.setValue(m_theScientificDoubleValues[property]);
        return v;
    }

    return QtVariantPropertyManager::value(property);
}


QString PropertyVariantManager::valueText(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        return m_theMaterialValues[property].getName();
    }
    if (m_theGroupValues.contains(property)) {
        return m_theGroupValues[property].getText();
    }
    if (m_theColorValues.contains(property)) {
        return m_theColorValues[property].getText();
    }
    if (m_theScientificDoubleValues.contains(property)) {
        return m_theScientificDoubleValues[property].getText();
    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon PropertyVariantManager::valueIcon(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        return QIcon(m_theMaterialValues[property].getPixmap());
    }
    if (m_theColorValues.contains(property)) {
        return QIcon(m_theColorValues[property].getPixmap());
    }
    return QtVariantPropertyManager::valueIcon(property);
}


void PropertyVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    if (m_theMaterialValues.contains(property)) {
        if( val.userType() != materialTypeId() ) return;
        MaterialProperty mat = val.value<MaterialProperty>();
        m_theMaterialValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theGroupValues.contains(property)) {
        if( val.userType() != groupTypeId() ) return;
        GroupProperty group_prop = val.value<GroupProperty>();
        m_theGroupValues[property] = group_prop;
        QVariant v2;
        v2.setValue(group_prop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theColorValues.contains(property)) {
        if( val.userType() != colorPropertyTypeId() ) return;
        ColorProperty mat = val.value<ColorProperty>();
        m_theColorValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theScientificDoubleValues.contains(property)) {
        if( val.userType() != scientificDoubleTypeId() ) return;
        ScientificDoubleProperty double_prop = val.value<ScientificDoubleProperty>();
        m_theScientificDoubleValues[property] = double_prop;
        QVariant v2;
        v2.setValue(double_prop);
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
        m_theMaterialValues[property] = m;
    }
    if (propertyType(property) == groupTypeId()) {
        GroupProperty m;
        m_theGroupValues[property] = m;
    }
    if (propertyType(property) == colorPropertyTypeId()) {
        ColorProperty m;
        m_theColorValues[property] = m;
    }
    if (propertyType(property) == scientificDoubleTypeId()) {
        ScientificDoubleProperty m;
        m_theScientificDoubleValues[property] = m;
    }

    QtVariantPropertyManager::initializeProperty(property);
}


void PropertyVariantManager::uninitializeProperty(QtProperty *property)
{
    m_theMaterialValues.remove(property);
    m_theGroupValues.remove(property);
    m_theColorValues.remove(property);
    m_theScientificDoubleValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

