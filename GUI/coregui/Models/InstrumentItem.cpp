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
const QString InstrumentItem::P_DETECTOR = "Detector";

InstrumentItem::InstrumentItem()
    : SessionItem(Constants::InstrumentType)
{
    setItemName(Constants::InstrumentType);

    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

    addGroupProperty(P_BEAM, Constants::BeamType);

    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);

    setDefaultTag(P_DETECTOR);
}

BeamItem *InstrumentItem::beamItem() const
{
    return &item<BeamItem>(InstrumentItem::P_BEAM);
}

DetectorItem* InstrumentItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* InstrumentItem::detectorGroup()
{
    return &item<GroupItem>(P_DETECTOR);
}

void InstrumentItem::setDetectorGroup(const QString& modelType)
{
    setGroupProperty(P_DETECTOR, modelType);
}

void InstrumentItem::clearMasks()
{
    detectorItem()->clearMasks();
}

void InstrumentItem::importMasks(MaskContainerItem* maskContainer)
{
    detectorItem()->importMasks(maskContainer);
}
