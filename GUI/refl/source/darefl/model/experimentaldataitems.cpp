// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/item_constants.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>

using namespace ModelView;

namespace DaRefl {

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

} // namespace DaRefl
