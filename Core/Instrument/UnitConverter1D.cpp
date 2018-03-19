// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/UnitConverter1D.cpp
//! @brief     Implements the class UnitConverter1D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "UnitConverter1D.h"
#include "AxisNames.h"
#include "Beam.h"
#include "IAxis.h"
#include "MathConstants.h"
#include "Units.h"
#include "VariableBinAxis.h"

namespace {
void checkDimensions(size_t i_axis);
double getQ(double wavelength, double angle);
}

UnitConverter1D::UnitConverter1D(const Beam& beam, const IAxis& axis)
    : m_wavelength(beam.getWavelength())
    , m_axis(axis.clone())
{
    if (m_axis->getMin() < 0 || m_axis->getMax() > M_PI_2)
        throw std::runtime_error("Error in UnitConverter1D: input axis range is out of bounds");
}

UnitConverter1D::~UnitConverter1D() = default;

UnitConverter1D* UnitConverter1D::clone() const
{
    return new UnitConverter1D(*this);
}

size_t UnitConverter1D::dimension() const
{
    return 1u;
}

double UnitConverter1D::calculateMin(size_t i_axis, AxesUnits units_type) const
{
    checkDimensions(i_axis);
    if (units_type == AxesUnits::DEFAULT)
        units_type = defaultUnits();
    return calculateValue(units_type, m_axis->getMin());
}

double UnitConverter1D::calculateMax(size_t i_axis, AxesUnits units_type) const
{
    checkDimensions(i_axis);
    if (units_type == AxesUnits::DEFAULT)
        units_type = defaultUnits();
    return calculateValue(units_type, m_axis->getMax());
}

size_t UnitConverter1D::axisSize(size_t i_axis) const
{
    checkDimensions(i_axis);
    return m_axis->size();
}

AxesUnits UnitConverter1D::defaultUnits() const
{
    return AxesUnits::DEGREES;
}

std::unique_ptr<IAxis> UnitConverter1D::createConvertedAxis(size_t i_axis, AxesUnits units) const
{
    checkDimensions(i_axis);
    if (units == AxesUnits::DEFAULT)
        units = defaultUnits();
    auto boundaries = m_axis->getBinBoundaries();
    for (size_t i = 0, size = boundaries.size(); i < size; ++i)
        boundaries[i] = calculateValue(units, boundaries[i]);
    const auto& name = axisName(0, units);
    return std::make_unique<VariableBinAxis>(name, m_axis->size(), boundaries);
}

UnitConverter1D::UnitConverter1D(const UnitConverter1D& other)
    : m_wavelength(other.m_wavelength)
    , m_axis(other.m_axis->clone())
{
}

double UnitConverter1D::calculateValue(AxesUnits units_type, double value) const
{
    switch(units_type) {
    case AxesUnits::RADIANS:
        return value;
    case AxesUnits::DEGREES:
        return Units::rad2deg(value);
    case AxesUnits::NBINS:
        return m_axis->findIndex(value);
    case AxesUnits::QSPACE:
        return getQ(m_wavelength, value);
    default:
        throw std::runtime_error("Error in SpecularConverter::calculateValue: "
                                 "target units not available: "
                                 + std::to_string(static_cast<int>(units_type)));
    }
}

std::vector<std::map<AxesUnits, std::string>> UnitConverter1D::createNameMaps() const
{
    std::vector<std::map<AxesUnits, std::string>> result;
    result.push_back(AxisNames::InitSpecAxis());
    return result;
}

namespace {
void checkDimensions(size_t i_axis)
{
    if (i_axis == 0)
        return;
    throw std::runtime_error("Error in UnitConverter1D::checkDimensions: "
                             "input dimension"
                             + std::to_string(i_axis) + "exceeds dimensionality of the converter.");
}

double getQ(double wavelength, double angle)
{
    return 4.0 * M_PI * std::sin(angle) / wavelength;
}
}
