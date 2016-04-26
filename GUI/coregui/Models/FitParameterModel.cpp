// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitParameterModel.h
//! @brief     Declares class FitParameterModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParameterModel.h"
#include "JobModel.h"
#include "FitParameterItems.h"
#include <QDebug>

FitParameterModel::FitParameterModel(SessionItem *fitParContainer, QObject *parent)
    : SessionModel(QString("FitParameterModel"), parent)
{
    setRootItem(fitParContainer);
    m_columnNames.insert(0, "FitParameterItem::OBSOLETE_P_NAME");
    m_columnNames.insert(1, FitParameterItem::P_USE);
    m_columnNames.insert(3, FitParameterItem::P_MIN);
    m_columnNames.insert(2, FitParameterItem::P_INIT);
    m_columnNames.insert(4, FitParameterItem::P_MAX);
}

FitParameterModel::~FitParameterModel()
{
    setRootItem(0);
}

Qt::ItemFlags FitParameterModel::flags(const QModelIndex &index) const
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


QVariant FitParameterModel::data(const QModelIndex & index, int role) const
{
    if ( !index.isValid() || index.column() < 0 || index.column() >= 5) {
        return QVariant();
    }
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (item->parent() != itemForIndex(QModelIndex()))
            {
                if (index.column() == 0) {
                    QVector<SessionItem *> links = item->parent()->getItems(FitParameterItem::T_LINK);

                    if(SessionItem *linkItem = links.at(index.row())) {
                        return linkItem->getItemValue(FitParameterLinkItem::P_LINK);
                    }
                } else {
                    return QVariant();
                }
            }
            if (index.column() == 0)
                return item->itemName();
            else
                return item->getItemValue(m_columnNames.value(index.column()));
        }
    }
    return QVariant();
}

bool FitParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole && index.column() > 0 && index.column() < 5) {
            item->setItemValue(m_columnNames.value(index.column()), value);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;

}

//bool FitParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!index.isValid())
//        return false;
//    if (SessionItem *item = itemForIndex(index)) {
//        if (role == Qt::EditRole && index.column() > 0 && index.column() < 5) {
//            item->setItemValue(m_columnNames->value(index.column()), value);
//            emit dataChanged(index, index);
//            return true;
//        }
//    }
//    return false;
//}

QVariant FitParameterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames.value(section);
    }
    return QVariant();
}

int FitParameterModel::rowCount(const QModelIndex &parent) const
{
//    if (parent.isValid() && parent.column() != 0)
//        return 0;
//    SessionItem *parent_item = itemForIndex(parent);
//    return parent_item ? parent_item->rowCount() : 0;
    if(SessionItem *parentItem = itemForIndex(parent)) {
        if(parentItem->modelType() == Constants::FitParameterType) {

            return parentItem->getItems(FitParameterItem::T_LINK).size();
        }
    }
    return SessionModel::rowCount(parent);
}

int FitParameterModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return 5;

}
