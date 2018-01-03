// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/IntensityDataItemUtils.cpp
//! @brief     Implements namespace IntensityDataItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IntensityDataItemUtils.h"
#include "GUIHelpers.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "IntensityDataItem.h"
#include "item_constants.h"

IntensityDataItem* IntensityDataItemUtils::intensityDataItem(SessionItem* parent)
{
    if (!parent)
        throw GUIHelpers::Error("IntensityDataItemUtils::intensityDataItem() -> Error. "
                                "Not initialized.");

    if (parent->modelType() == Constants::JobItemType)
        return &parent->item<IntensityDataItem>(JobItem::T_OUTPUT);
    else if(parent->modelType() == Constants::RealDataType)
        return &parent->item<IntensityDataItem>(RealDataItem::T_INTENSITY_DATA);
    else if(parent->modelType() == Constants::IntensityDataType)
        return dynamic_cast<IntensityDataItem *>(parent);
    else
        throw GUIHelpers::Error("IntensityDataItemUtils::intensityDataItem() -> Error. "
                                "Unexpected item.");
}

