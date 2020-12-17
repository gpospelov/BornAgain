//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/model/experimentaldataitems.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/item_constants.h"
#include "mvvm/standarditems/axisitems.h"
#include "mvvm/standarditems/data1ditem.h"

using namespace ModelView;

namespace gui2 {

CanvasItem::CanvasItem() : GraphViewportItem(Constants::CanvasItemType) {
    yAxis()->setProperty(ViewportAxisItem::P_IS_LOG, true);
    setData(std::string(""));
}

std::pair<double, double> CanvasItem::data_yaxis_range() const {
    auto [ymin, ymax] = GraphViewportItem::data_yaxis_range();
    return {ymin, ymax * 2.0};
}

CanvasContainerItem::CanvasContainerItem() : ContainerItem(Constants::CanvasContainerItemType) {}

std::vector<CanvasItem*> CanvasContainerItem::canvasItems() const {
    return items<CanvasItem>(T_ITEMS);
}

ExperimentalDataContainerItem::ExperimentalDataContainerItem()
    : ContainerItem(Constants::ExperimentalDataContainerItemType) {}

std::vector<Data1DItem*> ExperimentalDataContainerItem::dataItems() const {
    return items<ModelView::Data1DItem>(T_ITEMS);
}

} // namespace gui2
