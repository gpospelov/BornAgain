// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionProxyModels.cpp
//! @brief     Implement classes related to SessionModel proxies
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
    ParameterizedItem *parentt = m_source->itemForIndex(sourceParent);
    if (parentt->modelType() == Constants::GroupItemType) {
        ParameterizedItem *cur = parentt->parent()->getGroupItem(parentt->itemName());
        const QModelIndex sourceIndex = m_source->index(row, column, cur->index());
        return mapFromSource(sourceIndex);
    }
    const QModelIndex sourceIndex = m_source->index(row, column, sourceParent);
    return mapFromSource(sourceIndex);
}

QModelIndex SessionCompactModel::parent(const QModelIndex &child) const
{
    const QModelIndex sourceIndex = mapToSource(child);
    ParameterizedItem *head = m_source->itemForIndex(sourceIndex.parent());
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
    ParameterizedItem *item = m_source->itemForIndex(sourceParent);
    if (item && item->modelType() == Constants::GroupItemType) {
        ParameterizedItem *cur = item->parent()->getGroupItem(item->itemName());
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
//    ParameterizedItem *item = m_source->itemForIndex(sourceIndex);
//    return createIndex(sourceIndex.row(), sourceIndex.column(), item);


    int nrow(0);
    for(int i_row=0; i_row<m_source->rowCount(sourceIndex.parent()); ++i_row) {
        QModelIndex itemIndex = m_source->index(i_row, sourceIndex.column(), sourceIndex.parent());
        if(ParameterizedItem *item = m_source->itemForIndex(itemIndex)) {
            if(item->getAttribute().isHidden()) continue;
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
//    ParameterizedItem *item = static_cast<ParameterizedItem *>(proxyIndex.internalPointer());
//    if(item && item->parent()) {
//        return m_source->index(proxyIndex.row(), proxyIndex.column(), m_source->indexOfItem(item->parent()));
//    } else {
//        return m_source->index(proxyIndex.row(), proxyIndex.column(), QModelIndex());
//    }


    ParameterizedItem *item = static_cast<ParameterizedItem *>(proxyIndex.internalPointer());
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
//    ParameterizedItem *item = static_cast<ParameterizedItem *>(proxyIndex.internalPointer());

}

QModelIndex SessionTestModel::parent(const QModelIndex &child) const
{
    const QModelIndex sourceIndex = mapToSource(child);
//    ParameterizedItem *head = m_source->itemForIndex(sourceIndex.parent());
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

    ParameterizedItem *item = m_source->itemForIndex(sourceParent);
    int nrow(0);
    foreach(ParameterizedItem *child, item->childItems()) {
        if(child->getAttribute().isHidden()) continue;
        ++nrow;
    }
    return nrow;

//    ParameterizedItem *item = m_source->itemForIndex(sourceParent);
//    if (item && item->modelType() == Constants::GroupItemType) {
//        ParameterizedItem *cur = item->parent()->getGroupItem(item->itemName());
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


