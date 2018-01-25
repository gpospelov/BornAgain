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
#include "Beam.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "RectangularDetector.h"
#include "SphericalDetector.h"
#include "Units.h"

#include <cmath>
#include <stdexcept>

UnitConverterSimple::UnitConverterSimple(const Beam& beam)
    : m_wavelength(beam.getWavelength())
    , m_alpha_i(-beam.getAlpha())
    , m_phi_i(beam.getPhi())
{}

size_t UnitConverterSimple::dimension() const
{
    return m_axis_data_table.size();
}

void UnitConverterSimple::addAxisData(std::string name, double min, double max,
                                      AxesUnits default_units, size_t nbins)
{
    AxisData axis_data { name, min, max, default_units, nbins };
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

std::string UnitConverterSimple::axisName(size_t i_axis) const
{
    checkIndex(i_axis);
    auto axis_data = m_axis_data_table[i_axis];
    return axis_data.name;
}

UnitConverterSimple::UnitConverterSimple(const UnitConverterSimple& other)
    : m_axis_data_table(other.m_axis_data_table)
{}

void UnitConverterSimple::addDetectorAxis(const IDetector& detector, size_t i_axis)
{
    auto& axis = detector.getAxis(i_axis);
    addAxisData(axis.getName(), axis.getMin(), axis.getMax(), defaultUnits(), axis.size());
}

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

/* SphericalConverter **********************************************/

SphericalConverter::SphericalConverter(const SphericalDetector& detector, const Beam& beam)
    : UnitConverterSimple(beam)
{
    if (detector.dimension() != 2)
        throw std::runtime_error("Error in SphericalConverter constructor: "
                                 "detector has wrong dimension: "
                                 + std::to_string(static_cast<int>(detector.dimension())));
    addDetectorAxis(detector, 0);
    addDetectorAxis(detector, 1);
}

SphericalConverter::~SphericalConverter() =default;

SphericalConverter* SphericalConverter::clone() const
{
    return new SphericalConverter(*this);
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

/* RectangularConverter **********************************************/

RectangularConverter::RectangularConverter(const RectangularDetector& detector, const Beam& beam)
    : UnitConverterSimple(beam)
{
    if (detector.dimension() != 2)
        throw std::runtime_error("Error in RectangularConverter constructor: "
                                 "detector has wrong dimension: "
                                 + std::to_string(static_cast<int>(detector.dimension())));
    addDetectorAxis(detector, 0);
    addDetectorAxis(detector, 1);
    mP_detector_pixel.reset(detector.toSinglePixel());
}

RectangularConverter::~RectangularConverter() =default;

RectangularConverter* RectangularConverter::clone() const
{
    return new RectangularConverter(*this);
}

RectangularConverter::RectangularConverter(const RectangularConverter& other)
    : UnitConverterSimple(other)
    , mP_detector_pixel(other.mP_detector_pixel->clone())
{}

double RectangularConverter::calculateValue(size_t i_axis, AxesUnits units_type, double value) const
{
    auto k00 = mP_detector_pixel->getPosition(0.0, 0.0);
    auto k01 = mP_detector_pixel->getPosition(0.0, 1.0);
    auto k10 = mP_detector_pixel->getPosition(1.0, 0.0);
    auto max_pos = i_axis == 0 ? k10 : k01;  // position of max along given axis
    auto k_f = normalizeToWavelength(k00 + value*(max_pos - k00));
    switch(units_type) {
    case AxesUnits::DEGREES:
        return Units::rad2deg(axisAngle(i_axis, k_f));
    case AxesUnits::RADIANS:
        return axisAngle(i_axis, k_f);
    case AxesUnits::QYQZ:
    {
        auto k_i = vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
        if (i_axis == BornAgain::X_AXIS_INDEX) {
            return (k_i - k_f).y();
        } else if (i_axis == BornAgain::Y_AXIS_INDEX) {
            return (k_f - k_i).z();
        }
        throw std::runtime_error("Error in RectangularConverter::calculateValue: "
                                 "incorrect axis index: "
                                 + std::to_string(static_cast<int>(i_axis)));
    }
    default:
        throw std::runtime_error("Error in RectangularConverter::calculateValue: "
                                 "target units not available: "
                                 + std::to_string(static_cast<int>(units_type)));
    }
}

kvector_t RectangularConverter::normalizeToWavelength(kvector_t vector) const
{
    if (m_wavelength <= 0.0)
        throw std::runtime_error("Error in RectangularConverter::normalizeToWavelength: "
                                 "wavelength <= 0");
    double K = M_TWOPI/m_wavelength;
    return vector.unit()*K;
}

double RectangularConverter::axisAngle(size_t i_axis, kvector_t k_f) const
{
    if (i_axis == BornAgain::X_AXIS_INDEX) {
        return k_f.phi();
    } else if (i_axis == BornAgain::Y_AXIS_INDEX) {
        return M_PI_2 - k_f.theta();
    }
    throw std::runtime_error("Error in RectangularConverter::axisAngle: "
                             "incorrect axis index: "
                             + std::to_string(static_cast<int>(i_axis)));
}

