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
#include "GroupPropertyRegistry.h"
#include "FancyGroupProperty.h"
#include <QEvent>
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QMetaEnum>

const QString ParameterizedItem::P_NAME = "Name";
const QString ParameterizedItem::P_PORT = "Port";

ParameterizedItem::ParameterizedItem(const QString &model_type,
                                     ParameterizedItem *parent)
    : m_model_type(model_type)
    , m_parent(parent)
    , m_block_property_change_event(false)
{
    if (m_parent) {
        m_parent->insertChildItem(-1, this);
    }

    registerProperty(P_NAME, QString(), PropertyAttribute::HiddenProperty);
    registerProperty(P_PORT, -1, PropertyAttribute::HiddenProperty);
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

void ParameterizedItem::insertChildItem(int row, ParameterizedItem *item)
{
    if(row == -1) row = m_children.size();
    item->m_parent = this;
    m_children.insert(row, item);
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
//        if (m_sub_items.contains(name)) {
//            updatePropertyItem(name);
//        }
        onPropertyChange(name);
    }
    return QObject::event(e);
}

void ParameterizedItem::onPropertyChange(const QString &name)
{
    qDebug() << "ParameterizedItem::onPropertyChange()" << modelType() << name;
    emit propertyChanged(name);
}


// returns child which should be removed by the model due to over population of children of given type
ParameterizedItem *ParameterizedItem::getCandidateForRemoval(ParameterizedItem *new_comer)
{
    if(!new_comer) return 0;

    QMap<int, QVector<ParameterizedItem *> > nport_to_nitems;
    foreach(ParameterizedItem *child, m_children) {
        int nport = child->getRegisteredProperty(P_PORT).toInt();
        nport_to_nitems[nport].push_back(child);
    }

    QMap<int, QVector<ParameterizedItem *> >::iterator it = nport_to_nitems.begin();
    while(it!=nport_to_nitems.end()) {
        int nport = it.key();
        if(m_port_info.contains(nport)) {
            if(m_port_info[nport].m_item_max_number != 0 && it.value().size() > m_port_info[nport].m_item_max_number) {
                foreach(ParameterizedItem *item, it.value()) {
                    if(item != new_comer) return item;
                }
            }
        }

        ++it;
    }

    return 0;
}

void ParameterizedItem::setItemPort(ParameterizedItem::PortInfo::Keys nport)
{
    setRegisteredProperty(P_PORT, nport);
}


void ParameterizedItem::onPropertyItemChanged(const QString &propertyName)
{
    qDebug() << "ParameterizedItem::onPropertyItemChanged()" << modelType() << propertyName;

    ParameterizedItem *propertyItem = qobject_cast<ParameterizedItem *>(sender());
    qDebug() << "ParameterizedItem::onPropertyItemChanged(), propertyItem " << propertyItem->modelType() << " property_name " << propertyName;
    for(QMap<QString, ParameterizedItem *>::iterator it=m_sub_items.begin(); it!= m_sub_items.end(); ++it) {
        if(it.value() == propertyItem) {
            qDebug() << "   found sender, group property" << it.key();
            FancyGroupProperty *group_property = getRegisteredProperty(it.key()).value<FancyGroupProperty *>();
            group_property->setValueLabel(propertyItem->getItemLabel());
            //setRegisteredProperty(it.key(), group_property.getVariant());
            emit propertyChanged(it.key());
            return;
        }
    }
    throw GUIHelpers::Error("ParameterizedItem::onPropertyItemChanged() -> Error. No such propertyItem found");
}


void ParameterizedItem::addToValidChildren(const QString &name, PortInfo::Keys nport, int nmax_items)
{
    m_valid_children.append(name);

    if(m_port_info.contains(nport)) {
        m_port_info[nport].m_item_names << name;
        m_port_info[nport].m_item_max_number = nmax_items;
    } else {
        m_port_info[nport] = PortInfo(name, nmax_items);
    }
}


void ParameterizedItem::addPropertyItem(QString name, ParameterizedItem *item)
{
    //if (!item) return;
    Q_ASSERT(item);
    qDebug() << "ParameterizedItem::addPropertyItem()" << name;

    if (m_sub_items.contains(name)) {
        qDebug() << "       ParameterizedItem::addPropertyItem() -> item is already there" << name << "replacing with " << item->modelType();
        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_sub_items[name] = item;
    item->m_parent = this;
    connect(item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyItemChanged(QString)));

    qDebug() << "ParameterizedItem::addPropertyItem() -> about to leave" << name;
}

void ParameterizedItem::addFancyPropertyItem(QString name, ParameterizedItem *item)
{
    //if (!item) return;
    Q_ASSERT(item);
    qDebug() << "ParameterizedItem::addPropertyItem()" << name;

    if (m_sub_items.contains(name)) {
        qDebug() << "       ParameterizedItem::addPropertyItem() -> item is already there" << name << "replacing with " << item->modelType();
        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_sub_items[name] = item;
    item->m_parent = this;
    connect(item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyItemChanged(QString)));

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
        qDebug() << "           " << group_prop.getValue();
    } else {
        throw GUIHelpers::Error("ParameterizedItem::createPropertyItem() -> Error unexpected behaviour");
    }

    return result;
}

void ParameterizedItem::updatePropertyItem(const QString &name)
{
    qDebug() << "ParameterizedItem::updatePropertyItem() '" << name << "'";
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

//ParameterizedItem * ParameterizedItem::registerGroupProperty(
//        const QString &name, const QString &value)
//{
//    qDebug() << "registerGroupProperty "
//             << modelType() << name << value;
//    GroupProperty group_prop(name, value);

//    Q_ASSERT(group_prop.isDefined());
//    if (group_prop.isDefined()) {
//        QVariant group_var;
//        group_var.setValue(group_prop);
//        registerProperty(name, group_var);
//    }
//    qDebug() << "   ParameterizedItem::registerGroupProperty() -> about to create property item";
//    ParameterizedItem *item = createPropertyItem(name);
//    qDebug() << "   ParameterizedItem::registerGroupProperty() -> about to add property";
//    addPropertyItem(name, item);
//    return item;
//}

ParameterizedItem *ParameterizedItem::registerFancyGroupProperty(const QString &name)
{
    qDebug() << "registerFancyGroupProperty "
             << modelType() << name;

    FancyGroupProperty *group_property = GroupPropertyRegistry::createGroupProperty(name);
    registerProperty(name, group_property->getVariant());
    group_property->setParent(this);


//    ParameterizedItem *subItem = group_property->createCorrespondingItem();
//    addPropertyItem(name, subItem);

//    GroupProperty group_prop(name, value);
//    Q_ASSERT(group_prop.isDefined());

//    group_prop.setGroupType(type);

//    if (group_prop.isDefined()) {
//        QVariant group_var;
//        group_var.setValue(group_prop);
//        registerProperty(name, group_var);
//    }
//    qDebug() << "   ParameterizedItem::registerGroupProperty() -> about to create property item";
//    ParameterizedItem *item = createPropertyItem(name);
//    qDebug() << "   ParameterizedItem::registerGroupProperty() -> about to add property";
//    addPropertyItem(name, item);
//    return subItem;
    return m_sub_items[name];
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



void ParameterizedItem::registerProperty(const QString &name, const QVariant &variant, const PropertyAttribute &attribute)
{
    //qDebug() << "   XXX   ParameterizedItem::registerProperty() " << modelType() << name;
    if(m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::registerProperty() -> Error. Already existing property "+name);

    m_registered_properties << name;
    m_property_attribute[name] = attribute;

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


void ParameterizedItem::setPropertyAttribute(const QString &name, const PropertyAttribute &attribute)
{
    m_property_attribute[name] = attribute;
}

void ParameterizedItem::setPropertyAttribute(const QString &name, const PropertyAttribute::Appearance &appearance)
{
    if(m_property_attribute.contains(name)) {
        m_property_attribute[name].setAppearance(appearance);
    } else {
        m_property_attribute[name] = PropertyAttribute(appearance);
    }
}

PropertyAttribute ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    return m_property_attribute[name];
}


void ParameterizedItem::print() const
{
    qDebug() << "--- ParameterizedItem::print() ------------------------------------";
    qDebug() << modelType() << itemName();
    qDebug() << "--- SubItems ---";
    for(QMap<QString, ParameterizedItem *>::const_iterator it=m_sub_items.begin(); it!=m_sub_items.end(); ++it) {
        qDebug() << "   key:" << it.key() << " value->modelType:" << it.value()->modelType();
    }
    qDebug() << "--- Properties ---";
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString name(property_names[i]);
        qDebug() << name << property(name.toUtf8().constData());
    }
    qDebug() << " ";

}
