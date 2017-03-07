// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceActions.h
//! @brief     Defines class RealSpaceActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACEACTIONS_H
#define REALSPACEACTIONS_H

#include "WinDllMacros.h"
#include <QObject>

//! Collection of actions for RealSpaceWidget.

class BA_CORE_API_ RealSpaceActions : public QObject
{
    Q_OBJECT

public:
    RealSpaceActions(QObject* parent = 0);
};

#endif // REALSPACEACTIONS_H
