// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/UnitConverters.cpp
//! @brief     Implements IUnitConverter classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "UnitConverters.h"
#include "BornAgainNamespace.h"
#include "Units.h"
#include "Vectors3D.h"

#include <cmath>
#include <stdexcept>

size_t UnitConverterSimple::dimension() const
{
    return m_axis_data_table.size();
}

void UnitConverterSimple::addAxisData(double min, double max, AxesUnits default_units, size_t nbins)
{
    AxisData axis_data { min, max, default_units, nbins };
    m_axis_data_table.push_back(axis_data);
}

double UnitConverterSimple::calculateMin(size_t i_axis, AxesUnits units_type) const
{
    checkIndex(i_axis);
    auto axis_data = m_axis_data_table[i_axis];
    if (units_type==defaultUnits() || units_type==AxesUnits::DEFAULT) {
        return axis_data.min;
    } else if (units_type==AxesUnits::NBINS) {
        return 0.0;
    }
    return calculateValue(i_axis, units_type, axis_data.min);
}

double UnitConverterSimple::calculateMax(size_t i_axis, AxesUnits units_type) const
{
    checkIndex(i_axis);
    auto axis_data = m_axis_data_table[i_axis];
    if (units_type==defaultUnits() || units_type==AxesUnits::DEFAULT) {
        return axis_data.max;
    } else if (units_type==AxesUnits::NBINS) {
        return static_cast<double>(axis_data.nbins);
    }
    return calculateValue(i_axis, units_type, axis_data.max);
}

size_t UnitConverterSimple::axisSize(size_t i_axis) const
{
    checkIndex(i_axis);
    auto axis_data = m_axis_data_table[i_axis];
    return axis_data.nbins;
}

// TODO: remove this implementation
std::string UnitConverterSimple::axisName(size_t) const
{
    return "default";
}

UnitConverterSimple::UnitConverterSimple(const UnitConverterSimple& other)
    : m_axis_data_table(other.m_axis_data_table)
{}

void UnitConverterSimple::checkIndex(size_t i_axis) const
{
    if (i_axis < dimension()) return;
    throw std::runtime_error("Error in UnitConverterSimple::checkIndex: passed axis index too big: "
                             + std::to_string(static_cast<int>(i_axis)));
}

void UnitConverterSimple::checkDimension(size_t dim) const
{
    if (dim == dimension()) return;
    throw std::runtime_error("Error in UnitConverterSimple::checkDimension: wrong dimension: "
                             + std::to_string(static_cast<int>(dim)));
}

SphericalConverter::SphericalConverter(size_t n_phi, double phi_min, double phi_max,
                                       size_t n_alpha, double alpha_min, double alpha_max,
                                       double wavelength, double alpha_i, double phi_i)
    : m_wavelength(wavelength), m_alpha_i(alpha_i), m_phi_i(phi_i)
{
    addAxisData(phi_min, phi_max, defaultUnits(), n_phi);
    addAxisData(alpha_min, alpha_max, defaultUnits(), n_alpha);
}

SphericalConverter::~SphericalConverter() =default;

SphericalConverter* SphericalConverter::clone() const
{
    checkDimension(2u);
    auto phi_data = m_axis_data_table[0];
    auto alpha_data = m_axis_data_table[1];
    return new SphericalConverter(phi_data.nbins, phi_data.min, phi_data.max,
                                  alpha_data.nbins, alpha_data.min, alpha_data.max,
                                  m_wavelength, m_alpha_i, m_phi_i);
}

double SphericalConverter::calculateValue(size_t i_axis, AxesUnits units_type, double value) const
{
    switch(units_type) {
    case AxesUnits::DEGREES:
        return Units::rad2deg(value);
    case AxesUnits::QYQZ:
    {
        auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
        if (i_axis == BornAgain::X_AXIS_INDEX) {
            auto k_f = vecOfLambdaAlphaPhi(m_wavelength, 0.0, value);
            return (k_i - k_f).y();
        } else if (i_axis == BornAgain::Y_AXIS_INDEX) {
            auto k_f = vecOfLambdaAlphaPhi(m_wavelength, value, 0.0);
            return (k_f - k_i).z();
        }
        throw std::runtime_error("Error in SphericalConverter::calculateValue: "
                                 "incorrect axis index: "
                                 + std::to_string(static_cast<int>(i_axis)));
    }
    default:
        throw std::runtime_error("Error in SphericalConverter::calculateValue: "
                                 "target units not available: "
                                 + std::to_string(static_cast<int>(units_type)));
    }
}
