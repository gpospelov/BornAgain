// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/StyledToolBar.cpp
//! @brief     Implements class StyledToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "StyledToolBar.h"
#include <QLabel>
#include <QStyle>

namespace {
const int fixed_height = 25;
}

StyledToolBar::StyledToolBar(QWidget *parent)
    : QToolBar(parent)
{
//    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setMovable(false);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setContentsMargins(0,0,0,0);
}

void StyledToolBar::addStyledSeparator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

void StyledToolBar::addStyledExpand()
{
    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    addWidget(empty);
}

int StyledToolBar::minimumHeight() const
{
    return fixed_height;
}
