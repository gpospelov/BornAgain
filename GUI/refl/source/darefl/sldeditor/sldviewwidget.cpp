// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QResizeEvent>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/jobmodel.h>
#include <darefl/sldeditor/graphicsscene.h>
#include <darefl/sldeditor/sldelementcontroller.h>
#include <darefl/sldeditor/sldviewwidget.h>

namespace DaRefl
{

//! The constructor
SLDViewWidget::SLDViewWidget(QWidget* parent) : QGraphicsView(parent)
{
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

void SLDViewWidget::setModels(ApplicationModels* models)
{
    m_sld_controller = std::make_unique<SLDElementController>(
        models->materialModel(), models->sampleModel(), models->sldViewModel(), nullptr);
    m_sld_controller->setScene(dynamic_cast<GraphicsScene*>(scene()));
    dynamic_cast<GraphicsScene*>(scene())->setItem(models->jobModel()->sldViewport());
}

//! Resize event management
void SLDViewWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    GraphicsScene* scene_item = static_cast<GraphicsScene*>(scene());
    scene_item->update_size(event->size());
}

} // namespace DaRefl
