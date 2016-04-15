// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FilterPropertyProxy.cpp
//! @brief     Implements class FilterPropertyProxy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FilterPropertyProxy.h"
#include "SessionModel.h"

int FilterPropertyProxy::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columns;
}

QModelIndex FilterPropertyProxy::toSourceIndex(QModelIndex index)
{
    FilterPropertyProxy *proxy = dynamic_cast<FilterPropertyProxy*>(const_cast<QAbstractItemModel*>(index.model()));
    if (proxy)
        return proxy->mapToSource(index);
    return index;
}

bool FilterPropertyProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 1, sourceParent);
    if (!sourceParent.isValid())
        return true;
    const QString modelType = index.data(SessionModel::ModelTypeRole).toString();
    if (modelType == Constants::PropertyType || modelType == Constants::GroupItemType || modelType == Constants::VectorType)
        return false;

    return true;//!sourceModel()->data(index, Qt::DisplayRole).isValid();
}
