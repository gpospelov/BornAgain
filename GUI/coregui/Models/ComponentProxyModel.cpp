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

    if (sourceModel()) {
        disconnect(sourceModel(), &QAbstractItemModel::dataChanged,
                   this, &ComponentProxyModel::sourceDataChanged);
        disconnect(sourceModel(), &QAbstractItemModel::layoutAboutToBeChanged,
                   this, &ComponentProxyModel::sourceLayoutAboutToBeChanged);
        disconnect(sourceModel(), &QAbstractItemModel::layoutChanged,
                   this, &ComponentProxyModel::sourceLayoutChanged);
        disconnect(sourceModel(), &QAbstractItemModel::rowsAboutToBeInserted,
                   this, &ComponentProxyModel::sourceRowsAboutToBeInserted);
        disconnect(sourceModel(), &QAbstractItemModel::rowsInserted,
                   this, &ComponentProxyModel::sourceRowsInserted);

    }

    QAbstractProxyModel::setSourceModel(model);

    if (sourceModel()) {
        connect(sourceModel(), &QAbstractItemModel::dataChanged,
                   this, &ComponentProxyModel::sourceDataChanged);
        connect(sourceModel(), &QAbstractItemModel::layoutAboutToBeChanged,
                   this, &ComponentProxyModel::sourceLayoutAboutToBeChanged);
        connect(sourceModel(), &QAbstractItemModel::layoutChanged,
                   this, &ComponentProxyModel::sourceLayoutChanged);
        connect(sourceModel(), &QAbstractItemModel::rowsAboutToBeInserted,
                   this, &ComponentProxyModel::sourceRowsAboutToBeInserted);
        connect(sourceModel(), &QAbstractItemModel::rowsInserted,
                   this, &ComponentProxyModel::sourceRowsInserted);
    }

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
    QMapIterator<QPersistentModelIndex, QPersistentModelIndex> it(m_proxySourceParent);

    QSet<int> rows;
    while (it.hasNext()) {
        it.next();
        if (it.value() == sourceParent)
            rows.insert(it.key().row());
    }
    return rows.size();
}

int ComponentProxyModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return SessionModel::MAX_COLUMNS;
}

void ComponentProxyModel::sourceDataChanged(const QModelIndex& topLeft,
                                              const QModelIndex& bottomRight,
                                              const QVector<int>& roles)
{
    Q_ASSERT(topLeft.isValid() ? topLeft.model() == sourceModel() : true);
    Q_ASSERT(bottomRight.isValid() ? bottomRight.model() == sourceModel() : true);
    dataChanged(mapFromSource(topLeft), mapFromSource(bottomRight), roles);
}

void ComponentProxyModel::sourceLayoutAboutToBeChanged(
    const QList<QPersistentModelIndex>& sourceParents, QAbstractItemModel::LayoutChangeHint hint)
{
    Q_UNUSED(sourceParents);
    Q_UNUSED(hint);
    qDebug() << "ComponentProxyModel::sourceLayoutAboutToBeChanged";
}

void ComponentProxyModel::sourceLayoutChanged(const QList<QPersistentModelIndex>& sourceParents,
                                              QAbstractItemModel::LayoutChangeHint hint)
{
    Q_UNUSED(sourceParents);
    Q_UNUSED(hint);
    qDebug() << "ComponentProxyModel::sourceLayoutChanged";
}

void ComponentProxyModel::sourceRowsAboutToBeInserted(const QModelIndex& parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);

    qDebug() << "ComponentProxyModel::sourceRowsAboutToBeInserted";
//    buildModelMap();
}

void ComponentProxyModel::sourceRowsInserted(const QModelIndex& parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);

    qDebug() << "ComponentProxyModel::sourceRowsInserted";
    buildModelMap();
}

//! Main method to build the map of persistent indeses.

void ComponentProxyModel::buildModelMap()
{
    m_sourceToProxy.clear();
    m_proxySourceParent.clear();

    ModelUtils::iterate(QModelIndex(), m_model, [=](const QModelIndex& index){
       SessionItem* item = m_model->itemForIndex(index);

//       qDebug() << "XXX index" << index << "index.parent" << index.parent();
       QPersistentModelIndex proxy = createIndex(index.row(), index.column(), item);
       m_sourceToProxy.insert(QPersistentModelIndex(index), proxy);

       QPersistentModelIndex sourceParent;
       if (index.parent().isValid())
           sourceParent = index.parent();

//       qDebug() << "YYY proxy" << proxy << "sourceParent" << sourceParent;
       m_proxySourceParent.insert(proxy, sourceParent);
//       qDebug() << " ";
    });

    layoutChanged();
}
