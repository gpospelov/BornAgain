//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/jobmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/jobmodel.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/jobitem.h"
#include "gui2/quicksimeditor/quicksim_types.h"
#include "mvvm/model/itemcatalogue.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data1ditem.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/standarditems/graphviewportitem.h"

using namespace ModelView;

namespace gui2 {

namespace {

std::unique_ptr<ItemCatalogue> CreateItemCatalogue() {
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<JobItem>();
    result->registerItem<CanvasItem>();
    result->registerItem<SLDCanvasItem>();
    return result;
}

} // namespace

JobModel::JobModel(std::shared_ptr<ItemPool> pool) : SessionModel("JobModel", pool) {
    setItemCatalogue(CreateItemCatalogue());
    insertItem<JobItem>();
}

GraphViewportItem* JobModel::sldViewport() const {
    return jobItem()->sldViewport();
}

CanvasItem* JobModel::specularViewport() const {
    return jobItem()->specularViewport();
}

GraphViewportItem* JobModel::diffViewport() const {
    return jobItem()->diffViewport();
}

void JobModel::updateReferenceGraph(const ModelView::GraphItem* graph) {
    jobItem()->updateReferenceGraph(graph);
}

//! Updates specular data in JobItem from simulation results.

void JobModel::updateSpecularData(const SimulationResult& data) {
    auto specularData = jobItem()->specularData();
    //    specularData->setAxis<ModelView::PointwiseAxisItem>(data.qvalues);
    specularData->item<PointwiseAxisItem>(Data1DItem::T_AXIS)->setParameters(data.qvalues);
    specularData->setValues(data.amplitudes);

    // updating difference graph
    jobItem()->updateDifferenceData();
}

//! Updates SLD profile data.

void JobModel::updateSLDProfile(const SLDProfile& data) {
    auto sldData = jobItem()->sldData();
    // sldData->setAxis<FixedBinAxisItem>(data.sld_real_values.size(), data.zmin, data.zmax);
    sldData->item<FixedBinAxisItem>(Data1DItem::T_AXIS)
        ->setParameters(data.sld_real_values.size(), data.zmin, data.zmax);
    sldData->setValues(data.sld_real_values);
}

JobItem* JobModel::jobItem() const {
    return Utils::TopItem<JobItem>(this);
}

} // namespace gui2
