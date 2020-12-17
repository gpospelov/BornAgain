//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/sldeditor/sldviewwidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/sldviewwidget.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/jobmodel.h"
#include "gui2/sldeditor/graphicsscene.h"
#include "gui2/sldeditor/sldelementcontroller.h"
#include <QResizeEvent>

namespace gui2 {

//! The constructor
SLDViewWidget::SLDViewWidget(QWidget* parent) : QGraphicsView(parent) {
    GraphicsScene* scene_item = new GraphicsScene(parent = this);
    setScene(scene_item);
    setRenderHints(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContentsMargins(0, 0, 0, 0);
}

//! The destructor
SLDViewWidget::~SLDViewWidget() = default;

void SLDViewWidget::setModels(ApplicationModels* models) {
    m_sld_controller = std::make_unique<SLDElementController>(
        models->materialModel(), models->sampleModel(), models->sldViewModel(), nullptr);
    m_sld_controller->setScene(dynamic_cast<GraphicsScene*>(scene()));
    dynamic_cast<GraphicsScene*>(scene())->setItem(models->jobModel()->sldViewport());
}

//! Resize event management
void SLDViewWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    scene_item->update_size(event->size());
}

} // namespace gui2
