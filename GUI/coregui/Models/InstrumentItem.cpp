// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItem.cpp
//! @brief     Implements class InstrumentItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentItem.h"
#include "BackgroundItems.h"
#include "BeamItem.h"
#include "BornAgainNamespace.h"
#include "DetectorItems.h"
#include "GUIHelpers.h"
#include "SessionModel.h"
#include "GroupItem.h"
#include "MaskItems.h"
#include "ParameterTranslators.h"

const QString InstrumentItem::P_IDENTIFIER = "Identifier";
const QString InstrumentItem::P_BEAM = "Beam";
const QString InstrumentItem::P_DETECTOR = "Detector";
const QString InstrumentItem::P_BACKGROUND = "Background";

InstrumentItem::InstrumentItem()
    : SessionItem(Constants::InstrumentType)
{
    setItemName(Constants::InstrumentType);

    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

    addGroupProperty(P_BEAM, Constants::BeamType);

    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);

    setDefaultTag(P_DETECTOR);

    addGroupProperty(P_BACKGROUND, Constants::BackgroundGroup);
}

BeamItem *InstrumentItem::beamItem() const
{
    return &item<BeamItem>(P_BEAM);
}

DetectorItem* InstrumentItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* InstrumentItem::detectorGroup()
{
    return &item<GroupItem>(P_DETECTOR);
}

BackgroundItem* InstrumentItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* InstrumentItem::backgroundGroup()
{
    return &item<GroupItem>(P_BACKGROUND);
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

QStringList InstrumentItem::translateList(const QStringList& list) const
{
    QStringList result;
    // Add constant background directly to simulation
    if (list.back().startsWith(P_BACKGROUND) && list.size()==2) {
        result << list[0] << QString::fromStdString(BornAgain::ConstantBackgroundType);
    } else {
        // TODO Consider usage of ModelTypeTranslator in IntrusmentItem's constructor
        // after the refactoring of SessionItem::translateList
        result = SessionItem::translateList(list);
        if (result.back() == Constants::InstrumentType) {
            result.removeLast();
            result << QStringLiteral("Instrument");
        }
    }
    return result;
}
