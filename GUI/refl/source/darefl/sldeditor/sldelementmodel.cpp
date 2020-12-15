// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/sldeditor/layerelementitem.h>
#include <darefl/sldeditor/sldelementmodel.h>

#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/reallimits.h>

using namespace ModelView;

namespace DaRefl {

namespace {
std::unique_ptr<ItemCatalogue> CreateItemCatalogue() {
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<LayerElementItem>();
    return result;
}

} // namespace

//! Contructor
SLDElementModel::SLDElementModel() : SessionModel("ViewItemsModel") {
    setItemCatalogue(CreateItemCatalogue());
}

//! Add a layer item to the model and return its pointer
LayerElementItem* SLDElementModel::addLayer() {
    auto layer_element_item = insertItem<LayerElementItem>();
    return layer_element_item;
}

} // namespace DaRefl
