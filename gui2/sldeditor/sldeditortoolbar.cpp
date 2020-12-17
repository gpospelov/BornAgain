//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/sldeditortoolbar.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/sldeditortoolbar.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/resources/resources.h"
#include "gui2/sldeditor/sldeditoractions.h"
#include <QAction>
#include <QToolButton>

namespace gui2 {

SLDEditorToolBar::SLDEditorToolBar(SLDEditorActions*, QWidget* parent) : QToolBar(parent) {
    StyleUtils::SetToolBarStyleTextBesides(this);

    auto reset_view = new QToolButton;
    reset_view->setToolTip("Set axes to default range.");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    addWidget(reset_view);
    connect(reset_view, &QToolButton::clicked, [this]() { resetViewport(); });
}

} // namespace gui2
