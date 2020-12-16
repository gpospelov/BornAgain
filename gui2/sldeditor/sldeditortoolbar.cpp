// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/sldeditor/sldeditortoolbar.h"
#include "gui2/mainwindow/styleutils.h"
#include "gui2/resources/resources.h"
#include "gui2/sldeditor/sldeditoractions.h"
#include <QAction>
#include <QToolButton>

namespace DaRefl {

SLDEditorToolBar::SLDEditorToolBar(SLDEditorActions*, QWidget* parent) : QToolBar(parent) {
    StyleUtils::SetToolBarStyleTextBesides(this);

    auto reset_view = new QToolButton;
    reset_view->setToolTip("Set axes to default range.");
    reset_view->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    addWidget(reset_view);
    connect(reset_view, &QToolButton::clicked, [this]() { resetViewport(); });
}

} // namespace DaRefl
