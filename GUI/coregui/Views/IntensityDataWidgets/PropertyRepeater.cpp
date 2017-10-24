// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/PropertyRepeater.cpp
//! @brief     Implements class PropertyRepeater
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PropertyRepeater.h"
#include "IntensityDataItem.h"
#include <QDebug>

PropertyRepeater::PropertyRepeater(QObject* parent)
    : QObject(parent)
    , m_block_repeater(false)
{

}

void PropertyRepeater::addItem(SessionItem* sessionItem, const QStringList& activeProperties)
{
    if (!sessionItem || m_dataItems.contains(sessionItem))
        return;


    sessionItem->mapper()->setOnItemDestroy([this](SessionItem* item)
    {
        m_dataItems.removeAll(item);
    }, this);

    sessionItem->mapper()->setOnPropertyChange(
        [this](SessionItem* item, const QString& name) { onPropertyChanged(item, name); }, this);

    sessionItem->mapper()->setOnChildPropertyChange(
        [this](SessionItem* item, const QString& name) {
            setOnChildPropertyChange(item, name);
        }, this);


    m_dataItems.push_back(sessionItem);
    if (!activeProperties.isEmpty())
        m_itemProperties[sessionItem] = activeProperties;
}

void PropertyRepeater::clear()
{
    for (auto item : m_dataItems)
        item->mapper()->unsubscribe(this);

    m_dataItems.clear();
    m_itemProperties.clear();
}

void PropertyRepeater::setActive(bool isActive)
{
    m_block_repeater = !isActive;
}

void PropertyRepeater::onPropertyChanged(SessionItem* item, const QString& propertyName)
{
    if (m_block_repeater)
        return;

    m_block_repeater = true;

    if (isPropertyBroadcastAllowed(item, propertyName)) {
        QVariant value = item->getItemValue(propertyName);
        qDebug() << item->modelType() << propertyName << value;

        for (auto target : targetItems(item))
            target->setItemValue(propertyName, value);

    }

    m_block_repeater = false;

}


void PropertyRepeater::setOnChildPropertyChange(SessionItem* item, const QString& propertyName)
{
    if (m_block_repeater)
        return;

    m_block_repeater = true;

    SessionItem* sourceItem = item->parent();

    if (isPropertyBroadcastAllowed(sourceItem, propertyName)) {
        QString tag = sourceItem->tagFromItem(item);
        QVariant value = item->getItemValue(propertyName);

        qDebug() << "PropertyRepeater: " << item << item->modelType() << item->itemName()
                 << " parent:" << item->parent() << item->parent()->modelType() << item->parent()->itemName()
                 << " propertyName:" << propertyName;
        qDebug() << "tag:" << tag << m_dataItems.size();

        for (auto target : targetItems(sourceItem))
            target->getItem(tag)->setItemValue(propertyName, value);
    }

    m_block_repeater = false;
}

//! Returns list of target items to update their properties.

QVector<SessionItem*> PropertyRepeater::targetItems(SessionItem* sourceItem)
{
    QVector<SessionItem*> result = m_dataItems;
    result.removeAll(sourceItem);
    return result;
}

//! Returns true if given item is allowed to send updates about property with given name.

bool PropertyRepeater::isPropertyBroadcastAllowed(SessionItem* item, const QString& propertyName)
{
    auto it = m_itemProperties.find(item);
    if (it == m_itemProperties.end())
        return true; // no special wishes, broadcast is allowed

    return it.value().contains(propertyName) ? true : false;
}
