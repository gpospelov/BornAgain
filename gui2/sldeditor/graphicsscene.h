//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/graphicsscene.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_GRAPHICSSCENE_H
#define BORNAGAIN_GUI2_SLDEDITOR_GRAPHICSSCENE_H

#include "darefl_export.h"
#include <QGraphicsScene>
#include <memory>

namespace ModelView {
class GraphCanvas;
class SceneAdapterInterface;
class GraphViewportItem;
class CustomPlotProxyWidget;
} // namespace ModelView

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_GRAPHICSSCENE_H
