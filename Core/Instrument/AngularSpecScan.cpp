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
#include "RealLimits.h"
#include "SpecularSimulationElement.h"

namespace {
const RealLimits inc_angle_limits = RealLimits::limited(0.0, M_PI_2);
}

AngularSpecScan::AngularSpecScan(double wl, std::vector<double> inc_angle)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(std::make_unique<PointwiseAxis>("inc_angles", std::move(inc_angle)))
{
    checkInitialization();
}

AngularSpecScan::AngularSpecScan(double wl, const IAxis& inc_angle)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(inc_angle.clone())
{
    checkInitialization();
}

AngularSpecScan::AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max)
    : ISpecularScan(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(std::make_unique<FixedBinAxis>("inc_angles", nbins, alpha_i_min, alpha_i_max))
{
    checkInitialization();
}

AngularSpecScan* AngularSpecScan::clone() const
{
    auto result = std::make_unique<AngularSpecScan>(m_wl, *m_inc_angle);
    result->setFootprintFactor(m_footprint.get());
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
        if (!inc_angle_limits.isInRange(result_angle))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }

    return result;
}

void AngularSpecScan::setFootprintFactor(const IFootprintFactor* f_factor)
{
    m_footprint.reset(f_factor ? f_factor->clone() : nullptr);
}

double AngularSpecScan::footprint(size_t i) const
{
    if (i >= numberOfSimulationElements())
        throw std::runtime_error("Error in AngularSpecScan::footprint: given index exceeds the "
                                 "number of simulation elements");

    const double angle_value = m_inc_angle->getBinCenter(i);
    if (!m_footprint || !inc_angle_limits.isInRange(angle_value))
        return 1.0;

    return m_footprint->calculate(angle_value);
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
