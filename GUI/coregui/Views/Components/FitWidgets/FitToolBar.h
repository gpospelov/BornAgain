// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/FitWidgets/FitToolBar.h
//! @brief     Defines class FitToolBar
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITTOOLBAR_H
#define FITTOOLBAR_H

#include "WinDllMacros.h"
#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;


class BA_CORE_API_ FitToolBar : public QToolBar
{
    Q_OBJECT

public:
    explicit FitToolBar(QWidget *parent = 0);

};


#endif // SIMULATIONTOOLBAR_H
