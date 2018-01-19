// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SimulationElement.cpp
//! @brief     Implements class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SimulationElement.h"
#include "IPixel.h"
#include "SpecularData.h"

SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i,
                                     std::unique_ptr<IPixel> pixel)
    : m_wavelength(wavelength)
    , m_alpha_i(alpha_i)
    , m_phi_i(phi_i)
    , m_intensity(0.0)
    , mP_pixel(std::move(pixel))
{
}

SimulationElement::SimulationElement(const SimulationElement& other)
    : m_polarization(other.m_polarization)
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_phi_i(other.m_phi_i)
    , m_intensity(other.m_intensity)
{
    mP_pixel.reset(other.mP_pixel->clone());
    if (other.m_specular_data)
        m_specular_data.reset(new SpecularData(*other.m_specular_data));
}

SimulationElement::SimulationElement(const SimulationElement& other, double x, double y)
    : m_polarization(other.m_polarization)
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_phi_i(other.m_phi_i)
    , m_intensity(other.m_intensity)
{
    mP_pixel.reset(other.mP_pixel->createZeroSizePixel(x, y));
    if (other.m_specular_data)
        m_specular_data.reset(new SpecularData(*other.m_specular_data));
}

SimulationElement::SimulationElement(SimulationElement&& other) noexcept
    : m_polarization(std::move(other.m_polarization))
    , m_wavelength(other.m_wavelength)
    , m_alpha_i(other.m_alpha_i)
    , m_phi_i(other.m_phi_i)
    , m_intensity(other.m_intensity)
    , mP_pixel(std::move(other.mP_pixel))
    , m_specular_data(std::move(other.m_specular_data))
{
}

SimulationElement::~SimulationElement() = default;

SimulationElement& SimulationElement::operator=(const SimulationElement &other)
{
    if (this != &other) {
        SimulationElement tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

kvector_t SimulationElement::getKi() const
{
    return vecOfLambdaAlphaPhi(m_wavelength, m_alpha_i, m_phi_i);
}

kvector_t SimulationElement::getMeanKf() const
{
    return mP_pixel->getK(0.5, 0.5, m_wavelength);
}

//! Returns outgoing wavevector Kf for in-pixel coordinates x,y.
//! In-pixel coordinates take values from 0 to 1.
kvector_t SimulationElement::getKf(double x, double y) const {
    return mP_pixel->getK(x, y, m_wavelength);
}

kvector_t SimulationElement::getMeanQ() const
{
    return getKi() - getMeanKf();
}

//! Returns scattering vector Q, with Kf determined from in-pixel coordinates x,y.
//! In-pixel coordinates take values from 0 to 1.
kvector_t SimulationElement::getQ(double x, double y) const
{
    return getKi() - mP_pixel->getK(x, y, m_wavelength);
}

void SimulationElement::swapContent(SimulationElement &other)
{
    m_polarization.swapContent(other.m_polarization);
    std::swap(m_wavelength, other.m_wavelength);
    std::swap(m_alpha_i, other.m_alpha_i);
    std::swap(m_phi_i, other.m_phi_i);
    std::swap(m_intensity, other.m_intensity);
    std::swap(mP_pixel, other.mP_pixel);
    std::swap(m_specular_data, other.m_specular_data);
}

double SimulationElement::getAlpha(double x, double y) const
{
    return M_PI_2 - getKf(x,y).theta();
}

double SimulationElement::getPhi(double x, double y) const
{
    return getKf(x,y).phi();
}

void SimulationElement::setSpecular()
{
    m_specular_data.reset(new SpecularData);
}

void SimulationElement::setSpecular(std::unique_ptr<SpecularData> specular_data)
{
    m_specular_data = std::move(specular_data);
}

double SimulationElement::getIntegrationFactor(double x, double y) const {
    return mP_pixel->getIntegrationFactor(x, y);
}

double SimulationElement::getSolidAngle() const {
    return mP_pixel->getSolidAngle();
}
