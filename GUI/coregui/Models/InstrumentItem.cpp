// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItem.cpp
//! @brief     Implements class InstrumentItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"

const QString InstrumentItem::P_IDENTIFIER = "Identifier";

InstrumentItem::InstrumentItem()
    : SessionItem(Constants::InstrumentType)
{
    setItemName(Constants::InstrumentType);

    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

    const QString T_DATA = "Data tag";
    registerTag(T_DATA, 0, -1, QStringList() << Constants::BeamType << Constants::DetectorType);
    setDefaultTag(T_DATA);
}

BeamItem *InstrumentItem::beamItem() const
{
    for(SessionItem *item : childItems())
        if(item->modelType() == Constants::BeamType)
            return dynamic_cast<BeamItem *>(item);
    return 0;
}

DetectorItem *InstrumentItem::detectorItem() const
{
    for(SessionItem *item : childItems())
        if(item->modelType() == Constants::DetectorType)
            return dynamic_cast<DetectorItem *>(item);
    return 0;
}
