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

QMimeData *ParameterTuningModel::mimeData(const QModelIndexList &proxyIndexes) const
{
    qDebug() << "ParameterTuningModel::mimeData" << proxyIndexes;
    QMimeData *mimeData = new QMimeData();

    foreach(QModelIndex proxyIndex, proxyIndexes) {
        if(ParameterItem *parameterItem = getParameterItem(proxyIndex)) {
            QString path = FitModelHelper::getParameterItemPath(parameterItem);
            mimeData->setData(FitParameterAbsModel::MIME_TYPE, path.toLatin1());
            qDebug() << "       FilterPropertyProxy::mimeData" << path;
            break;
        }
    }
    return mimeData;
}

//! Returns ParameterItem from given proxy index

ParameterItem *ParameterTuningModel::getParameterItem(const QModelIndex &proxyIndex) const
{
    SessionModel *sessionModel = dynamic_cast<SessionModel *>(sourceModel());
    Q_ASSERT(sessionModel);

    QModelIndex sourceIndex = toSourceIndex(proxyIndex);
    if(sourceIndex.column() == 0) {
        return dynamic_cast<ParameterItem *>(sessionModel->itemForIndex(sourceIndex));
    }
    return nullptr;
}
