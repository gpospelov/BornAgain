// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceView.h
//! @brief     Defines class RealSpaceView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALSPACEVIEW_H
#define REALSPACEVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

namespace ba3d { class Widget3D;}

//! Contains 3D view.

class BA_CORE_API_ RealSpaceView : public QWidget
{
    Q_OBJECT

public:
    RealSpaceView(QWidget* parent = 0);

private:
    ba3d::Widget3D* m_3dview;
};

#endif // REALSPACEVIEW_H
