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
#include "FitParameterAbsModel.h"
#include "ParameterTreeItems.h"
#include "FitModelHelper.h"
#include <QMimeData>
#include <QDebug>

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

QMimeData *FilterPropertyProxy::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "FitParameterAbsModel::mimeData" << indexes;
    QMimeData *mimeData = new QMimeData();

    foreach(QModelIndex proxyIndex, indexes) {
        QModelIndex index = FilterPropertyProxy::toSourceIndex(proxyIndex);
        if(index.column() != 0)
            continue;

        SessionModel *sessionModel = dynamic_cast<SessionModel *>(sourceModel());
        Q_ASSERT(sessionModel);
        if (ParameterItem *parameterItem
            = dynamic_cast<ParameterItem *>(sessionModel->itemForIndex(index))) {
            QString path = FitModelHelper::getParameterItemPath(parameterItem);
            mimeData->setData(FitParameterAbsModel::MIME_TYPE, path.toLatin1());
            qDebug() << "       FilterPropertyProxy::mimeData" << path;
            break;
        }
    }

//    QModelIndex index = toSourceIndex(indexes.first());
//    if (index.isValid()) {
//        if(SessionItem *item = static_cast<SessionItem *>(index.internalPointer())) {
//            QString path = item->value().toString();
//            mimeData->setData(FitParameterAbsModel::MIME_TYPE, path.toLatin1());
//            qDebug() << "       FilterPropertyProxy::mimeData" << path;

//        }
////        QString path = getPathFromIndex(index);
////        path = path.append("#%1").arg(itemFromIndex(index.sibling(index.row(), 1))
////                                      ->data(Qt::EditRole).toDouble());
//    }
    return mimeData;

}

//QStringList FilterPropertyProxy::mimeTypes() const
//{
//    QStringList types;
//    types << FitParameterAbsModel::MIME_TYPE;
//    return types;

//}

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
