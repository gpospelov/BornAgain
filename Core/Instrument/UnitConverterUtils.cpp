// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/UnitConverterUtils.cpp
//! @brief     Implements utilities for unit convertion.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "UnitConverterUtils.h"
#include "Instrument.h"
#include "OutputData.h"
#include "RectangularDetector.h"
#include "SimpleUnitConverters.h"
#include "SphericalDetector.h"

std::unique_ptr<OutputData<double>>
UnitConverterUtils::createOutputData(const IUnitConverter& converter, AxesUnits units)
{
    std::unique_ptr<OutputData<double>> result = std::make_unique<OutputData<double>>();
    for (size_t i = 0; i < converter.dimension(); ++i)
        result->addAxis(*converter.createConvertedAxis(i, units));
    result->setAllTo(0.0);
    return result;
}

std::unique_ptr<IUnitConverter>
UnitConverterUtils::createConverterForGISAS(const Instrument& instrument)
{
    const auto detector = instrument.getDetector();

    if (const auto spher_detector = dynamic_cast<const SphericalDetector*>(detector))
        return std::make_unique<SphericalConverter>(*spher_detector, instrument.getBeam());
    else if (const auto rect_detector = dynamic_cast<const RectangularDetector*>(detector))
        return std::make_unique<RectangularConverter>(*rect_detector, instrument.getBeam());

    throw std::runtime_error(
        "Error in createConverterForGISAS: wrong or absent detector type");
}
