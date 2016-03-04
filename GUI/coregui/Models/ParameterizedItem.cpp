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

#include <sstream>
#include <QDebug>

class SessionItemData
{
public:
    inline SessionItemData() : role(-1) {}
    inline SessionItemData(int r, const QVariant &v) : role(r), value(v) {}
    int role;
    QVariant value;
    inline bool operator==(const SessionItemData &other) const {
        return role == other.role && value == other.value;
    }
};

const QString ParameterizedItem::P_NAME = "Name";

ParameterizedItem::ParameterizedItem(QString modelType)
    : mp_parent(0)
    , m_model(0)
    , m_data(QVector<QVariant>(SessionModel::MAX_COLUMNS)) // TODO data vector ~> role vector
    , m_model_type(modelType) // TODO model type ~ ModelTypeRole
    , m_port(PortInfo::DEFAULT) // TODO ports ~> tags
    , m_defaultTag(QString())
{
    Q_ASSERT(!modelType.isEmpty());


    setDisplayName(m_model_type); // TODO displayName ~> tag name

    m_attribute.setVisible(); // TODO attributes ~> flags & roles
}

// internal
ParameterizedItem::~ParameterizedItem()
{
    QVector<ParameterizedItem*>::const_iterator it;
    for (it = m_children.constBegin(); it != m_children.constEnd(); ++it) {
        ParameterizedItem *child = *it;
        if (child)
            child->setModel(nullptr);
        delete child;
    }
    m_children.clear();
    if (mp_parent && m_model)
        mp_parent->childDeleted(this);
}

// internal
void ParameterizedItem::childDeleted(ParameterizedItem *child)
{
    int index = rowOfChild(child);
    Q_ASSERT(index != -1);
    m_children.replace(index, nullptr);
}

// internal
void ParameterizedItem::setParentAndModel(ParameterizedItem *parent, SessionModel *model)
{
    setModel(model);
    mp_parent = parent;
}

// internal
void ParameterizedItem::setModel(SessionModel *model)
{
    m_model = model;
    if (m_mapper) {
        m_mapper->setItem(this);
    }
    // process children as well
    for (auto &child : m_children) {
        child->setModel(model);
    }
}

// protected
bool ParameterizedItem::registerTag(QString name, int min, int max, QStringList modelTypes)
{
    // max: -1 -> no limits
    // min = max = 1 -> fixed
    if (min < 0 || (min > max && max >= 0))
        return false;
    if (name.isEmpty() || getTagInfo(name).isValid())
        return false;
    m_tags.append(SessionTagInfo(name, min, max, modelTypes));
    return true;
}

// protected
SessionTagInfo ParameterizedItem::getTagInfo(const QString &name) const
{
    QVector<SessionTagInfo>::const_iterator it;
    for (it = m_tags.constBegin(); it != m_tags.constEnd(); ++it) {
        SessionTagInfo tagInfo = *it;
        if (tagInfo.name == name)
            return tagInfo;
    }
    return SessionTagInfo();
}



// internal
bool ParameterizedItem::insertItem(int row, ParameterizedItem *item, const QString &tag)
{
    SessionTagInfo tagInfo = getTagInfo(tag);
    if (!tagInfo.isValid())
        return false;
    if (row < 0 || row > tagInfo.childCount)
        return false;
    if (tagInfo.max >= 0 && tagInfo.childCount == tagInfo.max)
        return false;
    if (!tagInfo.modelTypes.isEmpty()) {
        if (!tagInfo.modelTypes.contains(item->modelType()))
            return false;
    }
    int index = tagStartIndex(tag) + row;
    Q_ASSERT(index <= m_children.size());
    if (m_model)
            m_model->beginInsertRows(this->index(),index, index+1);
    if (item) {
        if (item->parent() == nullptr) {
            item->setParentAndModel(this, m_model);
        } else {
            qDebug() << "Double insertion of item";
            return false;
        }
    }
    m_children.insert(index, item);

    QVector<SessionTagInfo>::iterator it;
    for (it = m_tags.begin(); it != m_tags.end(); ++it) {
        if (it->name == tag) {
            it->childCount++;
            break;
        }
    }

    if (m_model)
            m_model->endInsertRows();
    return true;
}

ParameterizedItem *ParameterizedItem::takeItem(int row, const QString &tag)
{
    SessionTagInfo tagInfo = getTagInfo(tag);
    if (!tagInfo.isValid())
        return nullptr;
    if (row < 0 || row >= tagInfo.childCount)
        return nullptr;
    if (tagInfo.childCount <= tagInfo.min)
        return nullptr;
    int index = tagStartIndex(tag) + row;
    Q_ASSERT(index >= 0 && index <= m_children.size());
    if (m_model)
            m_model->beginRemoveRows(this->index(),index, index+1);
    ParameterizedItem *result = m_children.takeAt(index);

    QVector<SessionTagInfo>::iterator it;
    for (it = m_tags.begin(); it != m_tags.end(); ++it) {
        if (it->name == tag) {
            it->childCount--;
            break;
        }
    }

    if (m_model)
            m_model->endRemoveRows();
    return result;
}

// internal
int ParameterizedItem::tagStartIndex(const QString &name) const
{
    int index = 0;
    QVector<SessionTagInfo>::const_iterator it;
    for (it = m_tags.constBegin(); it != m_tags.constEnd(); ++it) {
        SessionTagInfo tagInfo = *it;
        if (tagInfo.name == name) {
            return index;
        } else {
            index += tagInfo.childCount;
        }
    }
    return -1;
}

ParameterizedItem *ParameterizedItem::getItem(QString tag, int index) const
{
    if (tag.isEmpty())
        tag = m_defaultTag;
    SessionTagInfo tagInfo = getTagInfo(tag);
    if (!tagInfo.isValid())
        return nullptr;
    if (tagInfo.childCount == 0)
        return nullptr;
    if (index < 0 || index >= tagInfo.childCount)
        return nullptr;
    int acc_index = tagStartIndex(tag) + index;
    Q_ASSERT(acc_index >= 0 && acc_index < m_children.size());
    return m_children[acc_index];
}

QVector<ParameterizedItem *> ParameterizedItem::getItems(QString tag) const
{
    if (tag.isEmpty())
        tag = m_defaultTag;
    SessionTagInfo tagInfo = getTagInfo(tag);
    if (!tagInfo.isValid())
        return QVector<ParameterizedItem*>();
    int index = tagStartIndex(tag);
    Q_ASSERT(index >= 0 && index < m_children.size());
    return m_children.mid(index, tagInfo.childCount);
}



QVariant ParameterizedItem::readUserRoles(int role) const
{
    if (role == SessionModel::ModelTypeRole)
        return m_model_type;
    else if (role == SessionModel::LabelRole) {
        if (isRegisteredProperty(P_NAME)) {
            return getRegisteredProperty(P_NAME);
        } else {
            return displayName();
        }
    }

    return QVariant();
}

bool ParameterizedItem::canWriteUserRole(int role) const
{
    if (role == SessionModel::ModelTypeRole || role == SessionModel::LabelRole)
        return false;

    return true;
}



QVariant ParameterizedItem::data(int role) const
{
    QVariant output = readUserRoles(role);
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    if (!output.isValid()) {
        QVector<SessionItemData>::const_iterator it;
        for (it = m_values.begin(); it != m_values.end(); ++it) {
            if ((*it).role == role)
                return (*it).value;
        }
    }
    return output;
}

bool ParameterizedItem::setData(int role, const QVariant &value)
{
    if (!canWriteUserRole(role))
        return false;
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    QVector<SessionItemData>::iterator it;
    for (it = m_values.begin(); it != m_values.end(); ++it) {
        if ((*it).role == role) {
            if (value.isValid()) {
                if ((*it).value.type() == value.type() && (*it).value == value)
                    return true;
                (*it).value = value;
            } else {
                m_values.erase(it);
            }
            if (m_model)
                emitValueChanged(QVector<int>() << role);
            return true;
        }
    }
    m_values.append(SessionItemData(role, value));
    if (m_model)
        emitValueChanged(QVector<int>() << role);

    return true;

}



// TODO : refactor following code

bool ParameterizedItem::hasData(int column)
{
    return data(column).isValid();
}

void ParameterizedItem::emitValueChanged(QVector<int> roles)
{
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        index = index.sibling(index.row(), SessionModel::ITEM_VALUE);
        m_model->dataChanged(index, index, roles);
    }
}

QVariant ParameterizedItem::value() const
{
    return data(Qt::DisplayRole);
}

bool ParameterizedItem::setValue(QVariant value)
{
    return setData(Qt::DisplayRole, value);
}

QString ParameterizedItem::itemName() const
{
    return data(SessionModel::LabelRole).toString();
}

void ParameterizedItem::setItemName(const QString &name)
{
    if (isRegisteredProperty(P_NAME)) {
        setRegisteredProperty(P_NAME, name);
    } else {
        registerProperty(P_NAME, name);
    }
}

QString ParameterizedItem::displayName() const
{
    if (mp_parent) {
        int index = mp_parent->getCopyNumberOfChild(this);
        if (index >= 0 && modelType() != Constants::PropertyType &&
                modelType() != Constants::GroupItemType) {
            QString new_name = m_display_name + QString::number(index);
            for (auto other : parent()->childItems()) {
                if (other != this) {
                    if (isRegisteredProperty(P_NAME) && other->itemName() == new_name) {
                        ++ index;
                        new_name = m_display_name + QString::number(index);
                    }
                }
            }
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

QModelIndex ParameterizedItem::index() const
{
    if (m_model) {
        return m_model->indexOfItem(const_cast<ParameterizedItem*>(this));
    }
    return QModelIndex();
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

QVector<ParameterizedItem *> ParameterizedItem::childItems() const
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

QList<ParameterizedItem *> ParameterizedItem::getUnregisteredChildren() const
{
    QList<ParameterizedItem *> result;
    for (auto child : m_children) {
        if (!isRegisteredProperty(child->itemName()))
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

    qDebug() << "IIIII ParameterizedItem::insertChildItem this" << this << this->modelType() << this->itemName() << "itemToInsert" << item << item->modelType() << item->itemName();

    if (m_model) {
        qDebug() << "AAA beginInsertRows" << m_model->indexOfItem(this);
        m_model->beginInsertRows(m_model->indexOfItem(this), row, row);
    }

    m_children.insert(row, item);

    if (item->modelType() == Constants::PropertyType ||
            item->modelType() == Constants::GroupItemType) {
        m_propertyItems.insert(item->itemName(), item);
    }

    if (m_model) {
        qDebug() << "AAA endInsertRows";
        m_model->endInsertRows();
    }
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

//! Registers new property. If variant represents some valid modelType, appropriate
//! item will be created. I
PropertyAttribute &ParameterizedItem::registerProperty(const QString &name, const QVariant &variant,
                                         const PropertyAttribute &attribute)
{
    if (isRegisteredProperty(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing property " + name);

    QString property_type = Constants::PropertyType;

    // normal item as child
//    if(variant.type() == QVariant::String &&
//            ItemFactory::isValidItemType(variant.toString())) {
//        property_type = variant.toString();
//        qDebug() << "AAAA" << property_type;
//        Q_ASSERT(0);
//    }

    ParameterizedItem *property = ItemFactory::createItem(property_type);
    property->setDisplayName(name);
    property->setAttribute(attribute);
    insertChildItem(-1, property);

//    if(property_type==Constants::PropertyType) {
        property->setValue(variant);
//    } else {
//        m_propertyItems.insert(property->itemName(), property);
//    }
    return property->getAttribute();
}

bool ParameterizedItem::isRegisteredProperty(const QString &name) const
{
    return m_propertyItems.contains(name);
}

ParameterizedItem *ParameterizedItem::getPropertyItem(const QString &name) const
{
    if (isRegisteredProperty(name)) {
        return m_propertyItems[name];
    }
    return 0;
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
        throw GUIHelpers::Error("Property not existing!");
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

void ParameterizedItem::emitPropertyChanged(const QString &name, QVector<int> roles)
{
    if (isRegisteredProperty(name)) {
        if (roles.isEmpty())
            getPropertyItem(name)->emitValueChanged();
        else
            getPropertyItem(name)->emitValueChanged(roles);
    }
}

void ParameterizedItem::removeRegisteredProperty(const QString &name)
{
    if(isRegisteredProperty(name)) {
        qDebug() << "ParameterizedItem::removeRegisteredProperty()" << name;
        if (ParameterizedItem *para = m_propertyItems[name]) {
            if (m_model) {
                QModelIndex index = m_model->indexOfItem(para);
                m_model->removeRows(index.row(), 1, index.parent());
                m_propertyItems.remove(name);
            } else {
                m_children.removeAll(m_propertyItems[name]);
                m_propertyItems.remove(name);
            }
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
    groupItem->setDisplayName(group_name);
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

ParameterizedItem *ParameterizedItem::getGroupItem(const QString &name, const QString &type) const
{
    if (GroupItem *item = dynamic_cast<GroupItem *>(m_propertyItems[name])) {
        GroupProperty_t group_property = item->group();
        if (type.isEmpty()) {
            return group_property->getCurrentItem();
        }
        QString backup = group_property->getCurrentType();
        group_property->setCurrentType(type);
        ParameterizedItem *value = group_property->getCurrentItem();
        group_property->setCurrentType(backup);
        return value;
    }
    return nullptr;
}

const PropertyAttribute &ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    if(name.isEmpty()) return m_attribute;

    if(ParameterizedItem *propertyItem = getPropertyItem(name)) {
        return propertyItem->getAttribute();
    } else {
        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> "
                                "Error. Unknown property item " + name);
    }
}

PropertyAttribute &ParameterizedItem::getPropertyAttribute(const QString &name)
{
    return const_cast<PropertyAttribute &>(
        static_cast<const ParameterizedItem *>(this)->getPropertyAttribute(name));
}

const PropertyAttribute &ParameterizedItem::getAttribute() const
{
    return m_attribute;
}

PropertyAttribute &ParameterizedItem::getAttribute()
{
    return const_cast<PropertyAttribute &>(
        static_cast<const ParameterizedItem *>(this)->getAttribute());
}

void ParameterizedItem::setPropertyAttribute(const QString &name,
                                             const PropertyAttribute &attribute)
{
    if(ParameterizedItem *propertyItem = getPropertyItem(name)) {
        propertyItem->setAttribute(attribute);
    } else {
        throw GUIHelpers::Error(
            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property item " + name);

    }
}

void ParameterizedItem::setAttribute(const PropertyAttribute &attribute)
{
    m_attribute = attribute;
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

ModelMapper *ParameterizedItem::mapper()
{
    if (!m_mapper) {
        m_mapper = std::unique_ptr<ModelMapper>(new ModelMapper);
        m_mapper->setItem(this);
    }
    return m_mapper.get();
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

void ParameterizedItem::swapChildren(int /* first */, int /* second */)
{
    // FIXME
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
    if (count > 1) return result;
    return -1;
}
