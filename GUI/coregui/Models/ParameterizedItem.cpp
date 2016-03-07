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
{
    Q_ASSERT(!modelType.isEmpty());

    setData(SessionModel::ModelTypeRole, modelType);
    setDisplayName(modelType); // TODO displayName ~> tag name
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
    if (row == -1)
        row = tagInfo.childCount;
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
    result->setParentAndModel(nullptr, nullptr);

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

QString ParameterizedItem::tagFromItem(const ParameterizedItem *item) const
{
    int index = m_children.indexOf(const_cast<ParameterizedItem*>(item));
    if (index == -1)
        return QString();
    QVector<SessionTagInfo>::const_iterator it;
    for (it = m_tags.constBegin(); it != m_tags.constEnd(); ++it) {
        SessionTagInfo tagInfo = *it;
        if (index < tagInfo.childCount) {
            return tagInfo.name;
        } else {
            index -= tagInfo.childCount;
        }
    }
}

QVector<int> ParameterizedItem::getRoles() const
{
    QVector<int> result;
    QVector<SessionItemData>::const_iterator it;
    for (it = m_values.constBegin(); it != m_values.constEnd(); ++it) {
        result.append(it->role);
    }
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
        tag = defaultTag();
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
        tag = defaultTag();
    SessionTagInfo tagInfo = getTagInfo(tag);
    if (!tagInfo.isValid())
        return QVector<ParameterizedItem*>();
    int index = tagStartIndex(tag);
    Q_ASSERT(index >= 0 && index < m_children.size());
    return m_children.mid(index, tagInfo.childCount);
}
void ParameterizedItem::changeFlags(bool enabled, int flag)
{
    int flags = this->flags();
    if (enabled) {
        flags |= flag;
    } else {
        flags &= ~flag;
    }
    setData(SessionModel::FlagRole, flags);
}

int ParameterizedItem::flags() const
{
    QVariant flags = data(SessionModel::FlagRole);
    if (!flags.isValid())
        return SessionModel::VISIBLE | SessionModel::EDITABLE | SessionModel::ENABLED;

    return flags.toInt();
}



QVariant ParameterizedItem::data(int role) const
{
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    QVector<SessionItemData>::const_iterator it;
    for (it = m_values.begin(); it != m_values.end(); ++it) {
        if ((*it).role == role)
            return (*it).value;
    }
    return QVariant();
}

bool ParameterizedItem::setData(int role, const QVariant &value)
{
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
                emitValueChanged(role);
            return true;
        }
    }
    m_values.append(SessionItemData(role, value));
    if (m_model)
        emitValueChanged(role);

    return true;

}




void ParameterizedItem::emitValueChanged(int role)
{
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        m_model->dataChanged(index, index, QVector<int>() << role);
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
    if (isRegisteredProperty(P_NAME)) {
        return getRegisteredProperty(P_NAME).toString();
    } else {
        return displayName();
    }
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
            return data(SessionModel::DisplayNameRole).toString() + QString::number(index);
        }
    }
    return data(SessionModel::DisplayNameRole).toString();
}

QString ParameterizedItem::modelType() const
{
    return data(SessionModel::ModelTypeRole).toString();
}

QString ParameterizedItem::itemLabel() const
{
    return QString("");
}

SessionModel *ParameterizedItem::model() const
{
    return m_model;
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
    SessionTagInfo tagInfo = getTagInfo(defaultTag());
    if (!tagInfo.isValid())
        return;
    if (row == -1)
        row = tagInfo.childCount;
    Q_ASSERT(insertItem(row, item, tagInfo.name));

//    item->mp_parent = this;
//    item->setModel(m_model);

//    qDebug() << "IIIII ParameterizedItem::insertChildItem this" << this << this->modelType() << this->itemName() << "itemToInsert" << item << item->modelType() << item->itemName();

//    if (m_model) {
//        qDebug() << "AAA beginInsertRows" << m_model->indexOfItem(this);
//        m_model->beginInsertRows(m_model->indexOfItem(this), row, row);
//    }

//    m_children.insert(row, item);

//    if (item->modelType() == Constants::PropertyType ||
//            item->modelType() == Constants::GroupItemType) {
//        m_propertyItems.insert(item->itemName(), item);
//    }

//    if (m_model) {
//        qDebug() << "AAA endInsertRows";
//        m_model->endInsertRows();
//    }
}


ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    return takeItem(row, defaultTag());
//    ParameterizedItem *item = m_children.takeAt(row);
//    item->mp_parent = nullptr;
//    item->setModel(nullptr);
//    return item;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return getTagInfo(defaultTag()).modelTypes.contains(child_name);
}

QList<QString> ParameterizedItem::acceptableChildItems() const
{
    return getTagInfo(defaultTag()).modelTypes.toVector().toList();
}

//! Registers new property. If variant represents some valid modelType, appropriate
//! item will be created. I
ParameterizedItem *ParameterizedItem::registerProperty(const QString &name, const QVariant &variant)
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
//    property->setAttribute(attribute);
    registerTag(name, 1, 1, QStringList() << property_type);
    insertItem(0, property, name);
//    insertChildItem(-1, property);

//    if(property_type==Constants::PropertyType) {
        property->setValue(variant);
//    } else {
//        m_propertyItems.insert(property->itemName(), property);
//    }
        return property;
}

bool ParameterizedItem::isRegisteredProperty(const QString &name) const
{
    return getTagInfo(name).isValid();
}

QVariant ParameterizedItem::getRegisteredProperty(const QString &name) const
{
    if (!isRegisteredProperty(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property '" + name
            + "', item '" + modelType() + "'");

    return getItem(name)->value();
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

     getItem(name)->setValue(variant);
}

void ParameterizedItem::removeRegisteredProperty(const QString &name)
{
    if(isRegisteredProperty(name)) {
        qDebug() << "ParameterizedItem::removeRegisteredProperty()" << name;
        if (ParameterizedItem *para =  takeItem(0, name)) {
            delete para;
//            if (m_model) {
//                QModelIndex index = m_model->indexOfItem(para);
//                m_model->removeRows(index.row(), 1, index.parent());
//                m_propertyItems.remove(name);
//            } else {
//                m_children.removeAll(m_propertyItems[name]);
//                m_propertyItems.remove(name);
//            }
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
    registerTag(group_name, 1, 1, QStringList() << Constants::GroupItemType);
    insertItem(0, groupItem, group_name);
//    insertChildItem(-1, groupItem);
//    ParameterizedItem *p_result = m_sub_items[group_name];
//    if (group_property->type() == GroupProperty::FIXED) {
//        p_result->setDisplayName(group_name);
//    }
    return groupItem;
}

bool ParameterizedItem::isGroupProperty(const QString &name) const
{
    SessionTagInfo tagInfo = getTagInfo(name);
    if (tagInfo.isValid()) {
        return tagInfo.modelTypes.contains(Constants::GroupItemType);
    }
    return false;
}

ParameterizedItem *ParameterizedItem::setGroupProperty(const QString &name, const QString &value) const
{
    qDebug() << "ParameterizedItem::setGroupProperty()" << name << value;
    if (GroupItem *item = dynamic_cast<GroupItem *>(getItem(name))) {
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
    if (GroupItem *item = dynamic_cast<GroupItem *>(getItem(name))) {
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

void ParameterizedItem::setVisible(bool enabled)
{
    changeFlags(enabled, SessionModel::VISIBLE);
}

void ParameterizedItem::setEnabled(bool enabled)
{
    changeFlags(enabled, SessionModel::ENABLED);
}

void ParameterizedItem::setEditable(bool enabled)
{
    changeFlags(enabled, SessionModel::EDITABLE);
}

bool ParameterizedItem::isVisible() const
{
    return flags() & SessionModel::VISIBLE;
}

bool ParameterizedItem::isEnabled() const
{
    return flags() & SessionModel::ENABLED;
}

bool ParameterizedItem::isEditable() const
{
    return flags() & SessionModel::EDITABLE;
}

AttLimits ParameterizedItem::limits() const
{
    return data(SessionModel::LimitsRole).value<AttLimits>();
}

void ParameterizedItem::setLimits(AttLimits value)
{
    this->setData(SessionModel::LimitsRole, QVariant::fromValue<AttLimits>(value));
}

int ParameterizedItem::decimals() const
{
    return data(SessionModel::DecimalRole).toInt();
}

void ParameterizedItem::setDecimals(int n)
{
    setData(SessionModel::DecimalRole, n);
}

QString ParameterizedItem::toolTip() const
{
    return data(Qt::ToolTipRole).toString();
}

void ParameterizedItem::setToolTip(QString tooltip)
{
    setData(Qt::ToolTipRole, tooltip);
}

QString ParameterizedItem::defaultTag() const
{
    return data(SessionModel::DefaultTagRole).toString();
}

void ParameterizedItem::setDefaultTag(QString tag)
{
    setData(SessionModel::DefaultTagRole, tag);
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
    setData(SessionModel::DisplayNameRole, display_name);
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
            if (child_type == model_type && !p_child_item->isRegisteredProperty(P_NAME)) {
                ++count;
            }
        }
    }
    if (count > 1) return result;
    return -1;
}
