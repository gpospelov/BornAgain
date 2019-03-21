// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/AngularSpecScan.cpp
//! @brief     Implements AngularSpecScan class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "AngularSpecScan.h"
#include "FixedBinAxis.h"
#include "IFootprintFactor.h"
#include "PointwiseAxis.h"
#include "PythonFormatting.h"
#include "RangedDistributions.h"
#include "RealLimits.h"
#include "ScanResolution.h"
#include "SpecularSimulationElement.h"

namespace {
const RealLimits wl_limits = RealLimits::nonnegative();
const RealLimits inc_limits = RealLimits::limited(0.0, M_PI_2);
}

AngularSpecScan::AngularSpecScan(double wl, std::vector<double> inc_angle)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(std::make_unique<PointwiseAxis>("inc_angles", std::move(inc_angle)))
    , m_wl_resolution(ScanResolution::scanEmptyResolution())
    , m_inc_resolution(ScanResolution::scanEmptyResolution())
{
    checkInitialization();
}

AngularSpecScan::AngularSpecScan(double wl, const IAxis& inc_angle)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(inc_angle.clone())
    , m_wl_resolution(ScanResolution::scanEmptyResolution())
    , m_inc_resolution(ScanResolution::scanEmptyResolution())
{
    checkInitialization();
}

AngularSpecScan::AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(std::make_unique<FixedBinAxis>("inc_angles", nbins, alpha_i_min, alpha_i_max))
    , m_wl_resolution(ScanResolution::scanEmptyResolution())
    , m_inc_resolution(ScanResolution::scanEmptyResolution())
{
    checkInitialization();
}

AngularSpecScan* AngularSpecScan::clone() const
{
    auto result = std::make_unique<AngularSpecScan>(m_wl, *m_inc_angle);
    result->setFootprintFactor(m_footprint.get());
    result->setWavelengthResolution(*m_wl_resolution);
    result->setAngleResolution(*m_inc_resolution);
    return result.release();
}

AngularSpecScan::~AngularSpecScan() = default;

std::vector<SpecularSimulationElement> AngularSpecScan::generateSimulationElements() const
{
    std::vector<SpecularSimulationElement> result;

    const size_t axis_size = m_inc_angle->size();
    std::vector<double> angles = m_inc_angle->getBinCenters();
    result.reserve(axis_size);
    for (size_t i = 0; i < axis_size; ++i) {
        const double result_angle = angles[i];
        result.emplace_back(m_wl, result_angle);
        if (!inc_limits.isInRange(result_angle))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }

    return result;
}

void AngularSpecScan::setFootprintFactor(const IFootprintFactor* f_factor)
{
    m_footprint.reset(f_factor ? f_factor->clone() : nullptr);
}

void AngularSpecScan::setWavelengthResolution(const ScanResolution& resolution)
{
    m_wl_resolution.reset(resolution.clone());
    if (m_wl_resolution->empty())
        return;

    RealLimits limits = m_wl_resolution->distribution()->limits();
    if (!limits.hasLowerLimit() || limits.lowerLimit() < wl_limits.lowerLimit()) {
        limits.setLowerLimit(wl_limits.lowerLimit());
        m_wl_resolution->setDistributionLimits(limits);
    }
}

void AngularSpecScan::setAngleResolution(const ScanResolution& resolution)
{
    m_inc_resolution.reset(resolution.clone());
    if (m_inc_resolution->empty())
        return;

    RealLimits limits = m_inc_resolution->distribution()->limits();
    if (!limits.hasLowerLimit() || limits.lowerLimit() < inc_limits.lowerLimit())
        limits.setLowerLimit(inc_limits.lowerLimit());
    if (!limits.hasUpperLimit() || limits.upperLimit() > inc_limits.upperLimit())
        limits.setUpperLimit(inc_limits.upperLimit());
    m_inc_resolution->setDistributionLimits(limits);
}

std::vector<double> AngularSpecScan::footprint(size_t i, size_t n_elements) const
{
    if (i + n_elements > numberOfSimulationElements())
        throw std::runtime_error("Error in AngularSpecScan::footprint: given index exceeds the "
                                 "number of simulation elements");

    std::vector<double> result(n_elements, 1.0);
    if (!m_footprint)
        return result;

    const std::vector<double> angles = m_inc_angle->getBinCenters();
    for (size_t j = i, k = 0; j < i + n_elements; ++j, ++k)
        if (inc_limits.isInRange(angles[j]))
            result[k] = m_footprint->calculate(angles[j]);
    return result;
}

size_t AngularSpecScan::numberOfSimulationElements() const
{
    return m_inc_angle->size();
}

std::string AngularSpecScan::print() const
{
    std::stringstream result;
    const std::string axis_def = PythonFormatting::indent() + "axis = ";
    result << axis_def
           << PythonFormatting::printAxis(*coordinateAxis(), BornAgain::UnitsRad,
                                          axis_def.size())
           << "\n";

    result << PythonFormatting::indent() << "scan = ";
    result << "ba.AngularSpecScan(" << PythonFormatting::printDouble(m_wl) << ", axis)";

    if (m_footprint) {
        result << "\n";
        result << *m_footprint << "\n";
        result << PythonFormatting::indent() << "scan.setFootprintFactor(footprint)";
    }
    if (!m_inc_resolution->empty()) {
        result << "\n";
        result << *m_inc_resolution << "\n";
        result << PythonFormatting::indent() << "scan.setAngleResolution(resolution)";
    }
    if (!m_wl_resolution->empty()) {
        result << "\n";
        result << *m_wl_resolution << "\n";
        result << PythonFormatting::indent() << "scan.setWavelengthResolution(resolution)";
    }
    return result.str();
}

void AngularSpecScan::checkInitialization()
{
    if (m_wl <= 0.0)
        throw std::runtime_error(
            "Error in AngularSpecScan::checkInitialization: wavelength shell be positive");

    std::vector<double> axis_values = m_inc_angle->getBinCenters();
    if (!std::is_sorted(axis_values.begin(), axis_values.end()))
        throw std::runtime_error("Error in AngularSpecScan::checkInitialization: q-vector values "
                                 "shall be sorted in ascending order.");

    // TODO: check for inclination angle limits after switching to pointwise resolution.
}
