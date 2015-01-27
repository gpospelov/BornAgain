// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/mainwindow/StyledToolBar.h
//! @brief     Defines class StyledToolBar
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STYLEDTOOLBAR_H
#define STYLEDTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar on top of SampleView window
class BA_CORE_API_ StyledToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit StyledToolBar(QWidget *parent = 0);

};


#endif // STYLEDTOOLBAR_H

