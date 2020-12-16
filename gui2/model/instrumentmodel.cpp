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
    result->registerItem<DaRefl::SpecularInstrumentItem>();
    result->registerItem<DaRefl::SpecularBeamItem>();
    result->registerItem<DaRefl::SpecularScanGroupItem>();
    result->registerItem<DaRefl::QSpecScanItem>();
    result->registerItem<DaRefl::ExperimentalScanItem>();
    return result;
}

} // namespace

namespace DaRefl {

InstrumentModel::InstrumentModel(std::shared_ptr<ItemPool> pool)
    : ModelView::SessionModel("InstrumentModel", pool) {
    setItemCatalogue(CreateItemCatalogue());
    insertItem<SpecularInstrumentItem>();
}

} // namespace DaRefl
