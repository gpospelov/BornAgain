// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/mainwindow/StyledToolBar.cpp
//! @brief     Implements class StyledToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "StyledToolBar.h"
#include <QLabel>
#include <QStyle>

namespace {
const int fixed_height = 25;
}

StyledToolBar::StyledToolBar(QWidget* parent) : QToolBar(parent)
{
    setMovable(false);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setContentsMargins(0, 0, 0, 0);
}

void StyledToolBar::addStyledSeparator()
{
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
}

//! Width of the spacing between buttons

void StyledToolBar::addSpacing(int width)
{
    QString space;
    space.fill(' ', width);
    addWidget(new QLabel(space));
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

void StyledToolBar::contextMenuEvent(QContextMenuEvent*)
{
    // Context menu reimplemented to suppress the default one
}
