// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DepthProbeInstrumentItem.cpp
//! @brief     Implements DepthProbeInstrumentItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DepthProbeInstrumentItem.h"
#include "AxesItems.h"
#include "DepthProbeSimulation.h"
#include "SimpleUnitConverters.h"
#include "Units.h"

const QString DepthProbeInstrumentItem::P_BEAM = "Beam";
const QString DepthProbeInstrumentItem::P_ZAXIS = "Z axis";

DepthProbeInstrumentItem::DepthProbeInstrumentItem()
    : InstrumentItem(Constants::DepthProbeInstrumentType)
{
    setItemName(Constants::DepthProbeInstrumentType);

    addGroupProperty(P_BEAM, Constants::SpecularBeamType);

    auto axis = addGroupProperty(P_ZAXIS, Constants::BasicAxisType);
    axis->getItem(BasicAxisItem::P_TITLE)->setVisible(false);
    axis->setItemValue(BasicAxisItem::P_MIN, -100.0);
    axis->setItemValue(BasicAxisItem::P_MAX, 100.0);
    axis->getItem(BasicAxisItem::P_NBINS)->setToolTip("Number of points in scan across sample bulk");
    axis->getItem(BasicAxisItem::P_MIN)->setToolTip("Starting value below sample horizont in nm");
    axis->getItem(BasicAxisItem::P_MAX)->setToolTip("Ending value above sample horizont in nm");
}

SpecularBeamItem*DepthProbeInstrumentItem::beamItem() const
{
    return &item<SpecularBeamItem>(P_BEAM);
}

std::unique_ptr<Instrument> DepthProbeInstrumentItem::createInstrument() const
{
    throw std::runtime_error("DepthProbeInstrumentItem::createInstrument()");
}

std::vector<int> DepthProbeInstrumentItem::shape() const
{
    throw std::runtime_error("DepthProbeInstrumentItem::shape()");
}

void DepthProbeInstrumentItem::setShape(const std::vector<int>&)
{
    throw std::runtime_error("DepthProbeInstrumentItem::setShape()");
}

std::unique_ptr<DepthProbeSimulation> DepthProbeInstrumentItem::createSimulation() const
{
    std::unique_ptr<DepthProbeSimulation> simulation = std::make_unique<DepthProbeSimulation>();

    const auto axis_item = beamItem()->currentInclinationAxisItem();

    auto axis = axis_item->createAxis(Units::degree);

    simulation->setBeamParameters(beamItem()->getWavelength(), static_cast<int>(axis->size()),
                                  axis->getMin(), axis->getMax());

    auto depthAxisItem = dynamic_cast<BasicAxisItem*>(getItem(P_ZAXIS));
    auto depthAxis = depthAxisItem->createAxis(1.0);
    simulation->setZSpan(depthAxis->size(), depthAxis->getMin(), depthAxis->getMax());

    return simulation;
}

std::unique_ptr<IUnitConverter> DepthProbeInstrumentItem::createUnitConverter() const
{
    return createSimulation()->createUnitConverter();
}
