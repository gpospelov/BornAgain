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
#include "SessionModel.h"
#include "GroupItem.h"
#include "MaskItems.h"

const QString InstrumentItem::P_IDENTIFIER = "Identifier";
const QString InstrumentItem::P_BEAM = "Beam";
const QString InstrumentItem::P_DETECTOR = "Data tag";

InstrumentItem::InstrumentItem()
    : SessionItem(Constants::InstrumentType)
{
    setItemName(Constants::InstrumentType);

    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

    addGroupProperty(P_BEAM, Constants::BeamType);
    addGroupProperty(P_DETECTOR, Constants::DetectorContainerType);

//    const QString T_DATA = "Data tag";
//    registerTag(T_DATA, 0, -1, QStringList() << Constants::DetectorContainerType);
    setDefaultTag(P_DETECTOR);
}

BeamItem *InstrumentItem::beamItem() const
{
    for(SessionItem *item : childItems())
        if(item->modelType() == Constants::BeamType)
            return dynamic_cast<BeamItem *>(item);
    return 0;
}

DetectorContainerItem *InstrumentItem::detectorContainerItem() const
{
    for(SessionItem *item : childItems())
        if(item->modelType() == Constants::DetectorContainerType)
            return dynamic_cast<DetectorContainerItem *>(item);
    return 0;
}

DetectorItem* InstrumentItem::detectorItem() const
{
    return detectorContainerItem()->detectorItem();
}

GroupItem* InstrumentItem::detectorGroup()
{
    return &detectorContainerItem()->item<GroupItem>(DetectorContainerItem::P_DETECTOR);
}

void InstrumentItem::setDetectorGroup(const QString& modelType)
{
    detectorContainerItem()->setGroupProperty(DetectorContainerItem::P_DETECTOR, modelType);
}

void InstrumentItem::clearMasks()
{
    detectorContainerItem()->clearMasks();
}

void InstrumentItem::importMasks(MaskContainerItem* maskContainer)
{
    DetectorContainerItem *detectorContainer = detectorContainerItem();
    detectorContainer->importMasks(maskContainer);
}
