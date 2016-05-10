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
#include <QDebug>

FitParameterAbsModel::FitParameterAbsModel(FitParameterContainerItem *fitParContainer, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(fitParContainer)
{
    m_columnNames.insert(0, "Name");
    m_columnNames.insert(1, FitParameterItem::P_USE);
    m_columnNames.insert(3, FitParameterItem::P_MIN);
    m_columnNames.insert(2, FitParameterItem::P_START_VALUE);
    m_columnNames.insert(4, FitParameterItem::P_MAX);

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

        if(links.size()) {
            if(SessionItem *linkItem = links.at(row)) {
                return createIndex(row, column, linkItem->getItem(FitParameterLinkItem::P_LINK));
            }
        }

    }


    return QModelIndex();


}

QModelIndex FitParameterAbsModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

//    qDebug() << "FitParameterAbsModel::parent";
    if (SessionItem *child_item = itemForIndex(child)) {
        if (SessionItem *parent_item = child_item->parent()) {
            if(parent_item->modelType()==Constants::FitParameterLinkType) {
//                qDebug() << "FitParameterAbsModel::parent" << child_item->modelType() << parent_item->modelType();

                return createIndex(0, 0, parent_item->parent());
            }
        }

    }


//    if (SessionItem *child_item = itemForIndex(child)) {
//        if (SessionItem *parent_item = child_item->parent()) {
//            if (parent_item == m_root_item)
//                return QModelIndex();

//            return createIndex(parent_item->parentRow(), 0, parent_item);
//        }
//    }
//    qDebug() << "               FitParameterAbsModel::parent QModelIndex()";
    return QModelIndex();

}

int FitParameterAbsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    SessionItem *parent_item = itemForIndex(parent);

//    qDebug() << "FitParameterAbsModel::rowCount" << parent << parent_item->modelType();
    if(parent_item->modelType() == Constants::FitParameterContainerType) {
//        qDebug() << "     XXX " << parent_item->rowCount();
        return parent_item->rowCount();
    }
    else if(parent_item->modelType() == Constants::FitParameterType) {
//        qDebug() << "     XXX " <<parent_item->getItems(FitParameterItem::T_LINK).size();
        return parent_item->getItems(FitParameterItem::T_LINK).size();
    }
    return 0;
//    return parent_item ? parent_item->rowCount() : 0;
}

int FitParameterAbsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return 5;

}

QVariant FitParameterAbsModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() || index.column() < 0 || index.column() >= 5) {
        return QVariant();
    }
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
//            qDebug() << "BBB" << index << role << item->modelType();
            if(item->modelType() == Constants::FitParameterType) {
                return item->displayName();
            } else {
                return item->value();
            }
//            if(index.column() == 0) {
//                return item->displayName();
//            } else {
//                return item->value();
//            }
        }

//        if (role == Qt::DisplayRole || role == Qt::EditRole) {
//            if (item->parent() != itemForIndex(QModelIndex()))
//            {
//                if (index.column() == 0) {
//                    QVector<SessionItem *> links = item->parent()->getItems(FitParameterItem::T_LINK);

//                    if(links.size()) {
//                        if(SessionItem *linkItem = links.at(index.row())) {
//                            return linkItem->getItemValue(FitParameterLinkItem::P_LINK);
//                        }
//                    }
//                } else {
//                    return QVariant();
//                }
//            }
//            if (index.column() == 0)
//                return item->itemName();
//            else
//                return item->getItemValue(m_columnNames.value(index.column()));
//        }
    }
    return QVariant();
}

//QModelIndex FitParameterAbsModel::indexOfItem(SessionItem *item) const
//{

//}

SessionItem *FitParameterAbsModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (SessionItem *item = static_cast<SessionItem *>(index.internalPointer()))
            return item;
    }
    return m_root_item;
}
