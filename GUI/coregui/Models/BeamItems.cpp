//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Models/BeamItems.cpp
//! @brief     Implements BeamItem hierarchy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Models/BeamItems.h"
#include "Base/Axis/IAxis.h"
#include "Base/Const/Units.h"
#include "Device/Beam/Beam.h"
#include "GUI/coregui/Models/BeamAngleItems.h"
#include "GUI/coregui/Models/BeamWavelengthItem.h"
#include "GUI/coregui/Models/FootprintItems.h"
#include "GUI/coregui/Models/GroupItem.h"
#include "GUI/coregui/Models/ParameterTranslators.h"
#include "GUI/coregui/Models/PointwiseAxisItem.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Models/SpecularBeamInclinationItem.h"
#include "GUI/coregui/Models/VectorItem.h"
#include "GUI/coregui/utils/GUIHelpers.h"
#include <cmath>

namespace {
const QString polarization_tooltip = "Polarization of the beam, given as the Bloch vector";

// defines wavelength limits according to given maximum q value
RealLimits getLimits(double max_q);
} // namespace

const QString BeamItem::P_INTENSITY = QString::fromStdString("Intensity");
const QString BeamItem::P_WAVELENGTH = QString::fromStdString("Wavelength");
const QString BeamItem::P_INCLINATION_ANGLE = QString::fromStdString("InclinationAngle");
const QString BeamItem::P_AZIMUTHAL_ANGLE = QString::fromStdString("AzimuthalAngle");
const QString BeamItem::P_POLARIZATION = "Polarization";

BeamItem::BeamItem(const QString& beam_model) : SessionItem(beam_model)
{
    addProperty(P_INTENSITY, 1e+08)
        ->setLimits(RealLimits::limited(0.0, 1e+32))
        .setToolTip("Beam intensity in neutrons (or gammas) per sec.")
        .setEditorType("ScientificDouble");

    addProperty<BeamAzimuthalAngleItem>(P_AZIMUTHAL_ANGLE);
    addProperty<VectorItem>(P_POLARIZATION)->setToolTip(polarization_tooltip);

    addTranslator(VectorParameterTranslator(P_POLARIZATION, "BlochVector"));
}

BeamItem::~BeamItem() = default;

double BeamItem::intensity() const
{
    return getItemValue(P_INTENSITY).toDouble();
}

void BeamItem::setIntensity(double value)
{
    setItemValue(P_INTENSITY, value);
}

double BeamItem::wavelength() const
{
    return item<BeamWavelengthItem>(P_WAVELENGTH)->wavelength();
}

void BeamItem::setWavelength(double value)
{
    item<BeamWavelengthItem>(P_WAVELENGTH)->resetToValue(value);
}

void BeamItem::setInclinationAngle(double value)
{
    item<BeamDistributionItem>(P_INCLINATION_ANGLE)->resetToValue(value);
}

double BeamItem::getAzimuthalAngle() const
{
    return item<BeamAzimuthalAngleItem>(P_AZIMUTHAL_ANGLE)->azimuthalAngle();
}

void BeamItem::setAzimuthalAngle(double value)
{
    item<BeamDistributionItem>(P_AZIMUTHAL_ANGLE)->resetToValue(value);
}

std::unique_ptr<Beam> BeamItem::createBeam() const
{
    double lambda = wavelength();
    double inclination_angle = Units::deg2rad(getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(getAzimuthalAngle());

    auto result =
        std::make_unique<Beam>(intensity(), lambda, Direction(inclination_angle, azimuthal_angle));

    result->setPolarization(item<VectorItem>(P_POLARIZATION)->getVector());

    return result;
}

// Specular beam item
/* ------------------------------------------------------------------------- */

const QString SpecularBeamItem::P_FOOPTPRINT = "Footprint";

const QString footprint_group_label("Type");

SpecularBeamItem::SpecularBeamItem() : BeamItem("SpecularBeam")
{
    addProperty<SpecularBeamInclinationItem>(P_INCLINATION_ANGLE);
    addProperty<SpecularBeamWavelengthItem>(P_WAVELENGTH);

    getItem(P_AZIMUTHAL_ANGLE)->setVisible(false);
    getItem(P_POLARIZATION)->setVisible(false);

    auto item = addGroupProperty(P_FOOPTPRINT, "Footprint group");
    item->setDisplayName(footprint_group_label);
    item->setToolTip("Footprint type");

    getItem(P_WAVELENGTH)
        ->mapper()
        ->setOnChildPropertyChange(
            [this](SessionItem*, QString property) {
                if (property != SymmetricDistributionItem::P_MEAN)
                    return;
                if (auto axis_item = dynamic_cast<PointwiseAxisItem*>(currentInclinationAxisItem()))
                    axis_item->updateIndicators();
            },
            this);

    inclinationAxisGroup()->mapper()->setOnValueChange([this]() { updateWavelength(); }, this);
}

SpecularBeamItem::~SpecularBeamItem() = default;

double SpecularBeamItem::getInclinationAngle() const
{
    return 0.0;
}

void SpecularBeamItem::setInclinationAngle(double value)
{
    ASSERT(value == 0.0);
    value = 0.0;
    BeamItem::setInclinationAngle(value);
}

GroupItem* SpecularBeamItem::inclinationAxisGroup()
{
    return dynamic_cast<GroupItem*>(
        getItem(P_INCLINATION_ANGLE)->getItem(SpecularBeamInclinationItem::P_ALPHA_AXIS));
}

BasicAxisItem* SpecularBeamItem::currentInclinationAxisItem()
{
    return dynamic_cast<BasicAxisItem*>(inclinationAxisGroup()->currentItem());
}

FootprintItem* SpecularBeamItem::currentFootprintItem() const
{
    return &groupItem<FootprintItem>(P_FOOPTPRINT);
}

void SpecularBeamItem::updateFileName(const QString& filename)
{
    item<SpecularBeamInclinationItem>(BeamItem::P_INCLINATION_ANGLE)->updateFileName(filename);
}

void SpecularBeamItem::updateToData(const IAxis& axis, QString units)
{
    if (units == "nbins") {
        inclinationAxisGroup()->setCurrentType("BasicAxis");
        auto axis_item = currentInclinationAxisItem();
        axis_item->setBinCount(static_cast<int>(axis.size()));
        return;
    }

    auto axis_group = inclinationAxisGroup();
    auto axis_item = static_cast<PointwiseAxisItem*>(axis_group->getChildOfType("PointwiseAxis"));
    axis_item->init(axis, units);
    axis_group->setCurrentType("PointwiseAxis"); // calls updateWavelength()
    axis_item->updateIndicators();
}

void SpecularBeamItem::updateWavelength()
{
    auto item = inclinationAxisGroup()->currentItem();
    auto wl_item = static_cast<SpecularBeamWavelengthItem*>(getItem(P_WAVELENGTH));
    if (auto axis_item = dynamic_cast<PointwiseAxisItem*>(item)) {
        auto axis = axis_item->axis();
        if (axis && axis_item->getUnitsLabel() == "q-space")
            wl_item->setToRange(getLimits(axis->upperBound()));
    } else
        wl_item->setToRange(RealLimits::positive());
}

// GISAS beam item
/* ------------------------------------------------------------------------- */

GISASBeamItem::GISASBeamItem() : BeamItem("GISASBeam")
{
    addProperty<BeamInclinationAngleItem>(P_INCLINATION_ANGLE);
    addProperty<BeamWavelengthItem>(P_WAVELENGTH);
}

GISASBeamItem::~GISASBeamItem() = default;

double GISASBeamItem::getInclinationAngle() const
{
    return item<BeamInclinationAngleItem>(P_INCLINATION_ANGLE)->inclinationAngle();
}

namespace {
RealLimits getLimits(double max_q)
{
    double upper_lim = std::nextafter(4.0 * M_PI / max_q, 0.0);
    RealLimits result = RealLimits::positive();
    result.setUpperLimit(upper_lim);
    return result;
}
} // namespace
