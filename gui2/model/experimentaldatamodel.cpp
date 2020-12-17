//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/experimentaldatamodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/experimentaldatamodel.h"
#include "gui2/importdataview/graphimportdata.h"
#include "gui2/model/experimentaldataitems.h"

#include "mvvm/model/itemcatalogue.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/containeritem.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/standarditems/graphviewportitem.h"

#include <algorithm>
#include <cmath>

using namespace ModelView;

namespace {

std::unique_ptr<ItemCatalogue> CreateItemCatalogue() {
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<gui2::CanvasItem>();
    result->registerItem<gui2::CanvasContainerItem>();
    result->registerItem<gui2::ExperimentalDataContainerItem>();
    return result;
}

} // namespace

namespace gui2 {

ExperimentalDataModel::ExperimentalDataModel(std::shared_ptr<ItemPool> pool)
    : SessionModel("ExperimentalDataModel", pool)

{
    init_model();
}

//! Returns the canvas container of the model.

CanvasContainerItem* ExperimentalDataModel::canvasContainer() const {
    return topItem<CanvasContainerItem>();
}

//! Returns the data container of the model.

ExperimentalDataContainerItem* ExperimentalDataModel::dataContainer() const {
    return topItem<ExperimentalDataContainerItem>();
}

CanvasItem* ExperimentalDataModel::addCanvas() {
    return insertItem<CanvasItem>(canvasContainer());
}

//! Adds graph to 'target_canvas' and returns the result.
//! Internally add Data1DItem object to ExperimentalDataContainerItem,
//! and set it to GraphItem.

ModelView::GraphItem* ExperimentalDataModel::addGraph(const GraphImportData& graph_data,
                                                      CanvasItem& target_canvas) {
    auto result = insertItem<GraphItem>(&target_canvas);

    auto data = insertItem<Data1DItem>(dataContainer());
    data->setAxis<PointwiseAxisItem>(graph_data.bin_centers);
    data->setValues(graph_data.bin_values);
    result->setDataItem(data);

    result->setData(graph_data.graph_description);

    return result;
}

//! Remove graph from the model. Underlying DataItem will be removed too.

void ExperimentalDataModel::removeGraph(GraphItem& graph) {
    auto dataItem = graph.dataItem();

    removeItem(graph.parent(), graph.tagRow());
    removeItem(dataItem->parent(), dataItem->tagRow());
}

//! Remove canvas with all its graphs.

void ExperimentalDataModel::removeCanvas(CanvasItem& canvas) {
    // Remove graph first. Use special method for that, since we want to remove underlying items.
    for (auto graph : canvas.graphItems())
        removeGraph(*graph);
    removeItem(canvas.parent(), canvas.tagRow());
}

//! Merge canvas from the vector. All graphs will be the children of the first canvas in the vector.
//! All other canvas will be emptied and deleted.

void ExperimentalDataModel::mergeCanvases(const std::vector<CanvasItem*>& canvases) {
    if (canvases.size() <= 1)
        return;

    CanvasItem* target = canvases.front();
    for (auto it = std::next(canvases.begin()); it < canvases.end(); ++it) {
        CanvasItem* source = (*it);
        for (auto graph : source->graphItems())
            moveItem(graph, target, {"", -1});
        removeItem(source->parent(), source->tagRow());
    }
}

void ExperimentalDataModel::init_model() {
    setItemCatalogue(CreateItemCatalogue());

    insertItem<ExperimentalDataContainerItem>(rootItem());
    insertItem<CanvasContainerItem>(rootItem());

    setUndoRedoEnabled(true);
}

} // namespace gui2
