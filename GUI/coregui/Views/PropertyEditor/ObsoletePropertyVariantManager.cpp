// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoletePropertyVariantManager.cpp
//! @brief     Implements class ObsoletePropertyVariantManager
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoletePropertyVariantManager.h"
#include "DesignerHelper.h"
#include "SessionItem.h"

ObsoletePropertyVariantManager::ObsoletePropertyVariantManager(QObject *parent)
    : QtVariantPropertyManager(parent)
{

}


int ObsoletePropertyVariantManager::materialTypeId()
{
    int result = qMetaTypeId<ExternalProperty>();
    return result;
}

int ObsoletePropertyVariantManager::colorPropertyTypeId()
{
    int result = qMetaTypeId<ColorProperty>();
    return result;
}

int ObsoletePropertyVariantManager::scientificDoubleTypeId()
{
    int result = qMetaTypeId<ObsoleteScientificDoubleProperty>();
    return result;
}

int ObsoletePropertyVariantManager::fancyGroupTypeId()
{
    int result = qMetaTypeId<GroupProperty_t>();
    return result;
}

int ObsoletePropertyVariantManager::comboPropertyTypeId()
{
    int result = qMetaTypeId<ComboProperty>();
    return result;
}

bool ObsoletePropertyVariantManager::isPropertyTypeSupported(int propertyType) const
{
    if (propertyType == materialTypeId())
        return true;
    if (propertyType == colorPropertyTypeId())
        return true;
    if (propertyType == scientificDoubleTypeId())
        return true;
    if (propertyType == fancyGroupTypeId())
        return true;
    if (propertyType == comboPropertyTypeId())
        return true;
    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}


int ObsoletePropertyVariantManager::valueType(int propertyType) const
{
    if (propertyType == materialTypeId())
        return materialTypeId();
    if (propertyType == colorPropertyTypeId())
        return colorPropertyTypeId();
    if (propertyType == scientificDoubleTypeId())
        return scientificDoubleTypeId();
    if (propertyType == fancyGroupTypeId())
        return fancyGroupTypeId();
    if (propertyType == comboPropertyTypeId())
        return comboPropertyTypeId();
    return QtVariantPropertyManager::valueType(propertyType);
}


QVariant ObsoletePropertyVariantManager::value(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        QVariant v;
        v.setValue(m_theMaterialValues[property]);
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
    if(m_theFancyGroupValues.contains(property)) {
        QVariant v;
        v.setValue(m_theFancyGroupValues[property]);
        return v;
    }
    if(m_theComboValues.contains(property)) {
        QVariant v;
        v.setValue(m_theComboValues[property]);
        return v;
    }

    return QtVariantPropertyManager::value(property);
}


QString ObsoletePropertyVariantManager::valueText(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        return m_theMaterialValues[property].getName();
    }
    if (m_theColorValues.contains(property)) {
        return m_theColorValues[property].getText();
    }
    if (m_theScientificDoubleValues.contains(property)) {
        return m_theScientificDoubleValues[property].getText();
    }
    if (m_theFancyGroupValues.contains(property)) {
        return m_theFancyGroupValues[property]->currentLabel();
    }
    if (m_theComboValues.contains(property)) {
        return m_theComboValues[property].getValue();
    }
    return QtVariantPropertyManager::valueText(property);
}


QIcon ObsoletePropertyVariantManager::valueIcon(const QtProperty *property) const
{
    if (m_theMaterialValues.contains(property)) {
        return QIcon(m_theMaterialValues[property].getPixmap());
    }
    if (m_theColorValues.contains(property)) {
        return QIcon(m_theColorValues[property].getPixmap());
    }
    return QtVariantPropertyManager::valueIcon(property);
}


void ObsoletePropertyVariantManager::setValue(QtProperty *property, const QVariant &val)
{
    if (m_theMaterialValues.contains(property)) {
        if( val.userType() != materialTypeId() ) return;
        ExternalProperty mat = val.value<ExternalProperty>();
        m_theMaterialValues[property] = mat;
        QVariant v2;
        v2.setValue(mat);
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
        ObsoleteScientificDoubleProperty double_prop = val.value<ObsoleteScientificDoubleProperty>();
        m_theScientificDoubleValues[property] = double_prop;
        QVariant v2;
        v2.setValue(double_prop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theFancyGroupValues.contains(property)) {
        if( val.userType() != fancyGroupTypeId() ) return;
        GroupProperty_t group_prop = val.value<GroupProperty_t>();
        m_theFancyGroupValues[property] = group_prop;
        QVariant v2;
        v2.setValue(group_prop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }
    if (m_theComboValues.contains(property)) {
        if( val.userType() != comboPropertyTypeId() ) return;
        ComboProperty comboprop = val.value<ComboProperty>();
        m_theComboValues[property] = comboprop;
        QVariant v2;
        v2.setValue(comboprop);
        emit propertyChanged(property);
        emit valueChanged(property, v2);
        return;
    }

    QtVariantPropertyManager::setValue(property, val);
}


void ObsoletePropertyVariantManager::initializeProperty(QtProperty *property)
{
    if (propertyType(property) == materialTypeId()) {
        ExternalProperty m;
        m_theMaterialValues[property] = m;
    }
    if (propertyType(property) == colorPropertyTypeId()) {
        ColorProperty m;
        m_theColorValues[property] = m;
    }
    if (propertyType(property) == scientificDoubleTypeId()) {
        ObsoleteScientificDoubleProperty m;
        m_theScientificDoubleValues[property] = m;
    }
    if (propertyType(property) == fancyGroupTypeId()) {
        GroupProperty_t m;
        m_theFancyGroupValues[property] = m;
    }
    if (propertyType(property) == comboPropertyTypeId()) {
        ComboProperty m;
        m_theComboValues[property] = m;
    }

    QtVariantPropertyManager::initializeProperty(property);
}


void ObsoletePropertyVariantManager::uninitializeProperty(QtProperty *property)
{
    m_theMaterialValues.remove(property);
    m_theColorValues.remove(property);
    m_theScientificDoubleValues.remove(property);
    m_theFancyGroupValues.remove(property);
    m_theComboValues.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}

