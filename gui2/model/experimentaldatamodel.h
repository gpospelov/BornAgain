//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/experimentaldatamodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_EXPERIMENTALDATAMODEL_H
#define BORNAGAIN_GUI2_MODEL_EXPERIMENTALDATAMODEL_H

#include "darefl_export.h"
#include "mvvm/model/sessionmodel.h"
#include <vector>

namespace ModelView {
class SessionItem;
class GraphItem;
class GraphViewportItem;
} // namespace ModelView

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_EXPERIMENTALDATAMODEL_H
