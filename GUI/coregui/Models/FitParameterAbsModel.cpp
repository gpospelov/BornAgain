// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterAbsModel.cpp
//! @brief     Implements class FitParameterAbsModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterAbsModel.h"
#include "SessionItem.h"
#include "FitParameterItems.h"
#include "SessionModel.h"
#include "JobModel.h"
#include <QDebug>

FitParameterAbsModel::FitParameterAbsModel(FitParameterContainerItem *fitParContainer, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(fitParContainer)
{
    m_columnNames.insert(ITEM_NAME, "Name");
    m_columnNames.insert(ITEM_USE, FitParameterItem::P_TYPE);
    m_columnNames.insert(ITEM_MIN, FitParameterItem::P_MIN);
    m_columnNames.insert(ITEM_START, FitParameterItem::P_START_VALUE);
    m_columnNames.insert(ITEM_MAX, FitParameterItem::P_MAX);

    connectModel(fitParContainer->model());

    m_root_item->mapper()->setOnItemDestroy(
                [this](SessionItem *parent) {
        Q_ASSERT(parent == m_root_item);
        m_root_item = 0;
    });

}

Qt::ItemFlags FitParameterAbsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags returnVal = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.isValid() && index.parent() == QModelIndex()) {
        if (index.column() == 0)
            returnVal |= Qt::ItemIsDropEnabled;
        else
            returnVal |= Qt::ItemIsEditable;
    } else if (!index.isValid()) {
        returnVal |= Qt::ItemIsDropEnabled;
    }
    return returnVal;
}

QModelIndex FitParameterAbsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= columnCount(QModelIndex())
        || (parent.isValid() && parent.column() != 0))
        return QModelIndex();

    SessionItem *parent_item = itemForIndex(parent);
    Q_ASSERT(parent_item);

    if(parent_item->modelType() == Constants::FitParameterContainerType) {
        if (SessionItem *fitParItem = parent_item->childAt(row)) {
            SessionItem *itemToPack = fitParItem;
            if(column != 0) {
                itemToPack = fitParItem->getItem(m_columnNames.value(column));
            }
            return createIndex(row, column, itemToPack);
        }
    }

    else if(parent_item->modelType() == Constants::FitParameterType && column == 0) {
        QVector<SessionItem *> links = parent_item->getItems(FitParameterItem::T_LINK);
        if(row < links.size()) {
            if(SessionItem *linkItem = links.at(row)) {
                return createIndex(row, column, linkItem->getItem(FitParameterLinkItem::P_LINK));
            }
        }
    }

    return QModelIndex();
}

QModelIndex FitParameterAbsModel::parent(const QModelIndex &child) const
{
    if(!m_root_item) return QModelIndex();

    if (!child.isValid())
        return QModelIndex();

    if (SessionItem *child_item = itemForIndex(child)) {
        if (SessionItem *parent_item = child_item->parent()) {
            if(parent_item->modelType()==Constants::FitParameterLinkType) {
                SessionItem *fitPar = parent_item->parent();
                return createIndex(fitPar->parentRow(), 0, fitPar);
            }
        }

    }

    return QModelIndex();
}

int FitParameterAbsModel::rowCount(const QModelIndex &parent) const
{
    if(!m_root_item) return 0;

    if (parent.isValid() && parent.column() != 0)
        return 0;
    SessionItem *parent_item = itemForIndex(parent);

    if(parent_item->modelType() == Constants::FitParameterContainerType) {
        return parent_item->rowCount();
    }

    else if(parent_item->modelType() == Constants::FitParameterType) {
        return parent_item->getItems(FitParameterItem::T_LINK).size();
    }

    return 0;
}

int FitParameterAbsModel::columnCount(const QModelIndex &parent) const
{
    if(!m_root_item) return 0;

    if (parent.isValid() && parent.column() != 0)
        return 0;

    if(!parent.isValid())
        return MAX_COLUMNS;

    if(parent.isValid()) {
        if(SessionItem *parentItem = itemForIndex(parent)) {
            if(parentItem->modelType() == Constants::FitParameterType) {
                return (parentItem->getItems(FitParameterItem::T_LINK).size() ? 1 : 0);
            }
        }

    }

    return 0;
}

QVariant FitParameterAbsModel::data(const QModelIndex &index, int role) const
{
    if(!m_root_item) return QVariant();

    if ( !index.isValid() || index.column() < 0 || index.column() >= MAX_COLUMNS)
        return QVariant();

    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if(item->modelType() == Constants::FitParameterType) {
                return item->displayName();
            } else {
                return item->value();
            }
        }
    }

    return QVariant();
}

bool FitParameterAbsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!m_root_item) return false;

    if (!index.isValid())
        return false;
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole) {
            item->setValue(value);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant FitParameterAbsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames.value(section);
    }
    return QVariant();
}


void FitParameterAbsModel::onSourceDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    Q_UNUSED(bottomRight);

    JobModel *sourceModel = qobject_cast<JobModel *>(sender());
    Q_ASSERT(sourceModel);
    SessionItem *sourceItem = sourceModel->itemForIndex(topLeft);

    QModelIndex itemIndex = indexOfItem(sourceItem);

    if(itemIndex.isValid())
        emit dataChanged(itemIndex, itemIndex, roles);
}

void FitParameterAbsModel::onSourceRowsInserted(const QModelIndex &parent, int first, int last)
{
//    Q_UNUSED(parent);
//    Q_UNUSED(first);
//    Q_UNUSED(last);
    qDebug() << "FitParameterAbsModel::onSourceRowsInserted" << parent << first << last;
    JobModel *sourceModel = qobject_cast<JobModel *>(sender());
    Q_ASSERT(sourceModel);

    return;
    if(SessionItem *sourceItem = sourceModel->itemForIndex(parent)) {
        if(sourceItem->modelType() == Constants::FitParameterContainerType) {
            beginInsertRows(QModelIndex(), first, first);
            endInsertRows();
        }

    }

}

void FitParameterAbsModel::onSourceBeginRemoveRows(const QModelIndex &parent, int first, int last)
{
    qDebug() << "FitParameterAbsModel::onSourceBeginRemoveRows" << parent << first << last;
    JobModel *sourceModel = qobject_cast<JobModel *>(sender());
    Q_ASSERT(sourceModel);

// Two alternative ways which seems to be working
    // way #1
    beginResetModel();

    QModelIndex itemIndex = sourceModel->index(first, 0, parent);
    if(sourceModel->itemForIndex(itemIndex) == m_root_item)
        m_root_item = 0;


    endResetModel();


    return;

    // way #2
    if(SessionItem *sourceItem = sourceModel->itemForIndex(parent)) {
        QModelIndex localIndex = indexOfItem(sourceItem);
        beginRemoveRows(localIndex, 0, rowCount(localIndex));
        endRemoveRows();

        QModelIndex itemIndex = sourceModel->index(first, 0, parent);
        if(sourceModel->itemForIndex(itemIndex) == m_root_item)
            m_root_item = 0;

    }
}

void FitParameterAbsModel::onSourceAboutToBeReset()
{
    beginResetModel();
    endResetModel();
}

void FitParameterAbsModel::connectModel(QAbstractItemModel *sourceModel, bool isConnect)
{
    Q_ASSERT(sourceModel);
    if(isConnect) {
        connect(sourceModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                this, SLOT(onSourceDataChanged(QModelIndex,QModelIndex,QVector<int>)));
//        connect(sourceModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
//                   this, SLOT(onSourceRowsInserted(QModelIndex,int,int)));
        connect(sourceModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                   this, SLOT(onSourceBeginRemoveRows(QModelIndex,int,int)));
        connect(sourceModel, SIGNAL(modelAboutToBeReset()), this, SLOT(onSourceAboutToBeReset()));



    }

    else {
        disconnect(sourceModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                this, SLOT(onSourceDataChanged(QModelIndex,QModelIndex,QVector<int>)));
//        disconnect(sourceModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
//                   this, SLOT(onSourceRowsInserted(QModelIndex,int,int)));
        disconnect(sourceModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                   this, SLOT(onSourceBeginRemoveRows(QModelIndex,int,int)));
        disconnect(sourceModel, SIGNAL(modelAboutToBeReset()), this, SLOT(onSourceAboutToBeReset()));
    }
}

QModelIndex FitParameterAbsModel::indexOfItem(SessionItem *item) const
{

    if(SessionItem *parent_item = item->parent()) {
        if(parent_item->modelType() == Constants::FitParameterContainerType) {
            if(item->modelType() == Constants::FitParameterType) {
                return createIndex(item->parentRow(), 0, item);
            }
        }

        else if(parent_item->modelType() == Constants::FitParameterType) {

            QString tag = parent_item->tagFromItem(item);
            int col = m_columnNames.key(tag, -1);
            if(col > 0) {
                return createIndex(parent_item->parentRow(), col, item);
            }
        }

        else if(parent_item->modelType() == Constants::FitParameterLinkType) {
            QVector<SessionItem *> links = parent_item->parent()->getItems(FitParameterItem::T_LINK);
            return createIndex(links.indexOf(parent_item), 0, item);
        }

    }

    return QModelIndex();
}

SessionItem *FitParameterAbsModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (SessionItem *item = static_cast<SessionItem *>(index.internalPointer()))
            return item;
    }
    return m_root_item;
}
