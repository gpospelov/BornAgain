// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitModel.cpp
//! @brief     Implements class FitModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterModel.h"
#include "SessionModel.h"
#include "FitModel.h"
#include "FitParameterItems.h"
#include "FitParameterWidget.h"

#include <QMimeData>



FitParameterModel::FitParameterModel(FitModel *fitmodel, QWidget *parent)
    : SessionModel("FitParameterModel", parent)
    , m_columnNames(new QMap<int, QString>())
{
    setRootItem(fitmodel->itemForIndex(QModelIndex())->
            getChildOfType(Constants::FitParameterContainerType));
    setMaxColumns(5);
    m_columnNames->insert(0, FitParameterItem::P_NAME);
    m_columnNames->insert(1, FitParameterItem::P_USE);
    m_columnNames->insert(3, FitParameterItem::P_MIN);
    m_columnNames->insert(2, FitParameterItem::P_INIT);
    m_columnNames->insert(4, FitParameterItem::P_MAX);
}

FitParameterModel::~FitParameterModel()
{
    setRootItem(0);
    delete m_columnNames;
}

ParameterizedItem *FitParameterModel::addParameter()
{
    return insertNewItem(Constants::FitParameterType, indexOfItem(itemForIndex(QModelIndex())));
}

QModelIndex FitParameterModel::itemForLink(const QString &link) const
{
    for (int i=0; i<rowCount(QModelIndex()); i++){
        int rowcount = rowCount(index(i,0,QModelIndex()));
        for (int j = 0; j < rowcount; j++) {
            QModelIndex curIndex = index(j,0,index(i,0,QModelIndex()));
            QString value = itemForIndex(curIndex)
                    ->getRegisteredProperty(FitParameterLinkItem::P_LINK).toString();
            if (value == link)
                return curIndex;
        }
    }
    return QModelIndex();
}

Qt::ItemFlags FitParameterModel::flags(const QModelIndex & index) const
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

QStringList FitParameterModel::mimeTypes() const
{
    QStringList types;
    types << FitParameterWidget::MIME_TYPE;
    return types;
}

bool FitParameterModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                                        int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);
    if (column > 0)
        return false;
    QString link = QString::fromLatin1(data->data(FitParameterWidget::MIME_TYPE)).split("#")[0];
    QModelIndex cur = itemForLink(link);
    return !cur.isValid();
}

Qt::DropActions FitParameterModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool FitParameterModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                     int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (column > 0) return true;
    QStringList parts = QString::fromLatin1(data->data(FitParameterWidget::MIME_TYPE))
            .split("#");
    if (parts.size() != 2) return true;
    QModelIndex cur = parent;
    if (!parent.isValid()) {
        auto newlink = addParameter();
        double value = parts[1].toDouble();
        newlink->setRegisteredProperty(FitParameterItem::P_INIT, value);
        cur = indexOfItem(newlink);
    }
    auto link = insertNewItem(Constants::FitParameterLinkType, cur, row);
    if (link) link->setRegisteredProperty(FitParameterLinkItem::P_LINK, parts[0]);
    emit dataChanged(cur, cur);
    return true;
}

QVariant FitParameterModel::data(const QModelIndex & index, int role) const
{
    if ( !index.isValid() || index.column() < 0 || index.column() >= 5) {
        return QVariant();
    }
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (item->parent() != itemForIndex(QModelIndex()))
            {
                if (index.column() == 0)
                    return item->getRegisteredProperty(FitParameterLinkItem::P_LINK);
                else
                    return QVariant();
            }
            if (index.column() == 0)
                return item->itemName();
            else
                return item->getRegisteredProperty(m_columnNames->value(index.column()));
        }
    }
    return QVariant();
}

bool FitParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole && index.column() > 0 && index.column() < 5) {
            item->setRegisteredProperty(m_columnNames->value(index.column()), value);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant FitParameterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames->value(section);
    }
    return QVariant();
}
