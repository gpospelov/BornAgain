// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceToolBar.cpp
//! @brief     Implements class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpaceToolBar.h"
#include "mainwindow_constants.h"

RealSpaceToolBar::RealSpaceToolBar(QWidget* parent)
    : StyledToolBar(parent)
{
    setMinimumSize(Constants::styled_toolbar_height, Constants::styled_toolbar_height);

}
