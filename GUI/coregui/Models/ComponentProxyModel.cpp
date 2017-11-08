// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComponentProxyModel.cpp
//! @brief     Implements class ComponentProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentProxyModel.h"
#include "SessionModel.h"
#include "ModelUtils.h"
#include <functional>
#include <QDebug>

ComponentProxyModel::ComponentProxyModel(QObject* parent)
    : QAbstractProxyModel(parent)
    , m_model(nullptr)
{
}

void ComponentProxyModel::setSessionModel(SessionModel* model)
{
    beginResetModel();

    QAbstractProxyModel::setSourceModel(model);

    endResetModel();

    m_model = model;
    buildModelMap();
}

QModelIndex ComponentProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    if (!proxyIndex.isValid())
        return QModelIndex();

    return m_sourceToProxy.key(proxyIndex);
}

QModelIndex ComponentProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
    if (!sourceIndex.isValid())
        return QModelIndex();

    return m_sourceToProxy.value(sourceIndex);
}

QModelIndex ComponentProxyModel::index(int row, int column, const QModelIndex& parent) const
{
    QModelIndex sourceParent;
    if (parent.isValid())
        sourceParent = mapToSource(parent);

    QMapIterator<QPersistentModelIndex, QPersistentModelIndex> it(m_proxySourceParent);
    while (it.hasNext()) {
        it.next();
        if (it.value() == sourceParent && it.key().row() == row &&
            it.key().column() == column)
            return it.key();
    }
    return QModelIndex();
}

QModelIndex ComponentProxyModel::parent(const QModelIndex& child) const
{
    QModelIndex sourceParent = m_proxySourceParent.value(child);
    if (sourceParent.isValid())
        return mapFromSource(sourceParent);

    return QModelIndex();
}

int ComponentProxyModel::rowCount(const QModelIndex& parent) const
{
    QModelIndex sourceParent;
    if (parent.isValid())
        sourceParent = mapToSource(parent);
    int count = 0;
    QMapIterator<QPersistentModelIndex, QPersistentModelIndex> it(m_proxySourceParent);

    while (it.hasNext()) {
        it.next();
        if (it.value() == sourceParent)
            count++;
    }
    return count;
}

int ComponentProxyModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return SessionModel::MAX_COLUMNS;
}

//! Main method to build the map of persistent indeses.

void ComponentProxyModel::buildModelMap()
{
    m_sourceToProxy.clear();
    m_proxySourceParent.clear();

    ModelUtils::iterate(QModelIndex(), m_model, [=](const QModelIndex& index){
       SessionItem* item = m_model->itemForIndex(index);

       QPersistentModelIndex proxy = createIndex(index.row(), index.column(), item);
       m_sourceToProxy.insert(QPersistentModelIndex(index), proxy);

       QPersistentModelIndex sourceParent;
       if (item->parent())
           sourceParent = item->parent()->index();

       m_proxySourceParent.insert(proxy, sourceParent);
    });

}

