// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_GRAPHICSSCENE_H
#define DAREFL_SLDEDITOR_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "darefl_export.h"
#include <memory>

namespace ModelView {
class GraphCanvas;
class SceneAdapterInterface;
class GraphViewportItem;
class CustomPlotProxyWidget;
} // namespace ModelView

namespace DaRefl {

class RegionOfInterestItem;

//! Custom graphics scene to show QCustomPlot with additional elements on top.
class DAREFLCORE_EXPORT GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    GraphicsScene(QObject* parent = nullptr);
    ~GraphicsScene() override;

    void setContext();
    void setItem(ModelView::GraphViewportItem* viewport_item);
    ModelView::GraphCanvas* graphCanvas() const;
    ModelView::SceneAdapterInterface* sceneAdapter() const;
    void update_size(const QSize& newSize);

private:
    void createPlotProxy(ModelView::GraphCanvas* plot_canvas);
    ModelView::CustomPlotProxyWidget* plot_proxy{nullptr};
    std::unique_ptr<ModelView::SceneAdapterInterface> scene_adapter;
    ModelView::GraphCanvas* graph_canvas{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_GRAPHICSSCENE_H
