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
#include "Instrument.h"
#include "IDetector2D.h"
#include "AxesItems.h"

namespace {
const QString background_group_label = "Type";
void addAxisGroupProperty(SessionItem* parent, const QString& tag);
}

const QString InstrumentItem::P_IDENTIFIER = "Identifier";
const QString InstrumentItem::P_BEAM = "Beam";
const QString InstrumentItem::P_BACKGROUND = "Background";

QStringList InstrumentItem::translateList(const QStringList& list) const
{
    QStringList result;
    // Add constant background directly to simulation
    // TODO: this way of directly adding background is too sensitive
    //       to the background name
    if (list.back().endsWith(P_BACKGROUND) && list.size()==2) {
        result << list[0] << list[1];
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

BeamItem* InstrumentItem::beamItem() const
{
    return &item<BeamItem>(P_BEAM);
}

BackgroundItem* InstrumentItem::backgroundItem() const
{
    return &groupItem<BackgroundItem>(P_BACKGROUND);
}

GroupItem* InstrumentItem::backgroundGroup()
{
    return &item<GroupItem>(P_BACKGROUND);
}

std::unique_ptr<Instrument> InstrumentItem::createInstrument() const
{
    std::unique_ptr<Instrument> result(new Instrument);

    auto beam = beamItem()->createBeam();
    result->setBeam(*beam);

    return result;
}

InstrumentItem::InstrumentItem(const QString& modelType) : SessionItem(modelType)
{
    setItemName(modelType);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid())->setVisible(false);

    addGroupProperty(P_BEAM, Constants::BeamType);

    auto item = addGroupProperty(P_BACKGROUND, Constants::BackgroundGroup);
    item->setDisplayName(background_group_label);
    item->setToolTip("Background type");
}

const QString SpecularInstrumentItem::P_ALPHA_AXIS = "Alpha axis";

SpecularInstrumentItem::SpecularInstrumentItem()
    : InstrumentItem(Constants::SpecularInstrumentType)
{
    addAxisGroupProperty(this, P_ALPHA_AXIS);
}

std::unique_ptr<Instrument> SpecularInstrumentItem::createInstrument() const
{
    return InstrumentItem::createInstrument();
}

const QString Instrument2DItem::P_DETECTOR = "Detector";

Instrument2DItem::Instrument2DItem(const QString& modelType)
    : InstrumentItem(modelType)
{
    addGroupProperty(P_DETECTOR, Constants::DetectorGroup);

    setDefaultTag(P_DETECTOR);
}

Instrument2DItem::~Instrument2DItem() = default;

DetectorItem* Instrument2DItem::detectorItem() const
{
    return &groupItem<DetectorItem>(P_DETECTOR);
}

GroupItem* Instrument2DItem::detectorGroup()
{
    return &item<GroupItem>(P_DETECTOR);
}

void Instrument2DItem::setDetectorGroup(const QString& modelType)
{
    setGroupProperty(P_DETECTOR, modelType);
}

void Instrument2DItem::clearMasks()
{
    detectorItem()->clearMasks();
}

void Instrument2DItem::importMasks(MaskContainerItem* maskContainer)
{
    detectorItem()->importMasks(maskContainer);
}

std::unique_ptr<Instrument> Instrument2DItem::createInstrument() const
{
    auto result = InstrumentItem::createInstrument();

    auto detector = detectorItem()->createDetector();
    result->setDetector(*detector);

    return result;
}

GISASInstrumentItem::GISASInstrumentItem()
    : Instrument2DItem(Constants::GISASInstrumentType)
{
}

const QString OffSpecInstrumentItem::P_ALPHA_AXIS = "Alpha axis";

OffSpecInstrumentItem::OffSpecInstrumentItem()
    : Instrument2DItem(Constants::OffSpecInstrumentType)
{
    addAxisGroupProperty(this, P_ALPHA_AXIS);
}

namespace
{
void addAxisGroupProperty(SessionItem* parent, const QString& tag)
{
    auto item = parent->addGroupProperty(tag, Constants::BasicAxisType);
    item->setToolTip("Incoming alpha range [deg]");
    item->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    item->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan");
    item->getItem(BasicAxisItem::P_MIN)->setToolTip("Starting value [deg]");
    item->getItem(BasicAxisItem::P_MAX)->setToolTip("Ending value [deg]");

    item->setItemValue(BasicAxisItem::P_TITLE, "alpha_i");
    item->setItemValue(BasicAxisItem::P_MIN, 0.0);
    item->setItemValue(BasicAxisItem::P_MAX, 10.0);
}
} // namespace

