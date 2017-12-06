// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GroupItem.cpp
//! @brief     Implements class GroupItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GroupItem.h"
#include "GUIHelpers.h"
#include "ComboProperty.h"
#include <QDebug>
#include "GUIHelpers.h"

namespace {
QVariant createCombo(ObsoleteGroupProperty_t groupProperty)
{
    ComboProperty result;
    result.setValues(groupProperty->itemLabels());
    result.setCurrentIndex(groupProperty->currentIndex());
    return result.variant();
}

}

const QString GroupItem::T_ITEMS = "Item tag";

GroupItem::GroupItem() : SessionItem(Constants::GroupItemType)
{
    registerTag(T_ITEMS);
    setDefaultTag(T_ITEMS);

    mapper()->setOnValueChange([this]() { onValueChange(); });
}

void GroupItem::setGroupInfo(const GroupInfo& groupInfo)
{
    if (m_groupProperty)
        throw GUIHelpers::Error("GroupItem::setGroup() -> Error. Attempt to set group twice.");

    ObsoleteGroupProperty_t prop(new GroupProperty);
    prop->setGroupInfo(groupInfo);

    prop->setGroupItem(this);
    m_groupProperty = prop;

    updateValue();

//    setValue(QVariant::fromValue(groupProperty));
}

SessionItem* GroupItem::currentItem() const
{
//    return value().isValid() ? groupProperty()->currentItem() : nullptr;
    return groupProperty() ? groupProperty()->currentItem() : nullptr;
}

QString GroupItem::currentType() const
{
    return groupProperty()->currentType();
}

#include <QDebug>
SessionItem* GroupItem::setCurrentType(const QString& modelType)
{
    qDebug() << "GroupItem::setCurrentType -> current"
             << groupProperty()->currentType() << groupProperty()->currentIndex();
    qDebug() << "   setting" << modelType;
    groupProperty()->setCurrentType(modelType);
    qDebug() << "GroupItem::setCurrentType -> current"
             << groupProperty()->currentType() << groupProperty()->currentIndex();

    updateValue();

    return currentItem();
}

QStringList GroupItem::translateList(const QStringList& list) const
{
    // we do not add here the name of itself
    return list;
}

ObsoleteGroupProperty_t GroupItem::groupProperty() const
{
    return m_groupProperty;
//    return value().value<GroupProperty_t>();
}

SessionItem* GroupItem::getItemOfType(const QString& type)
{
    SessionItem* result = groupProperty()->getItemOfType(type);

//    setValue(createCombo(groupProperty()));

    return result;
}

void GroupItem::onValueChange()
{
    if (!value().canConvert<ComboProperty>())
        throw GUIHelpers::Error("GroupItem::onValueChange() -> Error. Wrong property type");

    qDebug() << "GroupItem::onValueChange()";

    ComboProperty property = value().value<ComboProperty>();
    if (property.currentIndex() != m_groupProperty->currentIndex()) {
        qDebug() << "GroupItem::onValueChange() -> setting index" << property.currentIndex();
        m_groupProperty->setCurrentIndex(property.currentIndex());
        // because of the delay between ComboProperty change and the change in GroupItem here,
        // we have to emit signals once again to inform other views (i.e. views other than the view
        // were property was changed
        emitDataChanged(Qt::DisplayRole | Qt::EditRole);
    }
}

void GroupItem::updateValue()
{
    setValue(createCombo(groupProperty()));
}

