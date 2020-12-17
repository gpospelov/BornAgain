//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/libtestmachinery/toymodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "toymodel.h"
#include "mvvm/model/itemcatalogue.h"
#include "toyitems.h"

namespace {
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue() {
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<ToyItems::MultiLayerItem>();
    result->registerItem<ToyItems::LayerItem>();
    result->registerItem<ToyItems::ParticleItem>();
    result->registerItem<ToyItems::LatticeItem>();
    result->registerItem<ToyItems::SphereItem>();
    result->registerItem<ToyItems::CylinderItem>();
    result->registerItem<ToyItems::AnysoPyramidItem>();
    result->registerItem<ToyItems::ShapeGroupItem>();
    return result;
}
} // namespace

ToyItems::SampleModel::SampleModel() : SessionModel("ToyModel") {
    setItemCatalogue(CreateItemCatalogue());
}

ToyItems::SampleModel::SampleModel(std::shared_ptr<ModelView::ItemPool> pool)
    : SessionModel("ToyModel", pool) {
    setItemCatalogue(CreateItemCatalogue());
}
