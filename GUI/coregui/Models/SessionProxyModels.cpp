// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionProxyModels.cpp
//! @brief     Implement classes related to SessionModel proxies
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionProxyModels.h"
#include <QDebug>

SessionCompactModel::SessionCompactModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
}

void SessionCompactModel::setSourceModel(QAbstractItemModel *source)
{
    QIdentityProxyModel::setSourceModel(source);
    m_source = dynamic_cast<SessionModel*>(source);
    connect(m_source, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SIGNAL(layoutChanged()));
}

QModelIndex SessionCompactModel::index(int row, int column, const QModelIndex &parent) const
{
    const QModelIndex sourceParent = mapToSource(parent);
    SessionItem *parentt = m_source->itemForIndex(sourceParent);
    if (parentt->modelType() == Constants::GroupItemType) {
        SessionItem *cur = parentt->parent()->getGroupItem(parentt->itemName());
        const QModelIndex sourceIndex = m_source->index(row, column, cur->index());
        return mapFromSource(sourceIndex);
    }
    const QModelIndex sourceIndex = m_source->index(row, column, sourceParent);
    return mapFromSource(sourceIndex);
}

QModelIndex SessionCompactModel::parent(const QModelIndex &child) const
{
    const QModelIndex sourceIndex = mapToSource(child);
    SessionItem *head = m_source->itemForIndex(sourceIndex.parent());
    if (head && head->parent() && head->parent()->modelType() == Constants::GroupItemType) {
        // skip immediate layer
        return mapFromSource(head->parent()->index());
    }
    const QModelIndex sourceParent = sourceIndex.parent();
    return mapFromSource(sourceParent);
}

int SessionCompactModel::rowCount(const QModelIndex &parent) const
{
    QModelIndex sourceParent = mapToSource(parent);
    SessionItem *item = m_source->itemForIndex(sourceParent);
    if (item && item->modelType() == Constants::GroupItemType) {
        SessionItem *cur = item->parent()->getGroupItem(item->itemName());
        if (cur)
            return m_source->rowCount(cur->index());
        else
            qDebug() << "proxy::rowCount: null pointer";
    }
    return m_source->rowCount(sourceParent);
}

// --------------------------------------------------------


SessionTestModel::SessionTestModel(QObject *parent)
    : QAbstractProxyModel(parent)
{

}

void SessionTestModel::setSourceModel(QAbstractItemModel *source)
{
    QAbstractProxyModel::setSourceModel(source);
    m_source = dynamic_cast<SessionModel*>(source);
}

QModelIndex SessionTestModel::mapFromSource(const QModelIndex &sourceIndex) const
{

    // one to one
//    SessionItem *item = m_source->itemForIndex(sourceIndex);
//    return createIndex(sourceIndex.row(), sourceIndex.column(), item);


    int nrow(0);
    for(int i_row=0; i_row<m_source->rowCount(sourceIndex.parent()); ++i_row) {
        QModelIndex itemIndex = m_source->index(i_row, sourceIndex.column(), sourceIndex.parent());
        if(SessionItem *item = m_source->itemForIndex(itemIndex)) {
            if(!item->isVisible()) continue;
            if(i_row == sourceIndex.row()) {
                return createIndex(nrow, sourceIndex.column(), item);
            }
            ++nrow;
        }

    }
//    return createIndex(sourceIndex.row(), sourceIndex.column(), item);
    return QModelIndex();


}

QModelIndex SessionTestModel::mapToSource(const QModelIndex &proxyIndex) const
{
    // ont-to-one
//    SessionItem *item = static_cast<SessionItem *>(proxyIndex.internalPointer());
//    if(item && item->parent()) {
//        return m_source->index(proxyIndex.row(), proxyIndex.column(), m_source->indexOfItem(item->parent()));
//    } else {
//        return m_source->index(proxyIndex.row(), proxyIndex.column(), QModelIndex());
//    }


    SessionItem *item = static_cast<SessionItem *>(proxyIndex.internalPointer());
    if(item) {
        if(item->parent()) {
            return m_source->index(item->index().row(), proxyIndex.column(), item->parent()->index());
        } else {
            return m_source->index(item->index().row(), proxyIndex.column(), QModelIndex());
        }
    }
    return QModelIndex();


}

QModelIndex SessionTestModel::index(int row, int column, const QModelIndex &parent) const
{
//    const QModelIndex sourceParent = mapToSource(parent);
//    const QModelIndex sourceIndex = m_source->index(row, column, sourceParent);
//    return mapFromSource(sourceIndex);

    if(row <0 || row >=rowCount(parent) || column <0 || column >=columnCount(parent)) return QModelIndex();

    return createIndex(row, column, nullptr);
//    SessionItem *item = static_cast<SessionItem *>(proxyIndex.internalPointer());

}

QModelIndex SessionTestModel::parent(const QModelIndex &child) const
{
    const QModelIndex sourceIndex = mapToSource(child);
//    SessionItem *head = m_source->itemForIndex(sourceIndex.parent());
//    if (head && head->parent() && head->parent()->modelType() == Constants::GroupItemType) {
//        // skip immediate layer
//        return mapFromSource(head->parent()->index());
//    }
    const QModelIndex sourceParent = sourceIndex.parent();
    return mapFromSource(sourceParent);
}

int SessionTestModel::rowCount(const QModelIndex &parent) const
{
    // one to one
    QModelIndex sourceParent = mapToSource(parent);
//    return m_source->rowCount(sourceParent);

    SessionItem *item = m_source->itemForIndex(sourceParent);
    int nrow(0);
    foreach(SessionItem *child, item->childItems()) {
        if(!child->isVisible()) continue;
        ++nrow;
    }
    return nrow;

//    SessionItem *item = m_source->itemForIndex(sourceParent);
//    if (item && item->modelType() == Constants::GroupItemType) {
//        SessionItem *cur = item->parent()->getGroupItem(item->itemName());
//        if (cur)
//            return m_source->rowCount(cur->index());
//        else
//            qDebug() << "proxy::rowCount: null pointer";
//    }
}

int SessionTestModel::columnCount(const QModelIndex &parent) const
{
    QModelIndex sourceParent = mapToSource(parent);
    return m_source->columnCount(sourceParent);
}


