// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTuningModel.cpp
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
#include "FitParameterHelper.h"
#include "ParameterTreeItems.h"
#include "SessionModel.h"
#include <QDebug>
#include <QMimeData>

ParameterTuningModel::ParameterTuningModel(QObject *parent)
    : FilterPropertyProxy(2, parent)
{

}

Qt::ItemFlags ParameterTuningModel::flags(const QModelIndex &proxyIndex) const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;

    QModelIndex sourceIndex = toSourceIndex(proxyIndex);
    if(sourceIndex.isValid()) {
        if (sourceIndex.column() == SessionModel::ITEM_VALUE) result |= Qt::ItemIsEditable;

        const QString modelType = sourceIndex.data(SessionModel::ModelTypeRole).toString();
        if(modelType == Constants::ParameterType) {
            if(ParameterItem *parameterItem = getParameterItem(proxyIndex)) {
                if(parameterItem->isFittable())
                    result |= Qt::ItemIsDragEnabled;
            }
        }
    }

    return result;
}

QMimeData *ParameterTuningModel::mimeData(const QModelIndexList &proxyIndexes) const
{
    qDebug() << "ParameterTuningModel::mimeData" << proxyIndexes;
    QMimeData *mimeData = new QMimeData();

    foreach(QModelIndex proxyIndex, proxyIndexes) {
        if(ParameterItem *parameterItem = getParameterItem(proxyIndex)) {
            QString path = FitParameterHelper::getParameterItemPath(parameterItem);
            mimeData->setData(SessionXML::LinkMimeType, path.toLatin1());
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
