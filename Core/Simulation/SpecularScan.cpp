// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularScan.cpp
//! @brief     Implements SpecularScan class tree.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularScan.h"
#include "FixedBinAxis.h"
#include "IFootprintFactor.h"
#include "PointwiseAxis.h"
#include "RealLimits.h"
#include "SpecularSimulationElement.h"

namespace {
const RealLimits inc_angle_limits = RealLimits::limited(0.0, M_PI_2);
const RealLimits qz_limits = RealLimits::nonnegative();
}

ISpecularScan::ISpecularScan(SPECULAR_DATA_TYPE data_type)
    : m_data_type(data_type)
{}

ISpecularScan::~ISpecularScan() = default;

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

QSpecScan::QSpecScan(std::vector<double> qs_nm)
    : ISpecularScan(SPECULAR_DATA_TYPE::q)
    , m_qs(std::make_unique<PointwiseAxis>("qs", std::move(qs_nm)))
{
    checkInitialization();
}

QSpecScan::QSpecScan(const IAxis& qs_nm)
    : ISpecularScan(SPECULAR_DATA_TYPE::q)
    , m_qs(qs_nm.clone())
{
    checkInitialization();
}

QSpecScan::QSpecScan(int nbins, double qz_min, double qz_max)
    : ISpecularScan(SPECULAR_DATA_TYPE::q)
    , m_qs(std::make_unique<FixedBinAxis>("qs", nbins, qz_min, qz_max))
{
    checkInitialization();
}

QSpecScan::~QSpecScan() = default;

QSpecScan* QSpecScan::clone() const
{
    return new QSpecScan(*m_qs);
}

//! Generates simulation elements for specular simulations
std::vector<SpecularSimulationElement> QSpecScan::generateSimulationElements() const
{
    std::vector<SpecularSimulationElement> result;

    const size_t axis_size = m_qs->size();
    std::vector<double> qs = m_qs->getBinCenters();
    result.reserve(axis_size);
    for (size_t i = 0; i < axis_size; ++i) {
        const double kz = qs[i] / 2.0;
        result.emplace_back(kz);
        if (!qz_limits.isInRange(kz))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }

    return result;
}

double QSpecScan::footprint(size_t i) const
{
    if (i >= numberOfSimulationElements())
        throw std::runtime_error("Error in QSpecScan::footprint: given index exceeds the "
                                 "number of simulation elements");
    return 1.0;
}

//! Returns the number of simulation elements
size_t QSpecScan::numberOfSimulationElements() const
{
    return m_qs->size();
}

void QSpecScan::checkInitialization()
{
    std::vector<double> axis_values = m_qs->getBinCenters();
    if (!std::is_sorted(axis_values.begin(), axis_values.end()))
        throw std::runtime_error("Error in QSpecScan::checkInitialization: q-vector values shall "
                                 "be sorted in ascending order.");

    if (!qz_limits.isInRange(axis_values.front()))
        throw std::runtime_error("Error in QSpecScan::checkInitialization: q-vector values are out "
                                 "of acceptable range.");
}
