// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularDataHandler.cpp
//! @brief     Implements SpecularDataHandler class tree.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularDataHandler.h"
#include "IAxis.h"
#include "IFootprintFactor.h"
#include "RealLimits.h"
#include "SpecularSimulationElement.h"

namespace {
const RealLimits inc_angle_limits = RealLimits::limited(0.0, M_PI_2);
const RealLimits qz_limits = RealLimits::positive();
}

ISpecularDataHandler::ISpecularDataHandler(SPECULAR_DATA_TYPE data_type)
    : m_data_type(data_type)
{}

ISpecularDataHandler::~ISpecularDataHandler() = default;

SpecularDataHandlerAng::SpecularDataHandlerAng(double wl, std::unique_ptr<IAxis> inc_angle,
                                               const IFootprintFactor* footprint)
    : ISpecularDataHandler(SPECULAR_DATA_TYPE::angle)
    , m_wl(wl)
    , m_inc_angle(std::move(inc_angle))
    , m_footprint(footprint ? footprint->clone() : nullptr)
{
    if (!m_inc_angle)
        throw std::runtime_error(
                "Error in SpecularDataHolderAngle: empty inclination angle axis passed.");
}

SpecularDataHandlerAng* SpecularDataHandlerAng::clone() const
{
    return new SpecularDataHandlerAng(m_wl, std::unique_ptr<IAxis>(m_inc_angle->clone()),
                                      m_footprint.get());
}

SpecularDataHandlerAng::~SpecularDataHandlerAng() = default;

std::vector<SpecularSimulationElement> SpecularDataHandlerAng::generateSimulationElements() const
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

double SpecularDataHandlerAng::footprint(size_t i) const
{
    if (!m_footprint)
        return 1.0;

    return m_footprint->calculate(m_inc_angle->getBinCenter(i));
}

size_t SpecularDataHandlerAng::numberOfSimulationElements() const
{
    return m_inc_angle->size();
}

SpecularDataHandlerTOF::SpecularDataHandlerTOF(double inc_angle, std::unique_ptr<IAxis> qz,
                                               const IFootprintFactor* footprint)
    : ISpecularDataHandler(SPECULAR_DATA_TYPE::lambda)
    , m_inc_angle(inc_angle)
    , m_qs(std::move(qz))
    , m_footprint(footprint ? footprint->clone() : nullptr)
{}

SpecularDataHandlerTOF::~SpecularDataHandlerTOF() = default;

SpecularDataHandlerTOF* SpecularDataHandlerTOF::clone() const
{
    return new SpecularDataHandlerTOF(m_inc_angle, std::unique_ptr<IAxis>(m_qs->clone()),
                                      m_footprint.get());
}

//! Generates simulation elements for specular simulations
std::vector<SpecularSimulationElement> SpecularDataHandlerTOF::generateSimulationElements() const
{
    std::vector<SpecularSimulationElement> result;

    const size_t axis_size = m_qs->size();
    std::vector<double> qzs = m_qs->getBinCenters();
    result.reserve(axis_size);
    for (size_t i = 0; i < axis_size; ++i) {
        const double kz = qzs[i] / 2.0;
        result.emplace_back(kz);
        if (!qz_limits.isInRange(kz))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }

    return result;
}

//! Returns footprint correction factor for simulation element with index _i_
double SpecularDataHandlerTOF::footprint(size_t) const
{
    if (!m_footprint)
        return 1.0;

    return m_footprint->calculate(m_inc_angle);
}

//! Returns the number of simulation elements
size_t SpecularDataHandlerTOF::numberOfSimulationElements() const
{
    return m_qs->size();
}
