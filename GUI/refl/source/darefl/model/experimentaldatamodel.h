// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_MODEL_EXPERIMENTALDATAMODEL_H
#define DAREFL_MODEL_EXPERIMENTALDATAMODEL_H

#include <darefl/darefl_export.h>
#include <mvvm/model/sessionmodel.h>
#include <vector>

namespace ModelView {
class SessionItem;
class GraphItem;
class GraphViewportItem;
} // namespace ModelView

namespace DaRefl {

class CanvasContainerItem;
class ExperimentalDataContainerItem;
class CanvasItem;
struct GraphImportData;

//! The model to store imported reflectometry data.

class DAREFLCORE_EXPORT ExperimentalDataModel : public ModelView::SessionModel {
public:
    ExperimentalDataModel(std::shared_ptr<ModelView::ItemPool> pool = {});

    CanvasContainerItem* canvasContainer() const;

    ExperimentalDataContainerItem* dataContainer() const;

    CanvasItem* addCanvas();

    ModelView::GraphItem* addGraph(const GraphImportData& graph_data, CanvasItem& target_canvas);

    void removeGraph(ModelView::GraphItem& graph);

    void removeCanvas(CanvasItem& canvas);

    void mergeCanvases(const std::vector<CanvasItem*>& canvases);

private:
    void init_model();
};

} // namespace DaRefl

#endif // DAREFL_MODEL_EXPERIMENTALDATAMODEL_H
