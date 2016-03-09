// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterizedItem.cpp
//! @brief     Implements class SessionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SessionItem.h"
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

const QString SessionItem::P_NAME = "Name";

SessionItem::SessionItem(const QString &modelType)
    : m_parent(0)
    , m_model(0)
{
    Q_ASSERT(!modelType.isEmpty());

    setData(SessionModel::ModelTypeRole, modelType);
    setDisplayName(modelType); // TODO displayName ~> tag name
}

// internal
SessionItem::~SessionItem()
{
    QVector<SessionItem*>::const_iterator it;
    for (it = m_children.constBegin(); it != m_children.constEnd(); ++it) {
        SessionItem *child = *it;
        if (child)
            child->setModel(nullptr);
        delete child;
    }
    m_children.clear();
    if (m_parent && m_model)
        m_parent->childDeleted(this);
}

// internal
void SessionItem::childDeleted(SessionItem *child)
{
    int index = rowOfChild(child);
    Q_ASSERT(index != -1);
    m_children.replace(index, nullptr);
}

// internal
void SessionItem::setParentAndModel(SessionItem *parent, SessionModel *model)
{
    setModel(model);
    m_parent = parent;
}

// internal
void SessionItem::setModel(SessionModel *model)
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

bool SessionItem::registerTag(const QString &name, int min, int max, QStringList modelTypes)
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

SessionTagInfo SessionItem::getTagInfo(const QString &tag) const
{
    QString tagName = tag.isEmpty() ? defaultTag() : tag;
    QVector<SessionTagInfo>::const_iterator it;
    for (it = m_tags.constBegin(); it != m_tags.constEnd(); ++it) {
        SessionTagInfo tagInfo = *it;
        if (tagInfo.name == tagName)
            return tagInfo;
    }
    return SessionTagInfo();
}


bool SessionItem::insertItem(int row, SessionItem *item, const QString &tag)
{
    if (!item)
        return false;
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    SessionTagInfo tagInfo = getTagInfo(tagName);
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
    int index = tagStartIndex(tagName) + row;
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
        if (it->name == tagName) {
            it->childCount++;
            break;
        }
    }

    if (m_model)
            m_model->endInsertRows();
    return true;
}

SessionItem *SessionItem::takeItem(int row, const QString &tag)
{
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    SessionTagInfo tagInfo = getTagInfo(tagName);
    if (!tagInfo.isValid())
        return nullptr;
    if (row < 0 || row >= tagInfo.childCount)
        return nullptr;
    if (tagInfo.childCount <= tagInfo.min)
        return nullptr;
    int index = tagStartIndex(tagName) + row;
    Q_ASSERT(index >= 0 && index <= m_children.size());
    if (m_model)
            m_model->beginRemoveRows(this->index(),index, index);
    SessionItem *result = m_children.takeAt(index);
    result->setParentAndModel(nullptr, nullptr);

    QVector<SessionTagInfo>::iterator it;
    for (it = m_tags.begin(); it != m_tags.end(); ++it) {
        if (it->name == tagName) {
            it->childCount--;
            break;
        }
    }

    if (m_model)
            m_model->endRemoveRows();
    return result;
}

QString SessionItem::tagFromItem(const SessionItem *item) const
{
    int index = m_children.indexOf(const_cast<SessionItem*>(item));
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
    return QString();
}

QVector<int> SessionItem::getRoles() const
{
    QVector<int> result;
    QVector<SessionItemData>::const_iterator it;
    for (it = m_values.constBegin(); it != m_values.constEnd(); ++it) {
        result.append(it->role);
    }
    return result;
}

// internal
int SessionItem::tagStartIndex(const QString &name) const
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

SessionItem *SessionItem::getItem(const QString &tag, int row) const
{
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    SessionTagInfo tagInfo = getTagInfo(tagName);
    if (!tagInfo.isValid())
        return nullptr;
    if (tagInfo.childCount == 0)
        return nullptr;
    if (row < 0 || row >= tagInfo.childCount)
        return nullptr;
    int index = tagStartIndex(tagName) + row;
    Q_ASSERT(index >= 0 && index < m_children.size());
    return m_children[index];
}

QVector<SessionItem *> SessionItem::getItems(const QString &tag) const
{
    const QString tagName = tag.isEmpty() ? defaultTag() : tag;
    SessionTagInfo tagInfo = getTagInfo(tagName);
    if (!tagInfo.isValid())
        return QVector<SessionItem*>();
    int index = tagStartIndex(tagName);
    Q_ASSERT(index >= 0 && index <= m_children.size());
    return m_children.mid(index, tagInfo.childCount);
}
void SessionItem::changeFlags(bool enabled, int flag)
{
    int flags = this->flags();
    if (enabled) {
        flags |= flag;
    } else {
        flags &= ~flag;
    }
    setData(SessionModel::FlagRole, flags);
}

int SessionItem::flags() const
{
    QVariant flags = data(SessionModel::FlagRole);
    if (!flags.isValid())
        return SessionModel::VISIBLE | SessionModel::EDITABLE | SessionModel::ENABLED;

    return flags.toInt();
}



QVariant SessionItem::data(int role) const
{
    role = (role == Qt::EditRole) ? Qt::DisplayRole : role;
    QVector<SessionItemData>::const_iterator it;
    for (it = m_values.begin(); it != m_values.end(); ++it) {
        if ((*it).role == role)
            return (*it).value;
    }
    return QVariant();
}

bool SessionItem::setData(int role, const QVariant &value)
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
                emitDataChanged(role);
            return true;
        }
    }
    m_values.append(SessionItemData(role, value));
    if (m_model)
        emitDataChanged(role);

    return true;
}




void SessionItem::emitDataChanged(int role)
{
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        m_model->dataChanged(index, index, QVector<int>() << role);
    }
}

QVariant SessionItem::value() const
{
    return data(Qt::DisplayRole);
}

bool SessionItem::setValue(QVariant value)
{
    QVariant previous_variant = this->value();
    if (previous_variant.isValid() && GUIHelpers::getVariantType(previous_variant) != GUIHelpers::getVariantType(value)) {
        qDebug() << "ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new "
                    "variant does not coincide.";
        qDebug() << "New variant" << value << ", previous " << previous_variant;
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Type of "
                                "previous and new variant does not coincide.");
    }
    return setData(Qt::DisplayRole, value);
}

QString SessionItem::itemName() const
{
    if (isTag(P_NAME)) {
        return getItemValue(P_NAME).toString();
    } else {
        return displayName();
    }
}

void SessionItem::setItemName(const QString &name)
{
    if (isTag(P_NAME)) {
        setItemValue(P_NAME, name);
    } else {
        addProperty(P_NAME, name);
    }
}

QString SessionItem::displayName() const
{
    if (m_parent) {
        int index = m_parent->getCopyNumberOfChild(this);
        if (index >= 0 && modelType() != Constants::PropertyType &&
                modelType() != Constants::GroupItemType) {
            return data(SessionModel::DisplayNameRole).toString() + QString::number(index);
        }
    }
    return data(SessionModel::DisplayNameRole).toString();
}

QString SessionItem::modelType() const
{
    return data(SessionModel::ModelTypeRole).toString();
}

QString SessionItem::itemLabel() const
{
    return QString("");
}

SessionModel *SessionItem::model() const
{
    return m_model;
}

QModelIndex SessionItem::index() const
{
    if (m_model) {
        return m_model->indexOfItem(const_cast<SessionItem*>(this));
    }
    return QModelIndex();
}

SessionItem *SessionItem::parent() const
{
    return m_parent;
}

int SessionItem::rowCount() const
{
    return m_children.count();
}

SessionItem *SessionItem::childAt(int row) const
{
    return m_children.value(row, nullptr);
}

int SessionItem::rowOfChild(SessionItem *child) const
{
    return m_children.indexOf(child);
}

int SessionItem::childNumber() const
{
    if (m_parent)
        return m_parent->rowOfChild(const_cast<SessionItem*>(this));

    return -1;
}

bool SessionItem::hasChildren() const
{
    return !m_children.isEmpty();
}

QVector<SessionItem *> SessionItem::childItems() const
{
    return m_children;
}

SessionItem *SessionItem::getChildOfType(const QString &type) const
{
    for (auto child : m_children) {
        if (child->modelType() == type) return child;
    }
    return nullptr;
}

SessionItem *SessionItem::getChildByName(const QString &name) const
{
    for (auto child : m_children) {
        if (child->itemName() == name) return child;
    }
    return nullptr;
}

QVector<SessionItem *> SessionItem::getChildrenOfType(const QString &model_type) const
{
    QVector<SessionItem *> result;
    for (auto child : m_children) {
        if (child->modelType() == model_type)
            result.append(child);
    }
    return result;
}


SessionItem *SessionItem::takeRow(int row)
{
//    return takeItem(row, defaultTag());
    SessionItem *item = childAt(row);
    QString tag = tagFromItem(item);
    auto items = getItems(tag);
    return takeItem(items.indexOf(item), tag);
}

bool SessionItem::acceptsAsDefaultChild(const QString &child_name) const
{
    return getTagInfo(defaultTag()).modelTypes.contains(child_name);
}

QVector<QString> SessionItem::acceptableDefaultChildTypes() const
{
    return getTagInfo(defaultTag()).modelTypes.toVector();
}

//! Registers new property. If variant represents some valid modelType, appropriate
//! item will be created. I
SessionItem *SessionItem::addProperty(const QString &name, const QVariant &variant)
{
    if (isTag(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing property " + name);

    const QString property_type = Constants::PropertyType;
    SessionItem *property = ItemFactory::createItem(property_type);
    property->setDisplayName(name);
    Q_ASSERT(registerTag(name, 1, 1, QStringList() << property_type));
    Q_ASSERT(insertItem(0, property, name));
    property->setValue(variant);
    return property;
}

bool SessionItem::isTag(const QString &name) const
{
    return getTagInfo(name).isValid();
}

QVariant SessionItem::getItemValue(const QString &tag) const
{
    if (!isTag(tag))
        throw GUIHelpers::Error(
            "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property '" + tag
            + "', item '" + modelType() + "'");

    return getItem(tag)->value();
}

void SessionItem::setItemValue(const QString &tag, const QVariant &variant)
{
    // check if variant of previous property coincides with new one
    if (!isTag(tag))
        throw GUIHelpers::Error("Property not existing!");

     getItem(tag)->setValue(variant);
}

SessionItem *SessionItem::addGroupProperty(const QString &groupName, const QString &groupModel)
{
    GroupProperty_t group_property
        = GroupPropertyRegistry::createGroupProperty(groupName, groupModel);
    GroupItem *groupItem = dynamic_cast<GroupItem *>(ItemFactory::createItem(Constants::GroupItemType));
    Q_ASSERT(groupItem);
    groupItem->setGroup(group_property);
    groupItem->setDisplayName(groupName);
    Q_ASSERT(registerTag(groupName, 1, 1, QStringList() << Constants::GroupItemType));
    Q_ASSERT(insertItem(0, groupItem, groupName));
    return groupItem;
}

SessionItem *SessionItem::setGroupProperty(const QString &name, const QString &value) const
{
    qDebug() << "ParameterizedItem::setGroupProperty()" << name << value;
    if (GroupItem *item = dynamic_cast<GroupItem *>(getItem(name))) {
        GroupProperty_t group_property = item->group();
        group_property->setCurrentType(value);
        return group_property->getCurrentItem();
    }
    return nullptr;
}

SessionItem *SessionItem::getGroupItem(const QString &name, const QString &type) const
{
    if (GroupItem *item = dynamic_cast<GroupItem *>(getItem(name))) {
        GroupProperty_t group_property = item->group();
        if (type.isEmpty()) {
            return group_property->getCurrentItem();
        }
        QString backup = group_property->getCurrentType();
        group_property->setCurrentType(type);
        SessionItem *value = group_property->getCurrentItem();
        group_property->setCurrentType(backup);
        return value;
    }
    return nullptr;
}

void SessionItem::setVisible(bool enabled)
{
    changeFlags(enabled, SessionModel::VISIBLE);
}

void SessionItem::setEnabled(bool enabled)
{
    changeFlags(enabled, SessionModel::ENABLED);
}

void SessionItem::setEditable(bool enabled)
{
    changeFlags(enabled, SessionModel::EDITABLE);
}

bool SessionItem::isVisible() const
{
    return flags() & SessionModel::VISIBLE;
}

bool SessionItem::isEnabled() const
{
    return flags() & SessionModel::ENABLED;
}

bool SessionItem::isEditable() const
{
    return flags() & SessionModel::EDITABLE;
}

AttLimits SessionItem::limits() const
{
    return data(SessionModel::LimitsRole).value<AttLimits>();
}

void SessionItem::setLimits(const AttLimits &value)
{
    this->setData(SessionModel::LimitsRole, QVariant::fromValue<AttLimits>(value));
}

int SessionItem::decimals() const
{
    return data(SessionModel::DecimalRole).toInt();
}

void SessionItem::setDecimals(int n)
{
    setData(SessionModel::DecimalRole, n);
}

QString SessionItem::toolTip() const
{
    return data(Qt::ToolTipRole).toString();
}

void SessionItem::setToolTip(const QString &tooltip)
{
    setData(Qt::ToolTipRole, tooltip);
}

QString SessionItem::defaultTag() const
{
    return data(SessionModel::DefaultTagRole).toString();
}

void SessionItem::setDefaultTag(const QString &tag)
{
    setData(SessionModel::DefaultTagRole, tag);
}

ModelMapper *SessionItem::mapper()
{
    if (!m_mapper) {
        m_mapper = std::unique_ptr<ModelMapper>(new ModelMapper);
        m_mapper->setItem(this);
    }
    return m_mapper.get();
}

void SessionItem::setDisplayName(const QString &display_name)
{
    setData(SessionModel::DisplayNameRole, display_name);
}

int SessionItem::getCopyNumberOfChild(const SessionItem *p_item) const
{
    if (!p_item) return -1;
    int result = -1;
    int count = 0;
    QString model_type = p_item->modelType();
    // check child items:
    if (hasChildren()) {
        for (auto p_child_item : m_children) {
            QString child_type = p_child_item->modelType();
            if (p_child_item == p_item) {
                result = count;
            }
            if (child_type == model_type && !p_child_item->isTag(P_NAME)) {
                ++count;
            }
        }
    }
    if (count > 1) return result;
    return -1;
}
