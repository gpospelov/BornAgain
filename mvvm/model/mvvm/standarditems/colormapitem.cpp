//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/colormapitem.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/standarditems/colormapitem.h"
#include "mvvm/model/comboproperty.h"
#include "mvvm/standarditems/data2ditem.h"
#include "mvvm/standarditems/linkeditem.h"
#include "mvvm/standarditems/plottableitems.h"

using namespace ModelView;

namespace {
const ComboProperty gradientCombo =
    ComboProperty::createFrom({"Grayscale", "Hot", "Cold", "Night", "Candy", "Geography", "Ion",
                               "Thermal", "Polar", "Spectrum", "Jet", "Hues"},
                              "Polar");
}

ColorMapItem::ColorMapItem() : CompoundItem(Constants::ColorMapItemType) {
    addProperty<LinkedItem>(P_LINK)->setDisplayName("Link");
    addProperty<TextItem>(P_TITLE)->setDisplayName("Title");
    addProperty(P_GRADIENT, gradientCombo)->setDisplayName("Gradient");
    addProperty(P_INTERPOLATION, true)->setDisplayName("Interpolation");
}

//! Sets link to the data item.

void ColorMapItem::setDataItem(const Data2DItem* data_item) {
    item<LinkedItem>(P_LINK)->setLink(data_item);
}

//! Returns data item linked to the given ColorMapItem.

Data2DItem* ColorMapItem::dataItem() const {
    return item<LinkedItem>(P_LINK)->get<Data2DItem>();
}
