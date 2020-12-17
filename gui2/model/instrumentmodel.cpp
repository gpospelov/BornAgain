// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/model/instrumentmodel.h"
#include "gui2/model/instrumentitems.h"
#include "mvvm/model/itemcatalogue.h"

using namespace ModelView;

namespace {

std::unique_ptr<ItemCatalogue> CreateItemCatalogue() {
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<gui2::SpecularInstrumentItem>();
    result->registerItem<gui2::SpecularBeamItem>();
    result->registerItem<gui2::SpecularScanGroupItem>();
    result->registerItem<gui2::QSpecScanItem>();
    result->registerItem<gui2::ExperimentalScanItem>();
    return result;
}

} // namespace

namespace gui2 {

InstrumentModel::InstrumentModel(std::shared_ptr<ItemPool> pool)
    : ModelView::SessionModel("InstrumentModel", pool) {
    setItemCatalogue(CreateItemCatalogue());
    insertItem<SpecularInstrumentItem>();
}

} // namespace gui2
