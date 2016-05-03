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
#include "ParameterTreeItems.h"
#include "ModelPath.h"
#include <QDebug>

FitParameterModel::FitParameterModel(SessionItem *fitParContainer, QObject *parent)
    : SessionModel(QString("FitParameterModel"), parent)
{
    setRootItem(fitParContainer);
    m_columnNames.insert(0, "Name");
    m_columnNames.insert(1, FitParameterItem::P_USE);
    m_columnNames.insert(3, FitParameterItem::P_MIN);
    m_columnNames.insert(2, FitParameterItem::P_START_VALUE);
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

                    if(links.size()) {
                        if(SessionItem *linkItem = links.at(index.row())) {
                            return linkItem->getItemValue(FitParameterLinkItem::P_LINK);
                        }
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

QVariant FitParameterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_columnNames.value(section);
    }
    return QVariant();
}

int FitParameterModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
        return 0;

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
    if(!parent.isValid())
        return 0;

    if (parent.isValid() && parent.column() != 0)
        return 0;
    return 5;

}

//! Creates fit parameter from given ParameterItem, sets starting value to the value
//! of ParameterItem, copy link.
void FitParameterModel::createFitParameter(ParameterItem *parameterItem)
{
    SessionItem *fitPar = getFitParContainer()->model()->insertNewItem(Constants::FitParameterType, getFitParContainer()->index());
    fitPar->setDisplayName(QStringLiteral("par"));
    Q_ASSERT(fitPar);
    if(parameterItem) {
        fitPar->setItemValue(FitParameterItem::P_START_VALUE, parameterItem->value());
        SessionItem *link = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
        link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));
    }
    emit layoutChanged();

}

//! Removes link to given parameterItem from fit parameters
void FitParameterModel::removeFromFitParameters(ParameterItem *parameterItem)
{
    FitParameterItem *fitParItem = getFitParameterItem(parameterItem);
    if(fitParItem) {
        foreach(SessionItem *linkItem, fitParItem->getItems(FitParameterItem::T_LINK)) {
            if(getParameterItemPath(parameterItem) == linkItem->getItemValue(FitParameterLinkItem::P_LINK)) {
                fitParItem->model()->removeRow(linkItem->index().row(), linkItem->index().parent());
                break;
            }
        }
        emit layoutChanged();
    }
}

//! Adds given parameterItem to the existing fit parameter with display name fitParName.
//! If parameterItem is already linked with another fitParameter, it will be relinked
void FitParameterModel::addToFitParameter(ParameterItem *parameterItem, const QString &fitParName)
{
    removeFromFitParameters(parameterItem);
    foreach(SessionItem *fitPar, getFitParContainer()->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if(fitPar->displayName() == fitParName) {
            SessionItem *link = fitPar->model()->insertNewItem(Constants::FitParameterLinkType, fitPar->index());
            link->setItemValue(FitParameterLinkItem::P_LINK, getParameterItemPath(parameterItem));
            emit layoutChanged();
            break;
        }
    }
}

//! Returns fFitParameterItem corresponding to given ParameterItem
FitParameterItem *FitParameterModel::getFitParameterItem(ParameterItem *parameterItem)
{
    return getFitParContainer()->getFitParameterItem(getParameterItemPath(parameterItem));
}

FitParameterContainerItem *FitParameterModel::getFitParContainer()
{
    FitParameterContainerItem *result = dynamic_cast<FitParameterContainerItem *>(rootItem());
    Q_ASSERT(result);
    return result;
}

//! Returns list of fit parameter display names
QStringList FitParameterModel::getFitParameterNames()
{
    QStringList result;

    foreach(SessionItem *item, getFitParContainer()->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        result.append(item->displayName());
    }

    return result;
}

//! return path to given item in the ParameterTreeContainer
QString FitParameterModel::getParameterItemPath(ParameterItem *parameterItem)
{
    QString result = ModelPath::getPathFromIndex(parameterItem->index());
//    int containerEnd = result.indexOf(QStringLiteral("Container/")) + 10;
    QString containerPrefix = Constants::ParameterContainerType+"/";
    int containerEnd = result.indexOf(containerPrefix) + containerPrefix.size();
    result = result.mid(containerEnd);
    return result;
}

