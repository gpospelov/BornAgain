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
#include <QEvent>
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QMetaEnum>
#include <PropertyVariantManager.h>



ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
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
        emit propertyChanged(name);
    }
    return QObject::event(e);
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
        GroupProperty group_prop = val.value<GroupProperty>();
        result = group_prop.createCorrespondingItem(
                    group_prop.getValue());
    } else {
        throw GUIHelpers::Error("ParameterizedItem::createPropertyItem() -> Error unexpected behaviour");
    }

    return result;
}

ParameterizedItem::ParameterizedItem(const QString &model_type,
                                     ParameterizedItem *parent)
    : m_model_type(model_type)
    , m_parent(parent)
    , m_block_property_change_event(false)
{
    if (m_parent) {
        m_parent->addChildItem(this);
    }
    setItemName(m_model_type);
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

ParameterizedItem * ParameterizedItem::registerGroupProperty(const QString &name, const QString &value)
{
    qDebug() << "   XXX   registerGroupProperty " << modelType() << name << value;
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

ParameterizedItem * ParameterizedItem::setGroupProperty(const QString &name, const QString &value)
{
    qDebug() << "ParameterizedItem::setGroupProperty";
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



void ParameterizedItem::registerProperty(const QString &name, const QVariant &variant, const QString &tooltip, PropertyVisibility visibility)
{
    qDebug() << "   XXX   registerProperty " << modelType() << name;
    if(m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::registerProperty() -> Error. Already existing property "+name);

    m_registered_properties << name;

    if(!tooltip.isEmpty()) {
        QString wrappedToolTip = QString("<FONT COLOR=black>"); // to have automatic line wrap
        wrappedToolTip += tooltip;
        wrappedToolTip += QString("</FONT>");
        m_property_tooltip[name] = wrappedToolTip;
    }
    if(visibility == HiddenProperty) m_hidden_properties << name;
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
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Unknown property "+name);

    return property(name.toUtf8().constData());
}


bool ParameterizedItem::isHiddenProperty(const QString &name) const
{
    return m_hidden_properties.contains(name);
}

QString ParameterizedItem::getPropertyToolTip(const QString &name) const
{
    return m_property_tooltip[name];
}
