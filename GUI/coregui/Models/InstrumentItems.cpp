// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItems.cpp
//! @brief     Implements InstrumentItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentItems.h"
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

InstrumentItem::InstrumentItem(const QString& modelType) : SessionItem(modelType)
{
    setItemName(modelType);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

}

const QString GISASInstrumentItem::P_BEAM = "Beam";
const QString GISASInstrumentItem::P_DETECTOR = "Detector";
const QString GISASInstrumentItem::P_BACKGROUND = "Background";

GISASInstrumentItem::GISASInstrumentItem()
    : InstrumentItem(Constants::GISASInstrumentType)
{
    addGroupProperty(P_BEAM, Constants::BeamType);

    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);

    setDefaultTag(P_DETECTOR);

    addGroupProperty(P_BACKGROUND, Constants::BackgroundGroup);
}

BeamItem *GISASInstrumentItem::beamItem() const
{
    return &item<BeamItem>(P_BEAM);
}

DetectorItem* GISASInstrumentItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* GISASInstrumentItem::detectorGroup()
{
    return &item<GroupItem>(P_DETECTOR);
}

BackgroundItem* GISASInstrumentItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* GISASInstrumentItem::backgroundGroup()
{
    return &item<GroupItem>(P_BACKGROUND);
}

void GISASInstrumentItem::setDetectorGroup(const QString& modelType)
{
    setGroupProperty(P_DETECTOR, modelType);
}

void GISASInstrumentItem::clearMasks()
{
    detectorItem()->clearMasks();
}

void GISASInstrumentItem::importMasks(MaskContainerItem* maskContainer)
{
    detectorItem()->importMasks(maskContainer);
}

QStringList GISASInstrumentItem::translateList(const QStringList& list) const
{
    QStringList result;
    // Add constant background directly to simulation
    if (list.back().startsWith(P_BACKGROUND) && list.size()==2) {
        result << list[0] << QString::fromStdString(BornAgain::ConstantBackgroundType);
    } else {
        // TODO Consider usage of ModelTypeTranslator in IntrusmentItem's constructor
        // after the refactoring of SessionItem::translateList
        result = SessionItem::translateList(list);
        if (result.back() == Constants::GISASInstrumentType) {
            result.removeLast();
            result << QStringLiteral("Instrument");
        }
    }
    return result;
}
