// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItems.cpp
//! @brief     Implements BeamItem hierarchy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "BeamItems.h"
#include "AxesItems.h"
#include "Beam.h"
#include "BeamAngleItems.h"
#include "BeamDistributionItem.h"
#include "BeamWavelengthItem.h"
#include "BornAgainNamespace.h"
#include "FootprintItems.h"
#include "GUIHelpers.h"
#include "ParameterTranslators.h"
#include "SessionItemUtils.h"
#include "SpecularBeamInclinationItem.h"
#include "Units.h"

using SessionItemUtils::GetVectorItem;

namespace
{
const QString polarization_tooltip = "Polarization of the beam, given as the Bloch vector";
}

const QString BeamItem::P_INTENSITY = QString::fromStdString(BornAgain::Intensity);
const QString BeamItem::P_WAVELENGTH = QString::fromStdString(BornAgain::Wavelength);
const QString BeamItem::P_INCLINATION_ANGLE = QString::fromStdString(BornAgain::Inclination);
const QString BeamItem::P_AZIMUTHAL_ANGLE = QString::fromStdString(BornAgain::Azimuth);
const QString BeamItem::P_POLARIZATION = QString("Polarization");

BeamItem::BeamItem(const QString& beam_model) : SessionItem(beam_model)
{
    addProperty(P_INTENSITY, 1e+08)
        ->setLimits(RealLimits::limited(0.0, 1e+32))
        .setToolTip("Beam intensity in neutrons (or gammas) per sec.")
        .setEditorType(Constants::ScientificEditorType);

    addGroupProperty(P_WAVELENGTH, Constants::BeamWavelengthType);
    addGroupProperty(P_AZIMUTHAL_ANGLE, Constants::BeamAzimuthalAngleType);
    addGroupProperty(P_POLARIZATION, Constants::VectorType)->setToolTip(polarization_tooltip);

    addTranslator(VectorParameterTranslator(P_POLARIZATION, BornAgain::BlochVector));
}

BeamItem::~BeamItem() = default;

double BeamItem::getIntensity() const
{
    return getItemValue(P_INTENSITY).toDouble();
}

void BeamItem::setIntensity(double value)
{
    setItemValue(P_INTENSITY, value);
}

double BeamItem::getWavelength() const
{
    BeamWavelengthItem* beamWavelength = dynamic_cast<BeamWavelengthItem*>(getItem(P_WAVELENGTH));
    return beamWavelength->wavelength();
}

void BeamItem::setWavelength(double value)
{
    auto beam_wavelength = dynamic_cast<BeamWavelengthItem*>(getItem(P_WAVELENGTH));
    Q_ASSERT(beam_wavelength);
    beam_wavelength->resetToValue(value);
}

void BeamItem::setInclinationAngle(double value)
{
    auto angleItem = dynamic_cast<BeamDistributionItem*>(getItem(P_INCLINATION_ANGLE));
    Q_ASSERT(angleItem);
    angleItem->resetToValue(value);
}

double BeamItem::getAzimuthalAngle() const
{
    const auto inclination
        = dynamic_cast<BeamAzimuthalAngleItem*>(getItem(P_AZIMUTHAL_ANGLE));
    Q_ASSERT(inclination);
    return inclination->azimuthalAngle();
}

void BeamItem::setAzimuthalAngle(double value)
{
    auto angleItem = dynamic_cast<BeamDistributionItem*>(getItem(P_AZIMUTHAL_ANGLE));
    Q_ASSERT(angleItem);
    angleItem->resetToValue(value);
}

std::unique_ptr<Beam> BeamItem::createBeam() const
{
    auto result = std::make_unique<Beam>();

    result->setIntensity(getIntensity());
    double lambda = getWavelength();
    double inclination_angle = Units::deg2rad(getInclinationAngle());
    double azimuthal_angle = Units::deg2rad(getAzimuthalAngle());
    result->setCentralK(lambda, inclination_angle, azimuthal_angle);

    result->setPolarization(GetVectorItem(*this, P_POLARIZATION));

    return result;
}

void BeamItem::setInclinationProperty(const QString& inclination_type)
{
    addGroupProperty(P_INCLINATION_ANGLE, inclination_type);
}

// Specular beam item
/* ------------------------------------------------------------------------- */

const QString SpecularBeamItem::P_FOOPTPRINT = QString("Footprint");

const QString footprint_group_label("Type");

SpecularBeamItem::SpecularBeamItem() : BeamItem(Constants::SpecularBeamType)
{
    setInclinationProperty(Constants::SpecularBeamInclinationType);

    auto item = addGroupProperty(P_FOOPTPRINT, Constants::FootprintGroup);
    item->setDisplayName(footprint_group_label);
    item->setToolTip("Footprint type");
}

SpecularBeamItem::~SpecularBeamItem() = default;

double SpecularBeamItem::getInclinationAngle() const
{
    Q_ASSERT(
        dynamic_cast<BeamDistributionItem*>(getItem(P_INCLINATION_ANGLE))->meanValue()
        == 0.0);
    return 0.0;
}

void SpecularBeamItem::setInclinationAngle(double value)
{
    Q_ASSERT(value == 0.0);
    value = 0.0;
    BeamItem::setInclinationAngle(value);
}

BasicAxisItem& SpecularBeamItem::getInclinationAngleAxis()
{
    return getItem(BeamItem::P_INCLINATION_ANGLE)
        ->item<BasicAxisItem>(SpecularBeamInclinationItem::P_ALPHA_AXIS);
}

FootprintItem* SpecularBeamItem::currentFootprintItem() const
{
    return &groupItem<FootprintItem>(P_FOOPTPRINT);
}

// GISAS beam item
/* ------------------------------------------------------------------------- */

GISASBeamItem::GISASBeamItem() : BeamItem(Constants::GISASBeamType)
{
    setInclinationProperty(Constants::BeamInclinationAngleType);
}

GISASBeamItem::~GISASBeamItem() = default;

double GISASBeamItem::getInclinationAngle() const
{
    const auto inclination
        = dynamic_cast<BeamInclinationAngleItem*>(getItem(P_INCLINATION_ANGLE));
    Q_ASSERT(inclination);
    return inclination->inclinationAngle();
}
