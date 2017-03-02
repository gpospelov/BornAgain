// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceScene.h
//! @brief     Defines class RealSpaceScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACESCENE_H
#define REALSPACESCENE_H

#include "WinDllMacros.h"
#include <QObject>

//! Provides 3D object generation logic for RealSpaceWidget.

class BA_CORE_API_ RealSpaceScene : public QObject
{
    Q_OBJECT

public:
    RealSpaceScene(QObject* parent = 0);
};

#endif // REALSPACESCENE_H
