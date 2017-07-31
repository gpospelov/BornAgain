// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionDecorationModel.h
//! @brief     Defines class SessionDecorationModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONDECORATIONMODEL_H
#define SESSIONDECORATIONMODEL_H

#include "WinDllMacros.h"
#include <QIdentityProxyModel>

class SessionModel;
class SessionItem;

//! Provides decorations (text color, icons, etc) for SessionModel in SessionModelView context.
//! It is implemented as identity proxy model, so it has one-to-one data structure as in
//! source SessionModel.

class BA_CORE_API_ SessionDecorationModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    SessionDecorationModel(QObject* parent);

    void setSessionModel(SessionModel* model);

    QVariant data(const QModelIndex &index, int role) const;

private:
    QVariant createIcon(const QModelIndex& index) const;

    SessionModel *m_model;
};

#endif
