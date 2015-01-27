// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitProxyModel.cpp
//! @brief     Implements class FitProxyModel
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitProxyModel.h"
#include "FitModel.h"
#include "ParameterizedItem.h"
#include "FitParameterItem.h"
#include <QDebug>


FitProxyModel::FitProxyModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

void FitProxyModel::setFitModel(FitModel *fitModel)
{
    m_fitModel = fitModel;
}

QVariant FitProxyModel::data(const QModelIndex &index, int role) const
{

//    if(role == Qt::DisplayRole) {
//        return QVariant(index.column());
//    }

//    return QVariant();

//    if (!index.isValid() || index.column() < 0
//            || index.column() >= columnCount(index)) {

//        qDebug() << "XXXXXXXXX FitProxyModel::data index.isValid(): " << index;

//        return QVariant();
//    }

    if(!index.isValid())
    {
        return QVariant();
    }


    if(index.isValid() && !index.parent().isValid())
    {
        //ParameterizedItem
        if (ParameterizedItem *item = itemForIndex(index)) {

            if(role == Qt::DisplayRole || role == Qt::EditRole) {
                switch (index.column()) {
                case 0: return item->itemName();
                case 1: return item->getRegisteredProperty(FitParameterItem::P_USE);
                case 2: return item->getRegisteredProperty(FitParameterItem::P_VALUE);
                case 3: return item->getRegisteredProperty(FitParameterItem::P_MIN);
                case 4: return item->getRegisteredProperty(FitParameterItem::P_MAX);
                default: return QVariant();
                }
            }
        }
    }

    if(index.isValid() && index.parent().isValid())
    {
        //description
        if (FitParameterItem *item = dynamic_cast<FitParameterItem *>(itemForIndex(index.parent()))) {
            if(item->getParNames().size() >0)
            {
                return QVariant(item->getParNames().at(0));
            }
        }
    }

    return QVariant();
}

int FitProxyModel::rowCount(const QModelIndex &parentIndex) const
{
    if(parentIndex.isValid())
    {
        return 0;
    }

    if(parentIndex.isValid() && parentIndex.parent().isValid())
    {
//        if (FitParameterItem *item = dynamic_cast<FitParameterItem *>(itemForIndex(index.parent()))) {
//            return item->getParNames().size();
//        }

        return 1;
    }


    int counter = 0;

    if(m_fitModel)
    {
        for( int i_row = 0; i_row < m_fitModel->rowCount( parentIndex ); ++i_row) {
            QModelIndex itemIndex = m_fitModel->index( i_row, 0, parentIndex );

            if (ParameterizedItem *item = m_fitModel->itemForIndex(itemIndex)){
                Q_UNUSED(item);
                counter++;
            }
        }
    }

    return counter;
}

int FitProxyModel::columnCount(const QModelIndex &parentIndex) const
{
    if(!parentIndex.isValid())
    {
        return 5;
    }

    if(parentIndex.isValid() && !parentIndex.parent().isValid())
    {
        return 1;
    }

    return 0;
}

QModelIndex FitProxyModel::index(int row, int column,
                                 const QModelIndex &parentIndex) const
{
    ParameterizedItem *parent_item = m_fitModel->itemForIndex(parentIndex);
    if (ParameterizedItem *item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}

QModelIndex FitProxyModel::parent(const QModelIndex &/*child*/) const
{
    /*if (!child.isValid()) return QModelIndex();
    if (ParameterizedItem *child_item = itemForIndex(child)) {
        if (ParameterizedItem *parent_item = child_item->parent()) {

            if (ParameterizedItem *grandparent_item = parent_item->parent())
            {
                int row = grandparent_item->rowOfChild(parent_item);
                return createIndex(row, 0, parent_item);
            }
        }
    }*/
    return QModelIndex();

}

Qt::ItemFlags FitProxyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsEnabled |Qt::ItemIsEditable;
    }
    else {
        result_flags |= Qt::ItemIsEditable;
    }
    return result_flags;
}

bool FitProxyModel::setData(const QModelIndex &index,
                           const QVariant &value, int role)
{
    if (!index.isValid()) return false;


    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role==Qt::EditRole) {
            qDebug() << "FitProxyModel::setData ";

            switch (index.column()) {
            case 0:
                item->setItemName(value.toString());
                break;
            case 1:
                item->setRegisteredProperty(FitParameterItem::P_USE, value);
                break;
            case 2:
                item->setRegisteredProperty(FitParameterItem::P_VALUE, value);
                break;
            case 3:
                item->setRegisteredProperty(FitParameterItem::P_MIN, value);
                break;
            case 4:
                item->setRegisteredProperty(FitParameterItem::P_MAX, value);
                break;
            default:
                return false;

            }
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

ParameterizedItem *FitProxyModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (ParameterizedItem *item = static_cast<ParameterizedItem *>(
                    index.internalPointer()))
            return item;
    }

    //ParameterizedItem *item = m_fitModel->itemForIndex(index);

    return 0;
}



