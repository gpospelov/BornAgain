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
#include "FixedBinAxis.h"
#include "MathConstants.h"
#include "PointwiseAxis.h"
#include "UnitConverterUtils.h"
#include "Units.h"

namespace
{
double getQ(double wavelength, double angle);

double getInvQ(double wavelength, double q);

std::unique_ptr<PointwiseAxis>
createTranslatedAxis(const IAxis& axis, std::function<double(double)> translator, std::string name);
} // namespace

UnitConverter1D::UnitConverter1D(const Beam& beam, const IAxis& axis, AxesUnits axis_units)
    : m_wavelength(beam.getWavelength())
{
    m_axis = createTranslatedAxis(axis, getTraslatorFrom(axis_units), axisName(0, axis_units));
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
    checkIndex(i_axis);
    units_type = UnitConverterUtils::substituteDefaultUnits(*this, units_type);
    if (units_type == AxesUnits::NBINS)
        return 0.0;
    auto translator = getTraslatorTo(units_type);
    return translator(m_axis->getBinCenter(0));
}

double UnitConverter1D::calculateMax(size_t i_axis, AxesUnits units_type) const
{
    checkIndex(i_axis);
    units_type = UnitConverterUtils::substituteDefaultUnits(*this, units_type);
    if (units_type == AxesUnits::NBINS)
        return static_cast<double>(m_axis->size());
    auto translator = getTraslatorTo(units_type);
    return translator(m_axis->getBinCenter(m_axis->size() - 1));
}

size_t UnitConverter1D::axisSize(size_t i_axis) const
{
    checkIndex(i_axis);
    return m_axis->size();
}

std::vector<AxesUnits> UnitConverter1D::availableUnits() const
{
    return {AxesUnits::NBINS, AxesUnits::RADIANS, AxesUnits::DEGREES, AxesUnits::QSPACE};
}

AxesUnits UnitConverter1D::defaultUnits() const
{
    return AxesUnits::DEGREES;
}

std::unique_ptr<IAxis> UnitConverter1D::createConvertedAxis(size_t i_axis, AxesUnits units) const
{
    checkIndex(i_axis);
    units = UnitConverterUtils::substituteDefaultUnits(*this, units);
    if (units == AxesUnits::NBINS)
        return std::make_unique<FixedBinAxis>(axisName(0, units), m_axis->size(),
                                              calculateMin(0, units), calculateMax(0, units));
    return createTranslatedAxis(*m_axis, getTraslatorTo(units), axisName(0, units));
}

UnitConverter1D::UnitConverter1D(const UnitConverter1D& other)
    : m_wavelength(other.m_wavelength)
    , m_axis(other.m_axis->clone())
{
}

std::function<double(double)> UnitConverter1D::getTraslatorFrom(AxesUnits units_type) const
{
    switch (units_type) {
    case AxesUnits::RADIANS:
        return [](double value) { return value; };
    case AxesUnits::DEGREES:
        return [](double value) { return Units::deg2rad(value); };
    case AxesUnits::QSPACE:
        return [this](double value) { return getInvQ(m_wavelength, value); };
    default:
        throw std::runtime_error(
            "Error in UnitConverter1D::getTranslatorFrom: unexpected units type");
    }
}

std::function<double(double)> UnitConverter1D::getTraslatorTo(AxesUnits units_type) const
{
    switch (units_type) {
    case AxesUnits::RADIANS:
        return [](double value) { return value; };
    case AxesUnits::DEGREES:
        return [](double value) { return Units::rad2deg(value); };
    case AxesUnits::QSPACE:
        return [this](double value) { return getQ(m_wavelength, value); };
    default:
        throw std::runtime_error(
            "Error in UnitConverter1D::getTranslatorTo: unexpected units type");
    }
}

std::vector<std::map<AxesUnits, std::string>> UnitConverter1D::createNameMaps() const
{
    std::vector<std::map<AxesUnits, std::string>> result;
    result.push_back(AxisNames::InitSpecAxis());
    return result;
}

namespace
{
double getQ(double wavelength, double angle)
{
    return 4.0 * M_PI * std::sin(angle) / wavelength;
}

double getInvQ(double wavelength, double q)
{
    double sin_angle = q * wavelength / (4.0 * M_PI);
    return std::asin(sin_angle);
}

std::unique_ptr<PointwiseAxis>
createTranslatedAxis(const IAxis& axis, std::function<double(double)> translator, std::string name)
{
    auto coordinates = axis.getBinCenters();
    for (size_t i = 0, size = coordinates.size(); i < size; ++i)
        coordinates[i] = translator(coordinates[i]);
    return std::make_unique<PointwiseAxis>(name, coordinates);
}
} // namespace
