//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/sldelementmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/sldeditor/sldelementmodel.h"
#include "gui2/sldeditor/layerelementitem.h"

#include "mvvm/model/externalproperty.h"
#include "mvvm/model/itemcatalogue.h"
#include "mvvm/utils/reallimits.h"

using namespace ModelView;

namespace gui2 {

namespace {
std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<LayerElementItem>();
    return result;
}

} // namespace

//! Contructor
SLDElementModel::SLDElementModel() : SessionModel("ViewItemsModel")
{
    setItemCatalogue(CreateItemCatalogue());
}

//! Add a layer item to the model and return its pointer
LayerElementItem* SLDElementModel::addLayer()
{
    auto layer_element_item = insertItem<LayerElementItem>();
    return layer_element_item;
}

} // namespace gui2
