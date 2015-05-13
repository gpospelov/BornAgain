// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/SimulationElement.cpp
//! @brief     Implements class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationElement.h"

SimulationElement::SimulationElement()
    : m_wavelength(0.0), m_alpha_i(0.0), m_phi_i(0.0), m_alpha_min(0.0), m_alpha_max(0.0),
      m_phi_min(0.0), m_phi_max(0.0), m_intensity(0.0)
{
    initPolarization();
}

SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i,
                                     double alpha_min, double alpha_max, double phi_min,
                                     double phi_max)
    : m_wavelength(wavelength), m_alpha_i(alpha_i), m_phi_i(phi_i), m_alpha_min(alpha_min),
      m_alpha_max(alpha_max), m_phi_min(phi_min), m_phi_max(phi_max), m_intensity(0.0)
{
    initPolarization();
}

SimulationElement::SimulationElement(const SimulationElement &other)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i), m_phi_i(other.m_phi_i),
      m_alpha_min(other.m_alpha_min), m_alpha_max(other.m_alpha_max), m_phi_min(other.m_phi_min),
      m_phi_max(other.m_phi_max), m_intensity(other.m_intensity)
{
    m_polarization = other.m_polarization;
    m_analyzer_operator = other.m_analyzer_operator;
}

SimulationElement &SimulationElement::operator=(const SimulationElement &other)
{
    if (this != &other) {
        SimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

void SimulationElement::swapContent(SimulationElement &other)
{
    std::swap(this->m_wavelength, other.m_wavelength);
    std::swap(this->m_alpha_i, other.m_alpha_i);
    std::swap(this->m_phi_i, other.m_phi_i);
    std::swap(this->m_alpha_min, other.m_alpha_min);
    std::swap(this->m_alpha_max, other.m_alpha_max);
    std::swap(this->m_phi_min, other.m_phi_min);
    std::swap(this->m_phi_max, other.m_phi_max);
    std::swap(this->m_intensity, other.m_intensity);
    std::swap(this->m_polarization, other.m_polarization);
    std::swap(this->m_analyzer_operator, other.m_analyzer_operator);
}

void SimulationElement::initPolarization()
{
    m_polarization = Eigen::Matrix2cd::Identity();
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

void AddElementsWithWeight(std::vector<SimulationElement>::const_iterator first,
                           std::vector<SimulationElement>::const_iterator last,
                           std::vector<SimulationElement>::iterator result, double weight)
{
    for (std::vector<SimulationElement>::const_iterator it = first; it != last; ++it, ++result) {
        result->addIntensity(it->getIntensity() * weight);
    }
}

void setAllElementIntensities(std::vector<SimulationElement>::iterator first,
                              std::vector<SimulationElement>::iterator last, double intensity)
{
    for (std::vector<SimulationElement>::iterator it = first; it != last; ++it) {
        it->setIntensity(intensity);
    }
}
