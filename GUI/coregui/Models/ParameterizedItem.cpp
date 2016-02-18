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
#include "ItemFactory.h"
#include "GUIHelpers.h"
//#include "PropertyVariantManager.h"

#include <sstream>

ParameterizedItem::ParameterizedItem(QString model_type)
    : m_model_type(QString())
    , m_data(QVector<QVariant>(SessionModel::MAX_COLUMNS))
    , mp_parent(0)
    , m_model(0)
    , m_port(PortInfo::DEFAULT)
{
    // provide useful name in the case of empty constructor
    m_model_type = model_type.isEmpty() ? "ParameterizedItem" : model_type;
    setDisplayName(m_model_type);

    // TODO port should not not be accessible as property, leave it for compatibility now
    registerProperty(OBSOLETE_P_PORT, -1);//.setHidden();
}

ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
}

QVariant ParameterizedItem::data(int column) const
{
    if (column >= 0 && column < m_data.size()) {
        return m_data[column];
    }
    return QVariant();
}

bool ParameterizedItem::setData(int column, const QVariant &data)
{
    if (column < 0 || column >= m_data.size())
        return false;

    m_data[column] = data;

    // inform model about the change
    if (m_model) {
        QModelIndex index = m_model->indexOfItem(this);
        m_model->dataChanged(index, index, QVector<int>() << Qt::DisplayRole << Qt::EditRole);
    }
    return true;
}

QVariant ParameterizedItem::value() const
{
    return data(SessionModel::ITEM_VALUE);
}

bool ParameterizedItem::setValue(QVariant value)
{
    return setData(SessionModel::ITEM_VALUE, value);
}

QString ParameterizedItem::name() const
{
    if (data(SessionModel::ITEM_NAME).isValid())
        return data(SessionModel::ITEM_NAME).toString();

    return displayName();
}

void ParameterizedItem::setName(const QString &name)
{
    setData(SessionModel::ITEM_NAME, name);
}

QString ParameterizedItem::displayName() const
{
    if (mp_parent) {
        int index = mp_parent->getCopyNumberOfChild(this);
        if (index >= 0) {
            return m_display_name + QString::number(index + 1);
        }
    }
    return m_display_name;
}

QString ParameterizedItem::modelType() const
{
    return m_model_type;
}

QString ParameterizedItem::label() const
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

ParameterizedItem::PortInfo::EPorts ParameterizedItem::port() const
{
    return m_port;
}

void ParameterizedItem::setPort(ParameterizedItem::PortInfo::EPorts nport)
{
    setRegisteredProperty(OBSOLETE_P_PORT, nport);
}

PropertyAttribute ParameterizedItem::attribute() const
{
    return data(SessionModel::ITEM_ATTR).value<PropertyAttribute>();
}

void ParameterizedItem::setAttribute(const PropertyAttribute &attribute)
{
    setData(SessionModel::ITEM_ATTR, QVariant::fromValue<PropertyAttribute>(attribute));
}

ParameterizedItem *ParameterizedItem::parent() const
{
    return mp_parent;
}

int ParameterizedItem::rowCount() const
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

bool ParameterizedItem::hasChildren() const
{
    return !m_children.isEmpty();
}

QList<ParameterizedItem *> ParameterizedItem::getChildren() const
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

ParameterizedItem *ParameterizedItem::getChildByDisplayName(const QString &name) const
{
    for (auto child : m_children) {
        if (child->displayName() == name) return child;
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

void ParameterizedItem::insertChild(int row, ParameterizedItem *item)
{
    if (row == -1)
        row = m_children.size();

    item->mp_parent = this;
    item->setModel(m_model);

    if (m_model)
        m_model->beginInsertRows(m_model->indexOfItem(item), row, row);

    m_children.insert(row, item);

    if (m_model)
        m_model->endInsertRows();

    // OBSOLETE watch for changes on the model
//    notifySiblings();
//    onChildPropertyChange(item);
}

ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    ParameterizedItem *item = m_children.takeAt(row);
    item->mp_parent = nullptr;
    item->setModel(nullptr);
    return item;

    // OBSOLETE watch for changes on the model
//    notifySiblings();
//    onChildPropertyChange(item);
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

QList<QString> ParameterizedItem::acceptableChildItems() const
{
    return m_valid_children;
}

ParameterizedItem *ParameterizedItem::registerProperty(const QString &name, const QVariant &variant,
                                         const PropertyAttribute &attribute)
{
    if (m_properties.contains(name))
        throw GUIHelpers::Error(
            "ParameterizedItem::registerProperty() -> Error. Already existing property " + name);

    // OBSOLETE here for compatibility reasons
    if (name == ParameterizedItem::OBSOLETE_P_PORT) {
        m_port = ParameterizedItem::PortInfo::EPorts(variant.toInt());
        return nullptr;
    } else if (name == ParameterizedItem::OBSOLETE_P_NAME) {
        setName(variant.toString());
        return nullptr;
    }
    // END of obsolete

    ParameterizedItem *property = ItemFactory::createItem(Constants::PropertyType);
    property->setName(name);
    property->setValue(variant);
    property->setAttribute(attribute);
    insertChild(-1, property);
    m_properties.insert(name, property);

    return property;
}


const QString ParameterizedItem::OBSOLETE_P_NAME = "Name";
const QString ParameterizedItem::OBSOLETE_P_PORT = "Port";





ParameterizedItem *ParameterizedItem::getParameterByName(const QString &name) const // NEW
{
    for (int i = 0; i < this->rowCount(); i++) {
        if (m_children[i]->m_model_type == "Parameter") {
            if (ParameterizedItem *child = m_children[i]) {
                if (child->data(0) == name)
                    return child;
            }
        }
    }
    return nullptr;
}

//// emits signal on property change - not need any more
//bool ParameterizedItem::event(QEvent *e)
//{
//    if (e->type() == QEvent::DynamicPropertyChange) {
//        QDynamicPropertyChangeEvent *propertyEvent = dynamic_cast<QDynamicPropertyChangeEvent *>(e);
//        Q_ASSERT(e);
//        QByteArray byte_array = propertyEvent->propertyName();
//        QString name(byte_array.constData());
//        onPropertyChange(name);
//    }
//    return QObject::event(e);
//}

QMap<QString, ParameterizedItem *> ParameterizedItem::getSubItems() const
{
    return m_sub_items;
}

void ParameterizedItem::addSubItem(QString name, ParameterizedItem *item)
{
//    // if (!item) return;
//    Q_ASSERT(item);
//    qDebug() << "ParameterizedItem::addPropertyItem()" << name;

    if (m_sub_items.contains(name)) {
//        qDebug() << "       ParameterizedItem::addPropertyItem() -> item is already there" << name
//                 << "replacing with " << item->modelType();
//        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_sub_items[name] = item;
    item->mp_parent = this;
    insertChild(-1, item); // NEW
    onSubItemChanged(name);
    onChildPropertyChange(item);
//    qDebug() << "ParameterizedItem::addPropertyItem() -> about to leave" << name;
}

bool ParameterizedItem::isRegisteredProperty(const QString &name) const
{
    return m_registered_properties.contains(name);
}

ParameterizedItem *ParameterizedItem::registerGroupProperty(const QString &group_name,
                                                            const Constants::ModelType &group_model)
{
//    qDebug() << "ParameterizedItem::registerGroupProperty() ->"
//             << "this->modelType" << modelType() << "group_name" << group_name << " group_model"
//             << group_model;

    GroupProperty_t group_property
        = GroupPropertyRegistry::createGroupProperty(group_name, group_model);
    QVariant variant;
    variant.setValue(group_property);
    registerProperty(group_name, variant);
    group_property->setParent(this);
    ParameterizedItem *p_result = m_sub_items[group_name];
    if (group_property->type() == GroupProperty::FIXED) {
        p_result->setDisplayName(group_name);
    }
    return p_result;
}

ParameterizedItem *ParameterizedItem::setGroupProperty(const QString &name, const QString &value)
{
//    qDebug() << "ParameterizedItem::setGroupProperty()" << name << value;
    GroupProperty_t group_property = getRegisteredProperty(name).value<GroupProperty_t>();
    group_property->setCurrentType(value);
    return m_sub_items[name];
}



void ParameterizedItem::setRegisteredProperty(const QString &name, const QVariant &variant)
{
//    // check if variant of previous property coincides with new one
//    QVariant previous_variant = getRegisteredProperty(name);
//    if (GUIHelpers::getVariantType(previous_variant) != GUIHelpers::getVariantType(variant)) {
//        qDebug() << "ParameterizedItem::setRegisteredProperty() -> Error. Type of previous and new "
//                    "variant does not coincide.";
//        qDebug() << "New variant" << variant << ", previous " << previous_variant;
//        throw GUIHelpers::Error("ParameterizedItem::setRegisteredProperty() -> Error. Type of "
//                                "previous and new variant does not coincide.");
//    }

//    setProperty(name.toUtf8().constData(), variant);
    if (name == ParameterizedItem::OBSOLETE_P_NAME) {
        if (m_model) {
            m_model->setData(m_model->indexOfItem(this), variant, Qt::DisplayRole);
        } else {
            this->setData(0, variant);
        }
        onPropertyChange(name);
    }
    if (ParameterizedItem *para = getParameterByName(name)) {
        if (0 && m_model) {
            m_model->setData(m_model->indexOfItem(para), variant, Qt::UserRole);
        } else {
            para->setData(1, variant);
        }
        onPropertyChange(name);
    }
}

QVariant ParameterizedItem::getRegisteredProperty(const QString &name) const
{
    if (!m_registered_properties.contains(name))
//        throw GUIHelpers::Error(
//            "ParameterizedItem::getRegisteredProperty() -> Error. Unknown property '" + name
//            + "', item '" + modelType() + "'");
        throw -1; // NEW

    // for debugging purpose
//    PropertyAttribute attribute = getPropertyAttribute(name);
//    if(attribute.getAppearance() == PropertyAttribute::DISABLED) {
//        throw GUIHelpers::Error("ParameterizedItem::getRegisteredProperty() -> Logic Error? "
//            "You are trying to get DISABLED property with name '" +name +"', model " + modelType());
//    }

//    return property(name.toUtf8().constData());
    if (name == ParameterizedItem::OBSOLETE_P_PORT) // NEW
        return m_port; // NEW
    if (name == ParameterizedItem::OBSOLETE_P_NAME) // NEW
        return data(0);
    if (ParameterizedItem *parameter = getParameterByName(name)) { // NEW
        QVariant data = parameter->data(1); // NEW
        return data;
    }
    return QVariant(); // NEW
}

void ParameterizedItem::removeRegisteredProperty(const QString &name)
{
    if(isRegisteredProperty(name)) {
//        qDebug() << "ParameterizedItem::removeRegisteredProperty()" << name;
        m_registered_properties.removeOne(name);
        m_property_attribute.remove(name);
        if (ParameterizedItem *para = getParameterByName(name)) {
            QModelIndex index = m_model->indexOfItem(para);
            m_model->removeRows(index.row(), 1, index.parent());
        }
//        setProperty(name.toUtf8().constData(), QVariant());

        if (m_sub_items.contains(name)) {
//            qDebug()
//                << "       ParameterizedItem::removeRegisteredProperty() -> Removing property iteme";
//            delete m_sub_items[name];
            m_sub_items.remove(name);
        }
    }
}


const PropertyAttribute &ParameterizedItem::getPropertyAttribute(const QString &name) const
{
    QMap<QString, PropertyAttribute>::const_iterator it = m_property_attribute.find(name);
    if(it == m_property_attribute.end()) {
//        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> Error. "
//                                "Unknown property attribute " + name);
        throw -1; // NEW
    }
    return it.value();
}

PropertyAttribute &ParameterizedItem::getPropertyAttribute(const QString &name)
{
    QMap<QString, PropertyAttribute>::iterator it = m_property_attribute.find(name);
    if(it == m_property_attribute.end()) {
//        throw GUIHelpers::Error("ParameterizedItem::getPropertyAttribute() -> Error. "
//                                "Unknown property attribute " + name);
        throw -1; // NEW

    }
    return it.value();
}

void ParameterizedItem::setPropertyAttribute(const QString &name,
                                             const PropertyAttribute &attribute)
{
    if (!m_registered_properties.contains(name))
//        throw GUIHelpers::Error(
//            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property " + name);
        throw -1; // NEW

    if (!m_property_attribute.contains(name))
//        throw GUIHelpers::Error(
//            "ParameterizedItem::setPropertyAttribute() -> Error. Unknown property attribute "
//            + name);
        throw -1; // NEW

    m_property_attribute[name] = attribute;
}


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

//// returns child which should be removed by the model due to overpopulation of children of given
//// type
ParameterizedItem *ParameterizedItem::getCandidateForRemoval(ParameterizedItem *new_comer)
{
    if (!new_comer)
        return 0;

    QMap<int, QVector<ParameterizedItem *> > nport_to_nitems;
    foreach (ParameterizedItem *child, m_children) {
        int nport = child->getRegisteredProperty(OBSOLETE_P_PORT).toInt();
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

QStringList ParameterizedItem::getParameterTreeList(QString prefix) const
{
    QStringList result;
    // add child parameters:
    if (hasChildren()) {
        for (auto p_child : m_children) {
            QString child_name = p_child->displayName();
            QString child_prefix = prefix + child_name + QString("/");
            result << p_child->getParameterTreeList(child_prefix);
        }
    }
    // add subitem parameters:
    if (m_sub_items.size() > 0) {
        for (QMap<QString, ParameterizedItem *>::const_iterator it = m_sub_items.begin();
             it != m_sub_items.end(); ++it) {
            const PropertyAttribute &prop_attribute = getPropertyAttribute(it.key());
            if (prop_attribute.isHidden() || prop_attribute.isDisabled()) continue;
            ParameterizedItem *p_subitem = it.value();
            QString subitem_name = p_subitem->displayName();
            QString subitem_prefix = prefix + subitem_name + QString("/");
            result << p_subitem->getParameterTreeList(subitem_prefix);
        }
    }
    // add own parameters:
    result << getParameterList(prefix);
    return result;
}

double ParameterizedItem::getParameterValue(const QString &name) const
{
    QString head = getFirstField(name);
    auto p_child = getChildByDisplayName(head);
    if (p_child) {
        return p_child->getParameterValue(stripFirstField(name));
    }
    if (isRegisteredProperty(head)) {
        return getRegisteredProperty(head).toDouble();
    } else {
        return 0.0;
    }
}

std::string ParameterizedItem::translateParameterName(const QString &par_name) const
{
    std::ostringstream result;
    auto list = splitParameterName(par_name);
    if (list.isEmpty()) {
        return std::string();
    }
    auto first_field = list[0];
    result << "/" << translateSingleName(first_field);
    if (list.size() > 1) {
        auto remainder = list[1];
        auto p_child = getChildByDisplayName(first_field);
        if (p_child) {
            result << p_child->translateParameterName(remainder);
        }
    }
    return result.str();
}

////! called when new SubItem appeared
void ParameterizedItem::onSubItemChanged(const QString &propertyName)
{
    connect(m_sub_items[propertyName], SIGNAL(propertyChanged(QString)), this,
            SLOT(processSubItemPropertyChanged(QString)), Qt::UniqueConnection);
    emit subItemChanged(propertyName);
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
    ParameterizedItem *propertyItem = qobject_cast<ParameterizedItem *>(sender());
    for (QMap<QString, ParameterizedItem *>::iterator it = m_sub_items.begin();
         it != m_sub_items.end(); ++it) {
        if (it.value() == propertyItem) {
            GroupProperty_t group_property
                = getRegisteredProperty(it.key()).value<GroupProperty_t>();
            group_property->setCurrentLabel(propertyItem->label());
            onSubItemPropertyChanged(it.key(), propertyName);
            return;
        }
    }
    throw -1; // NEW
//    throw GUIHelpers::Error("ParameterizedItem::onSubItemPropertyChanged() ->"
//                            " Error. No such propertyItem found");
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
    m_children.swap(first, second);
}

QStringList ParameterizedItem::splitParameterName(const QString &par_name) const
{
    QStringList result;
    for (auto& translator : m_special_translators) {
        result = translator->split(par_name);
        if (result.size() > 0) {
            return result;
        }
    }
    result << getFirstField(par_name);
    QString remainder = stripFirstField(par_name);
    if (!remainder.isEmpty()) {
        result << remainder;
    }
    return result;
}

QString ParameterizedItem::getFirstField(const QString &par_name) const
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()==0) return QString();
    return par_list.front();
}

QString ParameterizedItem::stripFirstField(const QString &par_name) const
{
    QStringList par_list = par_name.split("/");
    if (par_list.size()<2) return QString();
    par_list.removeFirst();
    return par_list.join("/");
}

std::string ParameterizedItem::translateSingleName(const QString &name) const
{
    for (auto& translator : m_special_translators) {
        auto result = translator->translate(name);
        if (!result.empty()) {
            return result;
        }
    }
    return name.toStdString();
}

void ParameterizedItem::addParameterTranslator(const IParameterTranslator &translator)
{
    m_special_translators.emplace_back(translator.clone());
}

void ParameterizedItem::notifySiblings()
{
    for (auto child : m_children) {
        child->onSiblingsChanged();
    }
}

QStringList ParameterizedItem::getParameterList(QString prefix) const
{
    QStringList result;
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        const PropertyAttribute &prop_attribute = getPropertyAttribute(prop_name);
        if (prop_attribute.isHidden() || prop_attribute.isDisabled() ) continue;
        QVariant variant = property(prop_name.toUtf8().constData());
        int type = variant.type(); // NEW
        if (type == QVariant::UserType) { // NEW
            type = variant.userType(); // NEW
        }
        if (type == QVariant::Double) {
            result << prefix + prop_name;
        }
    }
    return result;
}

int ParameterizedItem::getCopyNumberOfChild(const ParameterizedItem *p_item) const
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
            if (child_type == model_type) {
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
