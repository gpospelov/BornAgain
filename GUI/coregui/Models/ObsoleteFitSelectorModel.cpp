// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ObsoleteFitSelectorModel.cpp
//! @brief     Implements class ObsoleteFitSelectorModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteFitSelectorModel.h"
#include "ObsoleteFitParameterWidget.h"
#include <QStandardItem>
#include <QMimeData>
#include <QModelIndexList>

QMimeData *ObsoleteFitSelectorModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QModelIndex index = indexes.first();
    if (index.isValid()) {
        QString path = getPathFromIndex(index);
        path = path.append("#%1").arg(itemFromIndex(index.sibling(index.row(), 1))
                                      ->data(Qt::EditRole).toDouble());
        mimeData->setData(ObsoleteFitParameterWidget::MIME_TYPE, path.toLatin1());
    }
    return mimeData;
}

QString ObsoleteFitSelectorModel::getPathFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        QStringList namePath;
        QStandardItem *cur = itemFromIndex(index);
        while (cur) {
            namePath << cur->text();
            cur = cur->parent();
        }
        std::reverse(namePath.begin(), namePath.end());
        return namePath.join("/");
    }
    return QString();
}

QStandardItem *ObsoleteFitSelectorModel::getItemFromPath(const QString &path)
{
    QStringList parts = path.split("/");
    QStandardItem *t = invisibleRootItem();
    for(int i = 0; i < parts.length(); i++) {
        for (int j = 0; j < t->rowCount(); j++) {
            if (t->child(j,0)->text() == parts[i]) {
                t = t->child(j,0);
                break;
            }
        }
    }
    return t;
}
