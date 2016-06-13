// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ObsoleteFitParameterModel.cpp
//! @brief     Implements class FitParameterModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteFitParameterModel.h"
#include "SessionModel.h"
#include "ObsoleteFitModel.h"
#include "ObsoleteFitParameterItems.h"
#include "ObsoleteFitParameterWidget.h"

#include <QMimeData>



ObsoleteFitParameterModel::ObsoleteFitParameterModel(ObsoleteFitModel *fitmodel, QWidget *parent)
    : SessionModel("FitParameterModel", parent)
    , m_columnNames(new QMap<int, QString>())
{
    setRootItem(fitmodel->itemForIndex(QModelIndex())->
            getChildOfType(Constants::ObsoleteFitParameterContainerType));
    m_columnNames->insert(0, "FitParameterItem::OBSOLETE_P_NAME");
    m_columnNames->insert(1, ObsoleteFitParameterItem::P_USE);
    m_columnNames->insert(3, ObsoleteFitParameterItem::P_MIN);
    m_columnNames->insert(2, ObsoleteFitParameterItem::P_INIT);
    m_columnNames->insert(4, ObsoleteFitParameterItem::P_MAX);
}

ObsoleteFitParameterModel::~ObsoleteFitParameterModel()
{
    setRootItem(0);
    delete m_columnNames;
}

SessionItem *ObsoleteFitParameterModel::addParameter()
{
    return insertNewItem(Constants::ObsoleteFitParameterType, indexOfItem(itemForIndex(QModelIndex())));
}

QModelIndex ObsoleteFitParameterModel::itemForLink(const QString &link) const
{
    for (int i=0; i<rowCount(QModelIndex()); i++){
        int rowcount = rowCount(index(i,0,QModelIndex()));
        for (int j = 0; j < rowcount; j++) {
            QModelIndex curIndex = index(j,0,index(i,0,QModelIndex()));
            QString value = itemForIndex(curIndex)
                    ->getItemValue(ObsoleteFitParameterLinkItem::P_LINK).toString();
            if (value == link)
                return curIndex;
        }
    }
    return QModelIndex();
}

Qt::ItemFlags ObsoleteFitParameterModel::flags(const QModelIndex & index) const
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

QStringList ObsoleteFitParameterModel::mimeTypes() const
{
    QStringList types;
    types << ObsoleteFitParameterWidget::MIME_TYPE;
    return types;
}

bool ObsoleteFitParameterModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                                        int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);
    if (column > 0)
        return false;
    QString link = QString::fromLatin1(data->data(ObsoleteFitParameterWidget::MIME_TYPE)).split("#")[0];
    QModelIndex cur = itemForLink(link);
    return !cur.isValid();
}

Qt::DropActions ObsoleteFitParameterModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool ObsoleteFitParameterModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                     int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (column > 0) return true;
    QStringList parts = QString::fromLatin1(data->data(ObsoleteFitParameterWidget::MIME_TYPE))
            .split("#");
    if (parts.size() != 2) return true;
    QModelIndex cur = parent;
    if (!parent.isValid()) {
        auto newlink = addParameter();
        double value = parts[1].toDouble();
        newlink->setItemValue(ObsoleteFitParameterItem::P_INIT, value);
        cur = indexOfItem(newlink);
    }
    auto link = insertNewItem(Constants::ObsoleteFitParameterLinkType, cur, row);
    if (link) link->setItemValue(ObsoleteFitParameterLinkItem::P_LINK, parts[0]);
    emit dataChanged(cur, cur);
    return true;
}

QVariant ObsoleteFitParameterModel::data(const QModelIndex & index, int role) const
{
    if ( !index.isValid() || index.column() < 0 || index.column() >= 5) {
        return QVariant();
    }
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            if (item->parent() != itemForIndex(QModelIndex()))
            {
                if (index.column() == 0)
                    return item->getItemValue(ObsoleteFitParameterLinkItem::P_LINK);
                else
                    return QVariant();
            }
            if (index.column() == 0)
                return item->itemName();
            else
                return item->getItemValue(m_columnNames->value(index.column()));
        }
    }
    return QVariant();
}

bool ObsoleteFitParameterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (SessionItem *item = itemForIndex(index)) {
        if (role == Qt::EditRole && index.column() > 0 && index.column() < 5) {
            item->setItemValue(m_columnNames->value(index.column()), value);
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant ObsoleteFitParameterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames->value(section);
    }
    return QVariant();
}
