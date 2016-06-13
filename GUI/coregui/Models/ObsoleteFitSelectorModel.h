// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ObsoleteFitSelectorModel.h
//! @brief     Declares class ObsoleteFitSelectorModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEFITSELECTORMODEL_H
#define OBSOLETEFITSELECTORMODEL_H

#include "WinDllMacros.h"
#include <QStandardItemModel>

class QMimeData;
class QStandardItem;

class BA_CORE_API_ ObsoleteFitSelectorModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QString getPathFromIndex(const QModelIndex &index) const;
    QStandardItem *getItemFromPath(const QString &path);
};

#endif
