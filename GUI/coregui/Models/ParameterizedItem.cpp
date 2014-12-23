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
{
    if (m_parent) {
        m_parent->insertChildItem(-1, this);
    }

    registerProperty(P_NAME, QString(), PropertyAttribute(PropertyAttribute::HiddenProperty));
    registerProperty(P_PORT, -1, PropertyAttribute(PropertyAttribute::HiddenProperty));
    setItemName(m_model_type);
}


bool ParameterizedItem::isRegisteredProperty(const QString &name)
{
    return m_registered_properties.contains(name);
}

ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
    qDeleteAll(m_sub_items);
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
    onChildPropertyChange();
}

ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    ParameterizedItem *item = m_children.takeAt(row);
    item->m_parent = 0;
    onChildPropertyChange();
    return item;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

// emits signal on property change
bool ParameterizedItem::event(QEvent * e )
{
    if(e->type() == QEvent::DynamicPropertyChange) {
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
//    qDebug() << "ParameterizedItem::onPropertyChange()" << modelType() << name;
    if (m_parent) m_parent->onChildPropertyChange();
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


// to update label of FixedGroupProperty
void ParameterizedItem::onPropertyItemChanged(const QString & /*propertyName*/)
{
    ParameterizedItem *propertyItem = qobject_cast<ParameterizedItem *>(sender());
    for(QMap<QString, ParameterizedItem *>::iterator it=m_sub_items.begin();
        it!= m_sub_items.end(); ++it) {
        if(it.value() == propertyItem) {
            FancyGroupProperty_t group_property =
                    getRegisteredProperty(it.key()).value<FancyGroupProperty_t>();
            group_property->setValueLabel(propertyItem->getItemLabel());
            if (m_parent) m_parent->onChildPropertyChange();
            return;
        }
    }
    throw GUIHelpers::Error("ParameterizedItem::onPropertyItemChanged() ->"
                            " Error. No such propertyItem found");
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
    onChildPropertyChange();
    qDebug() << "ParameterizedItem::addPropertyItem() -> about to leave" << name;
}


ParameterizedItem *ParameterizedItem::registerGroupProperty(const QString &group_name, const Constants::ModelType &group_model)
{
    qDebug() << "registerFancyGroupProperty "
             << modelType() << group_name;

    FancyGroupProperty_t group_property = GroupPropertyRegistry::createGroupProperty(group_name, group_model);
    QVariant variant;
    variant.setValue(group_property);
    registerProperty(group_name, variant);
    group_property->setParent(this);
    return m_sub_items[group_name];
}


ParameterizedItem *ParameterizedItem::setGroupProperty(const QString &name, const QString &value)
{
    qDebug() << "ParameterizedItem::setFancyGroupProperty()" << name << value;
    FancyGroupProperty_t group_property = getRegisteredProperty(name).value<FancyGroupProperty_t>();
    group_property->setValue(value);
    return m_sub_items[name];
}


void ParameterizedItem::registerProperty(const QString &name, const QVariant &variant, const PropertyAttribute &attribute)
{
    if(m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::registerProperty() -> Error. Already existing property "+name);

    if(m_property_attribute.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::registerProperty() -> Error. Already existing attribute "+name);

    m_registered_properties << name;
    m_property_attribute[name] = attribute;

    setProperty(name.toUtf8().constData(), variant);
}


void ParameterizedItem::setRegisteredProperty(const QString &name, const QVariant &variant)
{
    // check if variant of previous property coincides with new one
    QVariant previous_variant = getRegisteredProperty(name);
    if(GUIHelpers::getVariantType(previous_variant) != GUIHelpers::getVariantType(variant)) {
        qDebug() << "ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new variant does not coincide.";
        qDebug() << "New variant" << variant << ", previous " << previous_variant;
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new variant does not coincide.");
    }

    setProperty(name.toUtf8().constData(), variant);
}


QVariant ParameterizedItem::getRegisteredProperty(const QString &name) const
{
    if( !m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::getRegisteredProperty() -> Error. Unknown property "+name);

    return property(name.toUtf8().constData());
}


void ParameterizedItem::removeRegisteredProperty(const QString &name)
{
    qDebug() << "ParameterizedItem::removeRegisteredProperty()" << name;
    if (m_sub_items.contains(name)) {
        qDebug() << "       ParameterizedItem::removeRegisteredProperty() -> Removing property iteme";
        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_registered_properties.removeOne(name);
    m_property_attribute.remove(name);
    setProperty(name.toUtf8().constData(), QVariant());
}


void ParameterizedItem::setPropertyAttribute(const QString &name, const PropertyAttribute &attribute)
{
    if(!m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::setPropertyAttribute() -> Error. Unknown property "+name);

    if(!m_property_attribute.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::setPropertyAttribute() -> Error. Unknown property attribute "+name);

    m_property_attribute[name] = attribute;
}


void ParameterizedItem::setPropertyAppearance(const QString &name, const PropertyAttribute::Appearance &appearance)
{
    if(!m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::setPropertyAppearance() -> Error. Unknown property "+name);

    if(!m_property_attribute.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::setPropertyAppearance() -> Error. Unknown property attribute "+name);

    m_property_attribute[name].setAppearance(appearance);
}

QStringList ParameterizedItem::getParameterTreeList() const
{
    QStringList result;
    // add child parameters:
    if (hasChildItems()) {
        for (QList<ParameterizedItem *>::const_iterator it = m_children.begin();
             it != m_children.end(); ++it) {
            QString child_name = (*it)->itemName();
            QStringList child_list = (*it)->getParameterTreeList();
            for (QStringList::const_iterator par_it = child_list.begin();
                 par_it != child_list.end(); ++par_it) {
                QString new_par_name = child_name + QString("/")
                        + *par_it;
                result << new_par_name;
            }
        }
    }
    // add subitem parameters:
    if (m_sub_items.size()>0) {
        for (QMap<QString, ParameterizedItem *>::const_iterator it =
             m_sub_items.begin(); it != m_sub_items.end(); ++it) {
            QString subitem_name = it.key();
            ParameterizedItem *subitem = it.value();
            QStringList subitem_list = subitem->getParameterTreeList();
            for (QStringList::const_iterator par_it = subitem_list.begin();
                 par_it != subitem_list.end(); ++par_it) {
                QString new_par_name = subitem_name + QString("/")
                        + *par_it;
                result << new_par_name;
            }
        }
    }
    // add own parameters:
    result << getParameterList();
    return result;
}

void ParameterizedItem::onChildPropertyChange()
{
    if (m_parent) m_parent->onChildPropertyChange();
}


PropertyAttribute ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    if(!m_registered_properties.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> Error. Unknown property "+name+" " + modelType());

    if(!m_property_attribute.contains(name))
        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> Error. Unknown property attribute "+name);

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


QStringList ParameterizedItem::getParameterList() const
{
    QStringList result;
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        PropertyAttribute prop_attribute = getPropertyAttribute(prop_name);
        if(prop_attribute.getAppearance() & PropertyAttribute::HiddenProperty) {
            continue;
        }
        QVariant variant = property(prop_name.toUtf8().constData());
        int type = GUIHelpers::getVariantType(variant);
        if (type == QVariant::Double) {
            result << prop_name;
        }
    }
    return result;
}
