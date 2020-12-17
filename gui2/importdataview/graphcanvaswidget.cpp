//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/importdataview/graphcanvaswidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/importdataview/graphcanvaswidget.h"
#include "gui2/model/experimentaldataitems.h"
#include "mvvm/plotting/graphcanvas.h"
#include <QVBoxLayout>

namespace gui2 {

GraphCanvasWidget::GraphCanvasWidget(QWidget* parent)
    : QWidget(parent), m_graphCanvas(new ModelView::GraphCanvas) {
    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_graphCanvas);
    layout->setContentsMargins(0, 5, 5, 5);
}

void GraphCanvasWidget::setItem(CanvasItem* canvas_item) {
    m_graphCanvas->setItem(canvas_item);
}

void GraphCanvasWidget::updateViewport() {
    m_graphCanvas->setViewportToContent();
}

} // namespace gui2
