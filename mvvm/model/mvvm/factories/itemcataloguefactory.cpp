//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/factories/itemcataloguefactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/factories/itemcataloguefactory.h"
#include "mvvm/standarditems/standarditemincludes.h"

using namespace ModelView;

std::unique_ptr<ItemCatalogue> ModelView::CreateStandardItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<ColorMapItem>();
    result->registerItem<ColorMapViewportItem>();
    result->registerItem<CompoundItem>();
    result->registerItem<ContainerItem>();
    result->registerItem<Data1DItem>();
    result->registerItem<Data2DItem>();
    result->registerItem<FixedBinAxisItem>();
    result->registerItem<GraphItem>();
    result->registerItem<GraphViewportItem>();
    result->registerItem<LinkedItem>();
    result->registerItem<PenItem>();
    result->registerItem<PointwiseAxisItem>();
    result->registerItem<PropertyItem>();
    result->registerItem<SessionItem>();
    result->registerItem<TextItem>();
    result->registerItem<VectorItem>();
    result->registerItem<ViewportAxisItem>();
    return result;
}
