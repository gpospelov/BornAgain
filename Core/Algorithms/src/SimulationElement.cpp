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
#include "Detector.h"

#include <Bin.h>

SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i,
                                     double alpha_min, double alpha_max, double phi_min,
                                     double phi_max)
    : m_wavelength(wavelength), m_alpha_i(alpha_i), m_phi_i(phi_i), m_alpha_min(alpha_min),
      m_alpha_max(alpha_max), m_phi_min(phi_min), m_phi_max(phi_max), m_intensity(0.0)
{
    m_pixel_map.reset(new AngularPixelMap(m_alpha_min, m_phi_min, m_alpha_max-m_alpha_min,
                                          m_phi_max-m_phi_min));
    initPolarization();
}

SimulationElement::SimulationElement(const SimulationElement &other)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i), m_phi_i(other.m_phi_i),
      m_alpha_min(other.m_alpha_min), m_alpha_max(other.m_alpha_max), m_phi_min(other.m_phi_min),
      m_phi_max(other.m_phi_max), m_intensity(other.m_intensity)
{
    m_pixel_map.reset(other.m_pixel_map->clone());
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

kvector_t SimulationElement::getKI() const
{
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
    return k_i;
}

kvector_t SimulationElement::getMeanKF() const
{
    return m_pixel_map->getK(0.5, 0.5, m_wavelength);
}

kvector_t SimulationElement::getMeanQ() const
{
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
    Bin1D alpha_f_bin(m_alpha_min, m_alpha_max);
    Bin1D phi_f_bin(m_phi_min, m_phi_max);
    Bin1DKVector k_f_bin(m_wavelength, alpha_f_bin, phi_f_bin);
    return k_i - k_f_bin.getMidPoint();
//    return k_i - getMeanKF();
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
    boost::swap(this->m_pixel_map, other.m_pixel_map);
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
