// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelPath.h
//! @brief     Defines ModelPath namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MODELPATH_H
#define MODELPATH_H

#include "WinDllMacros.h"
#include "ParameterTranslators.h"
#include <memory>
#include <vector>

class SessionItem;
class QModelIndex;
class SessionModel;

namespace ModelPath
{
    QString getPathFromIndex(const QModelIndex &index);

    QModelIndex getIndexFromPath(const SessionModel *model, const QString &path);

    SessionItem* getItemFromPath(const QString &relPath, const SessionItem* parent);

    bool isValidItem(SessionModel *model, SessionItem *item, const QModelIndex &parent);

    bool isTranslatable(const SessionItem *item, const QString &par_name);

    const SessionItem *ancestor(const SessionItem *item, const QString& requiredModelType);

    QString itemPathTranslation(const SessionItem& item, const SessionItem* topItem=0);
}

#endif // MODELPATH_H namespace
