// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FitSelectorModel.h
//! @brief     Defines class FitSelectorModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#ifndef FITSELECTORMODEL_H
#define FITSELECTORMODEL_H

#include "WinDllMacros.h"
#include <QStandardItemModel>

class QMimeData;
class QStandardItem;

class BA_CORE_API_ FitSelectorModel : public QStandardItemModel
{
    Q_OBJECT

public:
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    QString getPathFromIndex(const QModelIndex &index) const;
    QStandardItem *getItemFromPath(const QString &path);
};

#endif
