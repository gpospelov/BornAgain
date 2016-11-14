// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItem.cpp
//! @brief     Implements class SessionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIHelpers.h"
#include "GroupItem.h"
#include "GroupPropertyRegistry.h"
#include "ItemFactory.h"
#include "SessionModel.h"
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

//! Constructs new item with given model type. The type must be defined.

SessionItem::SessionItem(const QString &modelType)
    : m_parent(nullptr)
    , m_model(nullptr)
{
    Q_ASSERT(!modelType.isEmpty());

    setData(SessionModel::ModelTypeRole, modelType);
    setDisplayName(modelType);
    setDecimals(3);
    setLimits(RealLimits::lowerLimited(0.0));
}

//! Destructor deletes all its children and request parent to delete this item.

SessionItem::~SessionItem()
{
    if(m_mapper)
        m_mapper->callOnItemDestroy();

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

//! internal
void SessionItem::childDeleted(SessionItem *child)
{
    int index = rowOfChild(child);
    Q_ASSERT(index != -1);
    m_children.replace(index, nullptr);
}

//! internal
void SessionItem::setParentAndModel(SessionItem *parent, SessionModel *model)
{
    setModel(model);
    m_parent = parent;
}

//! internal
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



//! Returns model of this item.

SessionModel *SessionItem::model() const
{
    return m_model;
}

//! Returns parent of this item.

SessionItem *SessionItem::parent() const
{
    return m_parent;
}

//! Returns model index of this item.

 QModelIndex SessionItem::index() const
{
    if (m_model) {
        return m_model->indexOfItem(const_cast<SessionItem*>(this));
    }
    return QModelIndex();
}

//! Returns true when item has children.

bool SessionItem::hasChildren() const
{
    return !m_children.isEmpty();
}

//! Returns total number of children.

int SessionItem::rowCount() const
{
    return m_children.count();
}

//! Returns vector of all children.

QVector<SessionItem *> SessionItem::childItems() const
{
    return m_children;
}


//! Returns the child at the given row.

SessionItem *SessionItem::childAt(int row) const
{
    return m_children.value(row, nullptr);
}

//! Returns row index of given child.

int SessionItem::rowOfChild(SessionItem *child) const
{
    return m_children.indexOf(child);
}


//! Returns the index of this item within its parent, returns -1 when no parent is set.

int SessionItem::parentRow() const
{
    if (m_parent)
        return m_parent->rowOfChild(const_cast<SessionItem*>(this));
    return -1;
}

//! Returns the first child with the given name.
SessionItem *SessionItem::getChildByName(const QString &name) const
{
    for (auto child : m_children) {
        if (child->itemName() == name) return child;
    }
    return nullptr;
}

//! Returns the first child of the given type.

SessionItem *SessionItem::getChildOfType(const QString &type) const
{
    for (auto child : m_children) {
        if (child->modelType() == type) return child;
    }
    return nullptr;
}

//! Returns a vector of all children of the given type.

QVector<SessionItem *> SessionItem::getChildrenOfType(const QString &model_type) const
{
    QVector<SessionItem *> result;
    for (auto child : m_children) {
        if (child->modelType() == model_type)
            result.append(child);
    }
    return result;
}

//! Removes row from item and returns the item.

SessionItem *SessionItem::takeRow(int row)
{
    SessionItem *item = childAt(row);
    QString tag = tagFromItem(item);
    auto items = getItems(tag);
    return takeItem(items.indexOf(item), tag);
}

//! Add new tag to this item with given name, min, max and types.
//! max = -1 -> unlimited, modelTypes empty -> all types allowed

bool SessionItem::registerTag(const QString &name, int min, int max, QStringList modelTypes)
{
    if (min < 0 || (min > max && max >= 0))
        return false;
    if (name.isEmpty() || getTagInfo(name).isValid())
        return false;
    m_tags.append(SessionTagInfo(name, min, max, modelTypes));
    return true;
}

//! Returns true if tag is available.

bool SessionItem::isTag(const QString &name) const
{
    return getTagInfo(name).isValid();
}

//! Returns the tag name of given item when existing.

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

//! Returns corresponding tag info.

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

//! Returns true if model type can be added to default tag.

bool SessionItem::acceptsAsDefaultItem(const QString &item_name) const
{
    return getTagInfo(defaultTag()).modelTypes.contains(item_name);
}

//! Returns vector of acceptable default tag types.

QVector<QString> SessionItem::acceptableDefaultItemTypes() const
{
    return getTagInfo(defaultTag()).modelTypes.toVector();
}

//! internal
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

//! Returns item in given row of given tag.

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

//! Returns vector of all items of given tag.

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

//! Insert item into given tag into given row.

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
            m_model->beginInsertRows(this->index(),index, index);
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

//! Remove item from given row from given tag.

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

//! Add new property item and register new tag.

SessionItem *SessionItem::addProperty(const QString &name, const QVariant &variant)
{
    if (isTag(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing property " + name);

    const QString property_type = Constants::PropertyType;
    SessionItem *property = ItemFactory::createItem(property_type);
    property->setDisplayName(name);
    registerTag(name, 1, 1, QStringList() << property_type);
    if(!insertItem(0, property, name)) {
        throw GUIHelpers::Error("SessionItem::addProperty -> Error. Can't insert item");
    }
    property->setValue(variant);
    return property;
}

//! Directly access value of item under given tag.

QVariant SessionItem::getItemValue(const QString &tag) const
{
    if (!isTag(tag))
        throw GUIHelpers::Error(
            "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property '" + tag
            + "', item '" + modelType() + "'");

    return getItem(tag)->value();
}

//! Directly set value of item under given tag.

void SessionItem::setItemValue(const QString &tag, const QVariant &variant)
{
    // check if variant of previous property coincides with new one
    if (!isTag(tag))
        throw GUIHelpers::Error("Property not existing!");

     getItem(tag)->setValue(variant);
}

//! Creates new group item and register new tag, returns GroupItem.

SessionItem *SessionItem::addGroupProperty(const QString &groupName, const QString &groupType)
{
    SessionItem *result(0);

    if(GroupPropertyRegistry::isValidGroup(groupType)) {
        // create group item
        GroupProperty_t group_property
            = GroupPropertyRegistry::createGroupProperty(groupName, groupType);
        GroupItem *groupItem = dynamic_cast<GroupItem *>(
                    ItemFactory::createItem(Constants::GroupItemType));
        Q_ASSERT(groupItem);
        groupItem->setGroup(group_property);
        registerTag(groupName, 1, 1, QStringList() << Constants::GroupItemType);
        result = groupItem;
    }

    else {
        // create single item
        registerTag(groupName, 1, 1, QStringList() << groupType);
        result = ItemFactory::createItem(groupType);
    }

    Q_ASSERT(result);
    result->setDisplayName(groupName);
    if(!insertItem(0, result, groupName)) {
        throw GUIHelpers::Error("SessionItem::addGroupProperty -> Error. Can't insert group item");
    }

    return result;
}

//! Access subitem of group item. If not existing, new item will be created by group property.

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

//! Set the current type of group item.

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

//! Returns corresponding variant under given role, invalid variant when role is not present.

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

//! Set variant to role, create role if not present yet.

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

//! Returns vector of all present roles.

QVector<int> SessionItem::getRoles() const
{
    QVector<int> result;
    QVector<SessionItemData>::const_iterator it;
    for (it = m_values.constBegin(); it != m_values.constEnd(); ++it) {
        result.append(it->role);
    }
    return result;
}

//! Notify model about data changes.

void SessionItem::emitDataChanged(int role)
{
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        m_model->dataChanged(index, index.sibling(index.row(), 1), QVector<int>() << role);
    }
}

//! internal
int SessionItem::flags() const
{
    QVariant flags = data(SessionModel::FlagRole);
    if (!flags.isValid())
        return SessionModel::VISIBLE | SessionModel::EDITABLE | SessionModel::ENABLED;

    return flags.toInt();
}

//! internal
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

//! Get model type

QString SessionItem::modelType() const
{
    return data(SessionModel::ModelTypeRole).toString();
}

//! Get value

QVariant SessionItem::value() const
{
    return data(Qt::DisplayRole);
}

//! Set value, ensure that variant types match.

bool SessionItem::setValue(QVariant value)
{
    QVariant previous_variant = this->value();
    if (previous_variant.isValid() && GUIHelpers::getVariantType(previous_variant)
            != GUIHelpers::getVariantType(value)) {
        qDebug() << "ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new "
                    "variant does not coincide.";
        qDebug() << "New variant" << value << ", previous " << previous_variant;
        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Type of "
                                "previous and new variant does not coincide.");
    }
    return setData(Qt::DisplayRole, value);
}

//! Get default tag

QString SessionItem::defaultTag() const
{
    return data(SessionModel::DefaultTagRole).toString();
}

//! Set default tag

void SessionItem::setDefaultTag(const QString &tag)
{
    setData(SessionModel::DefaultTagRole, tag);
}

//! Get display name of item, append index if ambigue.

QString SessionItem::displayName() const
{
    QString result = data(SessionModel::DisplayNameRole).toString();

    if(modelType() == Constants::PropertyType || modelType() == Constants::GroupItemType ||
       modelType() == Constants::ParameterType || modelType() == Constants::ParameterLabelType)
        return result;

    if(m_parent) {
        QString tag = m_parent->tagFromItem(this);
        SessionTagInfo info = m_parent->getTagInfo(tag);
        // if only one child of this type is allowed, return name without change
        if (info.min == 1 && info.max == 1 && info.childCount == 1) {
            return result;
        }

        int index = m_parent->getCopyNumberOfChild(this);
        if(index >= 0) {
            return result + QString::number(index);
        }

    }

    return result;
}

//! Set display name

void SessionItem::setDisplayName(const QString &display_name)
{
    setData(SessionModel::DisplayNameRole, display_name);
}

//! internal
int SessionItem::getCopyNumberOfChild(const SessionItem *item) const
{
    if (!item) return -1;
    int result = -1;
    int count = 0;
    QString model_type = item->modelType();
    // check child items:
    for (auto p_child_item : m_children) {
        QString child_type = p_child_item->modelType();
        if (p_child_item == item) {
            result = count;
        }
        if (child_type == model_type && !p_child_item->isTag(P_NAME)) {
            ++count;
        }
    }
    if (count > 1) return result;
    return -1;
}

//! Get item name, return display name if no name is set.

QString SessionItem::itemName() const
{
    if (isTag(P_NAME)) {
        return getItemValue(P_NAME).toString();
    } else {
        return displayName();
    }
}

//! Set item name, add property if necessary.

void SessionItem::setItemName(const QString &name)
{
    if (isTag(P_NAME)) {
        setItemValue(P_NAME, name);
    } else {
        addProperty(P_NAME, name);
        // when name changes, than parent should be notified about it
        mapper()->setOnPropertyChange(
                    [this] (const QString &name)
        {
            if (name == P_NAME)
                emitDataChanged();
        });
    }
}


// access flags

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


// more roles

RealLimits SessionItem::limits() const
{
    return data(SessionModel::LimitsRole).value<RealLimits>();
}

SessionItem& SessionItem::setLimits(const RealLimits &value)
{
    this->setData(SessionModel::LimitsRole, QVariant::fromValue<RealLimits>(value));
    return *this;
}

int SessionItem::decimals() const
{
    return data(SessionModel::DecimalRole).toInt();
}

SessionItem& SessionItem::setDecimals(int n)
{
    setData(SessionModel::DecimalRole, n);
    return *this;
}

QString SessionItem::toolTip() const
{
    return data(Qt::ToolTipRole).toString();
}

SessionItem& SessionItem::setToolTip(const QString &tooltip)
{
    setData(Qt::ToolTipRole, tooltip);
    return *this;
}

//! Returns label of item shown in property editor.

QString SessionItem::itemLabel() const
{
    return QString("");
}

//! Returns the current model mapper of this item. Creates new one if necessary.

ModelMapper *SessionItem::mapper()
{
    if (!m_mapper) {
        m_mapper = std::unique_ptr<ModelMapper>(new ModelMapper);
        m_mapper->setItem(this);
    }
    return m_mapper.get();
}
