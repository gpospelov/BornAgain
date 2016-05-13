// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterProxyModel.cpp
//! @brief     Implements class FitParameterProxyModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterProxyModel.h"
#include "SessionItem.h"
#include "FitParameterItems.h"
#include "JobModel.h"
#include <QDebug>

//FitParameterProxyModel::FitParameterProxyModel(JobModel *jobModel, FitParameterContainerItem *fitParContainer, QObject *parent)
//    : QAbstractProxyModel(parent)
//    , m_jobModel(jobModel)
//    , m_parContainer(fitParContainer)
//{
//    Q_ASSERT(m_jobModel);
//    Q_ASSERT(m_parContainer);
//    setSourceModel(m_jobModel);
//}

FitParameterProxyModel::FitParameterProxyModel(FitParameterContainerItem *fitParContainer, QObject *parent)
    : QAbstractProxyModel(parent)
    , m_parContainer(fitParContainer)
{
    Q_ASSERT(m_parContainer);
    setSourceModel(fitParContainer->model());
    m_columnNames.insert(0, "Name");
    m_columnNames.insert(1, FitParameterItem::P_TYPE);
    m_columnNames.insert(3, FitParameterItem::P_MIN);
    m_columnNames.insert(2, FitParameterItem::P_START_VALUE);
    m_columnNames.insert(4, FitParameterItem::P_MAX);
}

QModelIndex FitParameterProxyModel::index(int row, int column, const QModelIndex &parent) const
{
//    if (row < 0 || column < 0 || column >= 1
//        || (parent.isValid() && parent.column() != 0))
//        return QModelIndex();

//    SessionItem *parent_item = m_jobModel->itemForIndex(mapToSource(parent));
//    if (SessionItem *item = parent_item->childAt(row)) {
//        return createIndex(row, column, item);
//    }

//    return QModelIndex();

    Q_ASSERT(parent.isValid() ? parent.model() == this : true);
    const QModelIndex sourceParent = mapToSource(parent);
    const QModelIndex sourceIndex = sourceModel()->index(row, column, sourceParent);
    return mapFromSource(sourceIndex);
}

QModelIndex FitParameterProxyModel::parent(const QModelIndex &child) const
{
//    if (!child.isValid())
//        return QModelIndex();
//    if (SessionItem *child_item = itemForIndex(child)) {
//        if (SessionItem *parent_item = child_item->parent()) {
//            if (parent_item == m_root_item)
//                return QModelIndex();

//            return createIndex(parent_item->parentRow(), 0, parent_item);
//        }
//    }
//    return QModelIndex();

    Q_ASSERT(child.isValid() ? child.model() == this : true);
    const QModelIndex sourceIndex = mapToSource(child);
    const QModelIndex sourceParent = sourceIndex.parent();
    return mapFromSource(sourceParent);
}

int FitParameterProxyModel::rowCount(const QModelIndex &parent) const
{
    Q_ASSERT(parent.isValid() ? parent.model() == this : true);
    return sourceModel()->rowCount(mapToSource(parent));


//    if(!parent.isValid()) {
//        return m_parContainer->rowCount();
//    }

//    QModelIndex sourceIndex = mapToSource(parent);
    if (SessionItem *item = this->itemForIndex(parent)) {
//        if(item->modelType() == Constants::FitParameterContainerType ||
//           item->modelType() == Constants::FitParameterType ) {
//            return item->rowCount();
//        }
        if(item->modelType() == Constants::FitParameterType) {
            return 0;
        }
    }

//    return 0;
    return sourceModel()->rowCount(mapToSource(parent));
}

int FitParameterProxyModel::columnCount(const QModelIndex &parent) const
{
    Q_ASSERT(parent.isValid() ? parent.model() == this : true);
    return sourceModel()->columnCount(mapToSource(parent));


    return 5;

    if (SessionItem *item = this->itemForIndex(parent)) {
//        if(item->modelType() == Constants::FitParameterContainerType ||
//           item->modelType() == Constants::FitParameterType ) {
//            return item->rowCount();
//        }
        if(item->modelType() == Constants::FitParameterType) {
            return 5;
        }
    }

    return sourceModel()->columnCount(mapToSource(parent));
}

QVariant FitParameterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames.value(section);
    }
    return QVariant();

}

QModelIndex FitParameterProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!sourceModel() || !proxyIndex.isValid())
        return QModelIndex();
    Q_ASSERT(proxyIndex.model() == this);
//    return QModelIndex(proxyIndex.row(), proxyIndex.column(), proxyIndex.internalPointer(), sourceModel());
//    return sourceModel()->createIndex(proxyIndex.row(), proxyIndex.column(), proxyIndex.internalPointer());

    if (SessionItem *item = this->itemForIndex(proxyIndex)) {
        QModelIndex sourceParent;
        if(item->parent()) sourceParent = item->parent()->index();
        return jobModel()->index(proxyIndex.row(), proxyIndex.column(), sourceParent);
//        return item->index();
    }
    return QModelIndex();

//    if(proxyIndex.isValid()) {
//        const QModelIndex sourceIndex = mapToSource(proxyIndex);
//        const QModelIndex sourceParent = sourceIndex.parent();

//        return m_jobModel->index(proxyIndex.row(), proxyIndex.column(), sourceParent);
//    }

//    return QModelIndex();

}

QModelIndex FitParameterProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
//    if (!sourceModel() || !sourceIndex.isValid())
//        return QModelIndex();
//    Q_ASSERT(sourceIndex.model() == sourceModel());
//    return createIndex(sourceIndex.row(), sourceIndex.column(), sourceIndex.internalPointer());


    if (!sourceModel() || !sourceIndex.isValid())
        return QModelIndex();

    int irow = sourceIndex.row();
    int icol = sourceIndex.column();

    if (SessionItem *item = jobModel()->itemForIndex(sourceIndex)) {
        if(SessionItem *parent = item->parent()) {
//            if(parent->modelType() == Constants::JobItemType || parent->modelType() == Constants::FitSuiteType) {
//                return QModelIndex();
//            }



//            qDebug() << "AAA" << item->modelType() << parent->modelType();
//            Q_ASSERT(0);
//            if(parent->modelType() == Constants::FitParameterContainerType) {
//                icol = m_columnNames.key(parent->tagFromItem(item));
//                qDebug() << "AAAAA" << icol << parent->tagFromItem(item);
//                Q_ASSERT(0);
//            }
        }
    }

    Q_ASSERT(sourceIndex.model() == sourceModel());
    return createIndex(irow, icol, sourceIndex.internalPointer());
}

SessionItem *FitParameterProxyModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (SessionItem *item = static_cast<SessionItem *>(index.internalPointer()))
            return item;
    }
    return 0;
}

JobModel *FitParameterProxyModel::jobModel() const
{
    return dynamic_cast<JobModel *>(m_parContainer->model());
}
