// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterizedItem.h
//! @brief     Defines class ParameterizedItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedItem.h"
#include "Exceptions.h"
#include "GroupProperty.h"
#include "MaterialEditor.h"
#include "GUIHelpers.h"
#include "PropertyVariantManager.h"
#include <QEvent>
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QMetaEnum>

const QString ParameterizedItem::P_NAME = "Name";

ParameterizedItem::ParameterizedItem(const QString &model_type,
                                     ParameterizedItem *parent)
    : m_model_type(model_type)
    , m_parent(parent)
    , m_block_property_change_event(false)
{
    if (m_parent) {
        m_parent->addChildItem(this);
    }

    registerProperty(P_NAME, QString(), HiddenProperty);
    setItemName(m_model_type);
}

ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
}

QString ParameterizedItem::itemName() const
{
    return getRegisteredProperty(P_NAME).toString();
}

void ParameterizedItem::setItemName(const QString &item_name)
{
    setRegisteredProperty(P_NAME, item_name);
}

ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    ParameterizedItem *item = m_children.takeAt(row);
    item->m_parent = 0;
    return item;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

// emmits signal on property change
bool ParameterizedItem::event(QEvent * e )
{
    if(e->type() == QEvent::DynamicPropertyChange && !getBlockPropertyChangeEvent()) {
        QDynamicPropertyChangeEvent *propertyEvent =
                dynamic_cast<QDynamicPropertyChangeEvent *>(e);
        Q_ASSERT(e);
        QByteArray byte_array = propertyEvent->propertyName();
        QString name(byte_array.constData());
        if (m_sub_items.contains(name)) {
            updatePropertyItem(name);
        }
        onPropertyChange(name);
    }
    return QObject::event(e);
}

void ParameterizedItem::onPropertyChange(const QString &name)
{
    //qDebug() << "ParameterizedItem::onPropertyChange() -> before emit";
    emit propertyChanged(name);
}


void ParameterizedItem::addPropertyItem(QString name, ParameterizedItem *item)
{
    //if (!item) return;
    Q_ASSERT(item);
    qDebug() << "ParameterizedItem::addPropertyItem()" << name;

    if (m_sub_items.contains(name)) {
        qDebug() << "       ParameterizedItem::addPropertyItem() -> item is already there" << name;
        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_sub_items[name] = item;
    item->m_parent = this;
    qDebug() << "ParameterizedItem::addPropertyItem() -> about to leave" << name;
}

ParameterizedItem *ParameterizedItem::createPropertyItem(QString name)
{
    ParameterizedItem *result = 0;
    qDebug() << "CreateSubItem: " << name;
    QByteArray name_byte_array = name.toUtf8();
    QVariant val = property(name_byte_array.constData());
    if (val.userType() == PropertyVariantManager::groupTypeId()) {
    //if (val.userType() == qMetaTypeId<GroupProperty>()) {
        GroupProperty group_prop = val.value<GroupProperty>();
        result = group_prop.createCorrespondingItem(
                    group_prop.getValue());
    } else {
        throw GUIHelpers::Error("ParameterizedItem::createPropertyItem() -> Error unexpected behaviour");
    }

    return result;
}

void ParameterizedItem::updatePropertyItem(QString name)
{
    qDebug() << "ParameterizedItem::updatePropertyItem() ";
    if (!m_sub_items.contains(name)) {
        qDebug() << "           ParameterizedItem::updatePropertyItem() -> No such item";
        return;
        //throw GUIHelpers::Error("ParameterizedItem::updatePropertyItem -> Error. No such sub property.");
    }
    ParameterizedItem *item = createPropertyItem(name);
    addPropertyItem(name, item);
    emit propertyItemChanged(name);
}

void ParameterizedItem::setMaterialProperty(MaterialProperty material)
{
    QVariant mat_var;
    if(material.isDefined()) {
        mat_var.setValue(material);
    } else {
        mat_var.setValue(MaterialEditor::getDefaultMaterialProperty());
    }
    setProperty("Material", mat_var);
}

ParameterizedItem * ParameterizedItem::registerGroupProperty(
        const QString &name, const QString &value)
{
    qDebug() << "registerGroupProperty "
             << modelType() << name << value;
    GroupProperty group_prop(name, value);

    Q_ASSERT(group_prop.isDefined());
    if (group_prop.isDefined()) {
        QVariant group_var;
        group_var.setValue(group_prop);
        registerProperty(name, group_var);
    }
    qDebug() << "   ParameterizedItem::registerGroupProperty() -> about to create property item";
    ParameterizedItem *item = createPropertyItem(name);
    qDebug() << "   ParameterizedItem::registerGroupProperty() -> about to add property";
    addPropertyItem(name, item);
    return item;
}

ParameterizedItem * ParameterizedItem::setGroupProperty(
        const QString &name, const QString &value)
{
    qDebug() << "ParameterizedItem::setGroupProperty" << name << value;
    setBlockPropertyChangeEvent(true);

    GroupProperty group_prop(name, value);

    Q_ASSERT(group_prop.isDefined());
    if (group_prop.isDefined()) {
        QVariant group_var;
        group_var.setValue(group_prop);
        setRegisteredProperty(name, group_var);
    }
    setBlockPropertyChangeEvent(false);

    ParameterizedItem *item = createPropertyItem(name);
    addPropertyItem(name, item);
    emit propertyItemChanged(name);
    return item;
}



void ParameterizedItem::registerProperty(const QString &name, const QVariant &variant, PropertyAttribute property_attribute)
{
    //qDebug() << "   XXX   ParameterizedItem::registerProperty() " << modelType() << name;
    if(m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::registerProperty() -> Error. Already existing property "+name);

    m_registered_properties << name;
    m_property_attribute[name] = property_attribute;

    setProperty(name.toUtf8().constData(), variant);
}

void ParameterizedItem::setRegisteredProperty(const QString &name, const QVariant &variant)
{
    if( !m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Unknown property "+name);

    setProperty(name.toUtf8().constData(), variant);
}

QVariant ParameterizedItem::getRegisteredProperty(const QString &name) const
{
    if( !m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::getRegisteredProperty() -> Error. Unknown property "+name);

    return property(name.toUtf8().constData());
}


void ParameterizedItem::setPropertyAttribute(const QString &name, ParameterizedItem::PropertyAttribute attribute)
{
    m_property_attribute[name] = attribute;
}

ParameterizedItem::PropertyAttribute ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    return m_property_attribute[name];
}


void ParameterizedItem::print() const
{
    qDebug() << "--- ParameterizedItem::print() ------------------------------------";
    qDebug() << modelType() << itemName();
    qDebug() << "--- SubItems ---";
    for(QMap<QString, ParameterizedItem *>::const_iterator it=m_sub_items.begin(); it!=m_sub_items.end(); ++it) {
        qDebug() << "   key:" << it.key() << " value:" << it.value()->modelType();
    }
    qDebug() << "--- Properties ---";
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString name(property_names[i]);
        qDebug() << name << property(name.toUtf8().constData());
    }
    qDebug() << " ";

}
