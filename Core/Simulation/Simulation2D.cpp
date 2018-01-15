// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation2D.cpp
//! @brief     Implements class Simulation2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Simulation2D.h"
#include "SimulationElement.h"


Simulation2D::Simulation2D(const MultiLayer& p_sample)
    : Simulation(p_sample)
{}

Simulation2D::Simulation2D(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation(p_sample_builder)
{}

Simulation2D::Simulation2D(const Simulation2D& other)
    : Simulation(other)
    , m_sim_elements(other.m_sim_elements)
{}

void Simulation2D::normalizeIntensity(size_t index, double beam_intensity)
{
    SimulationElement& element = m_sim_elements[index];
    double sin_alpha_i = std::abs(std::sin(element.getAlphaI()));
    if (sin_alpha_i == 0.0)
        sin_alpha_i = 1.0;
    const double solid_angle = element.getSolidAngle();
    element.setIntensity(element.getIntensity() * beam_intensity * solid_angle / sin_alpha_i);
}
