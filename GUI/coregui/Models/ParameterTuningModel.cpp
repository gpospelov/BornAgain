// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ParameterTuningModel.cpp
//! @brief     Implements class ParameterTuningModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParameterTuningModel.h"
#include "FitParameterItems.h"
#include "FitParameterAbsModel.h"
#include "FitModelHelper.h"
#include "SessionModel.h"
#include "ParameterTreeItems.h"
#include <QDebug>
#include <QMimeData>

ParameterTuningModel::ParameterTuningModel(QObject *parent)
    : FilterPropertyProxy(2, parent)
{

}

QMimeData *ParameterTuningModel::mimeData(const QModelIndexList &indexes) const
{
    qDebug() << "ParameterTuningModel::mimeData" << indexes;
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
