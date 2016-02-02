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
#include "IDetector2D.h"

#include <Bin.h>

SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i,
                                     const IPixelMap *pixelmap)
    : m_wavelength(wavelength), m_alpha_i(alpha_i), m_phi_i(phi_i), m_intensity(0.0)
{
    mP_pixel_map.reset(pixelmap->clone());
    initPolarization();
}

SimulationElement::SimulationElement(const SimulationElement &other)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i), m_phi_i(other.m_phi_i),
      m_intensity(other.m_intensity)
{
    mP_pixel_map.reset(other.mP_pixel_map->clone());
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

SimulationElement::SimulationElement(const SimulationElement &other, double x, double y)
    : m_wavelength(other.m_wavelength), m_alpha_i(other.m_alpha_i), m_phi_i(other.m_phi_i),
      m_intensity(other.m_intensity)
{
    mP_pixel_map.reset(other.mP_pixel_map->createZeroSizeMap(x, y));
    m_polarization = other.m_polarization;
    m_analyzer_operator = other.m_analyzer_operator;
}

kvector_t SimulationElement::getKI() const
{
    kvector_t k_i;
    k_i.setLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
    return k_i;
}

kvector_t SimulationElement::getMeanKF() const
{
    return mP_pixel_map->getK(0.5, 0.5, m_wavelength);
}

kvector_t SimulationElement::getMeanQ() const
{
    return getKI() - getMeanKF();
}

kvector_t SimulationElement::getQ(double x, double y) const
{
    return getKI() - mP_pixel_map->getK(x, y, m_wavelength);
}

void SimulationElement::swapContent(SimulationElement &other)
{
    std::swap(this->m_wavelength, other.m_wavelength);
    std::swap(this->m_alpha_i, other.m_alpha_i);
    std::swap(this->m_phi_i, other.m_phi_i);
    std::swap(this->m_intensity, other.m_intensity);
    std::swap(this->m_polarization, other.m_polarization);
    std::swap(this->m_analyzer_operator, other.m_analyzer_operator);
    boost::swap(this->mP_pixel_map, other.mP_pixel_map);
}

void SimulationElement::initPolarization()
{
    m_polarization = Eigen::Matrix2cd::Identity();
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

double SimulationElement::getAlpha(double x, double y) const
{
    kvector_t kf = getK(x, y);
    return M_PI_2 - kf.theta();
}

double SimulationElement::getPhi(double x, double y) const
{
    kvector_t kf = getK(x, y);
    return kf.phi();
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
