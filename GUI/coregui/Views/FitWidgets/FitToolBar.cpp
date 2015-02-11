// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitToolBar.cpp
//! @brief     Implements class FitToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitToolBar.h"
#include "styledbar.h"

#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <iostream>


FitToolBar::FitToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    setContentsMargins(0,0,0,0);

    this->addAction(new QAction(0));

}
