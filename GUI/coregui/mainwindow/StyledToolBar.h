// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/StyledToolBar.h
//! @brief     Declares class StyledToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef STYLEDTOOLBAR_H
#define STYLEDTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! The StyledToolBar class represents our standard narrow toolbar with the height 24 pixels.

class BA_CORE_API_ StyledToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit StyledToolBar(QWidget *parent = 0);
    void addStyledSeparator();
    void addStyledExpand();
};

#endif
