// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedItem.cpp
//! @brief     Implements class ParameterizedItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "GroupPropertyRegistry.h"
#include "GroupProperty.h"
#include "GroupItem.h"
#include "ItemFactory.h"
#include "GUIHelpers.h"
//#include "PropertyVariantManager.h"

#include <sstream>
#include <QDebug>

ParameterizedItem::ParameterizedItem(QString model_type)
    : mp_parent(0)
    , m_model(0)
    , m_data(QVector<QVariant>(SessionModel::MAX_COLUMNS))
    , m_model_type(QString())
    , m_port(PortInfo::DEFAULT)
{
    // provide useful name in case of empty constructor
    m_model_type = model_type.isEmpty() ? "ParameterizedItem" : model_type;
    setDisplayName(m_model_type);
}

ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
}

QVariant ParameterizedItem::data(int column) const
{
    if (column == SessionModel::ITEM_NAME && !m_data[column].isValid()) {
        return displayName();
    }
    if (column >= 0 && column < m_data.size()) {
        return m_data[column];
    }
    return QVariant();
}

bool ParameterizedItem::setData(int column, const QVariant &data)
{
    if (column < 0 || column >= m_data.size())
        return false;

    if (column == SessionModel::ITEM_NAME) {
        // only unique names allowed
        if (parent() && parent()->getChildByName(data.toString()))
            return false;
        if (data.toString().isEmpty())
            return false;
    }

    m_data[column] = data;

    // inform model about the change
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        index = index.sibling(index.row(), column);
        m_model->dataChanged(index, index, QVector<int>() << Qt::DisplayRole << Qt::EditRole);
    }
    return true;
}

bool ParameterizedItem::hasData(int column)
{
    return data(column).isValid();
}

QVariant ParameterizedItem::value() const
{
    return data(SessionModel::ITEM_VALUE);
}

bool ParameterizedItem::setValue(QVariant value)
{
    return setData(SessionModel::ITEM_VALUE, value);
}

QString ParameterizedItem::itemName() const
{
    return data(SessionModel::ITEM_NAME).toString();
}

void ParameterizedItem::setItemName(const QString &name)
{
    setData(SessionModel::ITEM_NAME, name);
}

QString ParameterizedItem::displayName() const
{
    if (mp_parent) {
        int index = mp_parent->getCopyNumberOfChild(this);
        if (index >= 0) {
            // in special cases we fail to create unique name
            QString new_name = m_display_name + QString::number(index);
            return new_name;
        }
    }
    return m_display_name;
}

QString ParameterizedItem::modelType() const
{
    return m_model_type;
}

QString ParameterizedItem::itemLabel() const
{
    return QString("");
}

void ParameterizedItem::setModel(SessionModel *model)
{
    m_model = model;
    // process children as well
    for (auto &child : m_children) {
        child->setModel(model);
    }
}

SessionModel *ParameterizedItem::model() const
{
    return m_model;
}

ParameterizedItem::PortInfo::EPorts ParameterizedItem::port() const
{
    return m_port;
}

void ParameterizedItem::setPort(ParameterizedItem::PortInfo::EPorts nport)
{
    m_port = nport;
}

ParameterizedItem *ParameterizedItem::parent() const
{
    return mp_parent;
}

int ParameterizedItem::childItemCount() const
{
    return m_children.count();
}

int ParameterizedItem::columnCount() const
{
    return SessionModel::MAX_COLUMNS;
}

ParameterizedItem *ParameterizedItem::childAt(int row) const
{
    return m_children.value(row, nullptr);
}

int ParameterizedItem::rowOfChild(ParameterizedItem *child) const
{
    return m_children.indexOf(child);
}

int ParameterizedItem::childNumber() const
{
    if (mp_parent)
        return mp_parent->rowOfChild(const_cast<ParameterizedItem*>(this));

    return -1;
}

bool ParameterizedItem::hasChildItems() const
{
    return !m_children.isEmpty();
}

QList<ParameterizedItem *> ParameterizedItem::childItems() const
{
    return m_children;
}

ParameterizedItem *ParameterizedItem::getChildOfType(const QString &type) const
{
    for (auto child : m_children) {
        if (child->modelType() == type) return child;
    }
    return nullptr;
}

ParameterizedItem *ParameterizedItem::getChildByName(const QString &name) const
{
    for (auto child : m_children) {
        if (child->itemName() == name) return child;
    }
    return nullptr;
}

QList<ParameterizedItem *> ParameterizedItem::getChildrenOfType(const QString &model_type) const
{
    QList<ParameterizedItem *> result;
    for (auto child : m_children) {
        if (child->modelType() == model_type)
            result.append(child);
    }
    return result;
}

void ParameterizedItem::insertChildItem(int row, ParameterizedItem *item)
{
    if (row == -1)
        row = m_children.size();

    item->mp_parent = this;
    item->setModel(m_model);

    if (m_model)
        m_model->beginInsertRows(m_model->indexOfItem(item), row, row);

    m_children.insert(row, item);

    if (item->modelType() == Constants::PropertyType ||
            item->modelType() == Constants::GroupItemType) {
        m_property_attribute[item->itemName()] = PropertyAttribute();
        m_propertyItems.insert(item->itemName(), item);
    }

    if (m_model)
        m_model->endInsertRows();
}

ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    ParameterizedItem *item = m_children.takeAt(row);
    item->mp_parent = nullptr;
    item->setModel(nullptr);
    return item;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

QList<QString> ParameterizedItem::acceptableChildItems() const
{
    return m_valid_children;
}

PropertyAttribute &ParameterizedItem::registerProperty(const QString &name, const QVariant &variant,
                                         const PropertyAttribute &attribute)
{
    if (isRegisteredProperty(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing property " + name);

    ParameterizedItem *property = ItemFactory::createItem(Constants::PropertyType);
    property->setItemName(name);
    property->setValue(variant);
    insertChildItem(-1, property);
    m_property_attribute[name] = attribute;
    return m_property_attribute[name];
}

bool ParameterizedItem::isRegisteredProperty(const QString &name) const
{
    return m_propertyItems.contains(name);
}

QVariant ParameterizedItem::getRegisteredProperty(const QString &name) const
{
    if (!isRegisteredProperty(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property '" + name
            + "', item '" + modelType() + "'");

    return m_propertyItems[name]->value();
}

void ParameterizedItem::setRegisteredProperty(const QString &name, const QVariant &variant)
{
    // check if variant of previous property coincides with new one
    if (!isRegisteredProperty(name))
        return;
    QVariant previous_variant = getRegisteredProperty(name);
    if (GUIHelpers::getVariantType(previous_variant) != GUIHelpers::getVariantType(variant)) {
        qDebug() << "ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new "
                    "variant does not coincide.";
        qDebug() << "New variant" << variant << ", previous " << previous_variant;
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Type of "
                                "previous and new variant does not coincide.");
    }

    m_propertyItems[name]->setValue(variant);
}

void ParameterizedItem::removeRegisteredProperty(const QString &name)
{
    if(isRegisteredProperty(name)) {
        qDebug() << "ParameterizedItem::removeRegisteredProperty()" << name;
        m_property_attribute.remove(name);
        if (ParameterizedItem *para = m_propertyItems[name]) {
            QModelIndex index = m_model->indexOfItem(para);
            m_model->removeRows(index.row(), 1, index.parent());
            m_propertyItems.remove(name);
        }
    }
}

ParameterizedItem *ParameterizedItem::registerGroupProperty(const QString &group_name,
                                                            const Constants::ModelType &group_model)
{
//    qDebug() << "ParameterizedItem::registerGroupProperty() ->"
//             << "this->modelType" << modelType() << "group_name" << group_name << " group_model"
//             << group_model;

    GroupProperty_t group_property
        = GroupPropertyRegistry::createGroupProperty(group_name, group_model);
    GroupItem *groupItem = dynamic_cast<GroupItem *>(ItemFactory::createItem(Constants::GroupItemType));
    groupItem->setGroup(group_property);
    groupItem->setItemName(group_name);
    insertChildItem(-1, groupItem);
//    ParameterizedItem *p_result = m_sub_items[group_name];
//    if (group_property->type() == GroupProperty::FIXED) {
//        p_result->setDisplayName(group_name);
//    }
    return groupItem;
}

bool ParameterizedItem::isGroupProperty(const QString &name) const
{
    if (m_propertyItems.contains(name)) {
        return m_propertyItems[name]->modelType() == Constants::GroupItemType;
    }
    return false;
}

ParameterizedItem *ParameterizedItem::setGroupProperty(const QString &name, const QString &value) const
{
    qDebug() << "ParameterizedItem::setGroupProperty()" << name << value;
    if (GroupItem *item = dynamic_cast<GroupItem *>(m_propertyItems[name])) {
        GroupProperty_t group_property = item->group();
        if (!value.isEmpty()) {
            group_property->setCurrentType(value);
        }
        return group_property->getCurrentItem();
    }
    return nullptr;
}

ParameterizedItem *ParameterizedItem::getGroupItem(const QString &name) const
{
    return setGroupProperty(name);
}

const PropertyAttribute &ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    QMap<QString, PropertyAttribute>::const_iterator it = m_property_attribute.find(name);
    if(it == m_property_attribute.end()) {
        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> Error. "
                                "Unknown property attribute " + name);
    }
    return it.value();
}

PropertyAttribute &ParameterizedItem::getPropertyAttribute(const QString &name)
{
    QMap<QString, PropertyAttribute>::iterator it = m_property_attribute.find(name);
    if(it == m_property_attribute.end()) {
        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> Error. "
                                "Unknown property attribute " + name);
    }
    return it.value();
}

void ParameterizedItem::setPropertyAttribute(const QString &name,
                                             const PropertyAttribute &attribute)
{
    if (!isRegisteredProperty(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property " + name);

    if (!m_property_attribute.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property attribute "
            + name);

    m_property_attribute[name] = attribute;
}

// returns child which should be removed by the model due to overpopulation of children of given
// type
ParameterizedItem *ParameterizedItem::getCandidateForRemoval(ParameterizedItem *new_comer)
{
    if (!new_comer)
        return 0;

    QMap<int, QVector<ParameterizedItem *> > nport_to_nitems;
    foreach (ParameterizedItem *child, m_children) {
//        int nport = child->getRegisteredProperty(OBSOLETE_P_PORT).toInt();
        int nport = int(child->port());
        nport_to_nitems[nport].push_back(child);
    }

    QMap<int, QVector<ParameterizedItem *> >::iterator it = nport_to_nitems.begin();
    while (it != nport_to_nitems.end()) {
        int nport = it.key();
        if (m_port_info.contains(nport)) {
            if (m_port_info[nport].m_item_max_number != 0
                && it.value().size() > m_port_info[nport].m_item_max_number) {
                foreach (ParameterizedItem *item, it.value()) {
                    if (item != new_comer)
                        return item;
                }
            }
        }
        ++it;
    }

    return 0;
}

void ParameterizedItem::setDisplayName(QString display_name)
{
    m_display_name = std::move(display_name);
}

void ParameterizedItem::addToValidChildren(const QString &name, PortInfo::EPorts nport,
                                           int nmax_items)
{
    m_valid_children.append(name);

    if (m_port_info.contains(nport)) {
        m_port_info[nport].m_item_names << name;
        m_port_info[nport].m_item_max_number = nmax_items;
    } else {
        m_port_info[nport] = PortInfo(name, nmax_items);
    }
}

void ParameterizedItem::swapChildren(int first, int second)
{
//    m_children.swap(first, second);
}

int ParameterizedItem::getCopyNumberOfChild(const ParameterizedItem *p_item) const
{
    if (!p_item) return -1;
    int result = -1;
    int count = 0;
    QString model_type = p_item->modelType();
    // check child items:
    if (hasChildItems()) {
        for (auto p_child_item : m_children) {
            QString child_type = p_child_item->modelType();
            if (p_child_item == p_item) {
                result = count;
            }
            if (child_type == model_type && !p_child_item->m_data[SessionModel::ITEM_NAME].isValid()) {
                ++count;
            }
        }
    }
    // check subitems:
//    if (m_sub_items.size() > 0) {
//        for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
//             it != m_sub_items.end(); ++it) {
//            ParameterizedItem *p_sub_item = it.value();
//            QString subitem_type = p_sub_item->modelType();
//            if (p_sub_item == p_item) {
//                result = count;
//            }
//            if (subitem_type == model_type) {
//                ++count;
//            }
//        }
//    }
    if (count > 1) return result;
    return -1;
}









//  END OF REFACTORED PARAMETERIZED ITEM



// START OBSOLETE - please replace this function with setGroupProperty without second parameter
QMap<QString, ParameterizedItem *> ParameterizedItem::getSubItems() const
{
    QMap<QString, ParameterizedItem *> result;
    auto groups = getChildrenOfType(Constants::GroupItemType);
    for (auto child : groups) {
        result.insert(child->itemName(), dynamic_cast<GroupItem*>(child)->group()->getCurrentItem());
    }
    return result;
}
// END OBSOLETE



//void ParameterizedItem::addSubItem(QString name, ParameterizedItem *item)
//{
////    // if (!item) return;
////    Q_ASSERT(item);
////    qDebug() << "ParameterizedItem::addPropertyItem()" << name;

//    if (m_sub_items.contains(name)) {
////        qDebug() << "       ParameterizedItem::addPropertyItem() -> item is already there" << name
////                 << "replacing with " << item->modelType();
////        delete m_sub_items[name];
//        m_sub_items.remove(name);
//    }
//    m_sub_items[name] = item;
//    item->mp_parent = this;
//    insertChild(-1, item); // NEW
//    onSubItemChanged(name);
//    onChildPropertyChange(item);
////    qDebug() << "ParameterizedItem::addPropertyItem() -> about to leave" << name;
//}






void ParameterizedItem::onPropertyChange(const QString &name)
{
    if (mp_parent)
        mp_parent->onChildPropertyChange(this, name);
    emit propertyChanged(name);
}

void ParameterizedItem::onChildPropertyChange(ParameterizedItem *item, const QString &propertyName)
{
//    qDebug() << "ParameterizedItem::onChildPropertyChange()";
    if (mp_parent)
        mp_parent->onChildPropertyChange(item, propertyName);
}

void ParameterizedItem::print() const
{
//    qDebug() << "--- ParameterizedItem::print() ------------------------------------";
//    qDebug() << modelType() << displayName();
//    qDebug() << "--- SubItems ---";
//    for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
//         it != m_sub_items.end(); ++it) {
//        qDebug() << "   key:" << it.key() << " value->modelType:" << it.value()->modelType();
//    }
//    qDebug() << "--- Properties ---";
//    QList<QByteArray> property_names = dynamicPropertyNames();
//    for (int i = 0; i < property_names.length(); ++i) {
//        QString name(property_names[i]);
//        qDebug() << name << property(name.toUtf8().constData());
//    }
//    qDebug() << " ";
}


////! called when new SubItem appeared
void ParameterizedItem::onSubItemChanged(const QString &propertyName)
{
//    connect(m_sub_items[propertyName], SIGNAL(propertyChanged(QString)), this,
//            SLOT(processSubItemPropertyChanged(QString)), Qt::UniqueConnection);
//    emit subItemChanged(propertyName);
}

void ParameterizedItem::onSubItemPropertyChanged(const QString &property_group,
                                                 const QString &property_name)
{
    emit subItemPropertyChanged(property_group, property_name);
    if (mp_parent)
        mp_parent->onChildPropertyChange(this, property_group);
}

void ParameterizedItem::onSiblingsChanged()
{
    emit siblingsChanged();
}

////! called when SubItem change one of its properties
void ParameterizedItem::processSubItemPropertyChanged(const QString &propertyName)
{
    Q_UNUSED(propertyName);
    return;
    ParameterizedItem *propertyItem = qobject_cast<ParameterizedItem *>(sender());
    /*for (QMap<QString, ParameterizedItem *>::iterator it = m_sub_items.begin();
         it != m_sub_items.end(); ++it) {
        if (it.value() == propertyItem) {
            GroupProperty_t group_property
                = getRegisteredProperty(it.key()).value<GroupProperty_t>();
            group_property->setCurrentLabel(propertyItem->itemLabel());
            onSubItemPropertyChanged(it.key(), propertyName);
            return;
        }
    }*/
    throw -1; // NEW
//    throw GUIHelpers::Error("ParameterizedItem::onSubItemPropertyChanged() ->"
//                            " Error. No such propertyItem found");
}
