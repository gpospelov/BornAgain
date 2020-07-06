// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeActions.h
//! @brief     Defines class ComponentTreeActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COMPONENTREEACTIONS_H
#define COMPONENTREEACTIONS_H

#include "Wrap/WinDllMacros.h"
#include <QObject>

class SessionItem;

//! Additional action for ComponentTreeView.

class BA_CORE_API_ ComponentTreeActions : public QObject
{
    Q_OBJECT
public:
    ComponentTreeActions(QObject* parent = nullptr);

public slots:
    void onCustomContextMenuRequested(const QPoint& point, SessionItem& item);
};

#endif // COMPONENTREEACTIONS_H
