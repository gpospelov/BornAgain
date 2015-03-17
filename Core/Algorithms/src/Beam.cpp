// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Beam.cpp
//! @brief     Implements class Beam.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Beam.h"
#include "Exceptions.h"
#include "Numeric.h"
#include <Eigen/LU>


Beam::Beam()
: m_lambda(1.0)
, m_alpha(0.0)
, m_phi(0.0)
, m_intensity(1.0)
{
    setName("Beam");
    init_parameters();
    initPolarization();
}

Beam::Beam(const Beam& other) : IParameterized(), m_lambda(other.m_lambda),
		m_alpha(other.m_alpha), m_phi(other.m_phi),
		m_intensity(other.m_intensity), m_polarization(other.m_polarization)
{
    setName(other.getName());
    init_parameters();
}

Beam& Beam::operator=(const Beam& other)
{
    if( this !=& other)
    {
        Beam tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

cvector_t Beam::getCentralK() const
{
    cvector_t k;
    k.setLambdaAlphaPhi(m_lambda, m_alpha, m_phi);
    return k;
}

void Beam::setCentralK(double lambda, double alpha_i, double phi_i)
{
    if (alpha_i >0) alpha_i = - alpha_i;
    m_lambda = lambda;
    m_alpha = alpha_i;
    m_phi = phi_i;
}

void Beam::setPolarization(const Eigen::Matrix2cd &polarization)
{
    if (checkPolarization(polarization)) {
        m_polarization = polarization;
    }
    else {
        throw Exceptions::ClassInitializationException("The given polarization"
                " matrix cannot represent a physical density matrix");
    }
}

void Beam::SetSpinUpFraction(double up_fraction)
{
    if (up_fraction < 0.0 || up_fraction > 1.0) {
        throw Exceptions::ClassInitializationException("The fraction of spin-up"
                " states must be between 0.0 and 1.0");
    }
    m_polarization.setZero();
    m_polarization(0,0) = up_fraction;
    m_polarization(1,1) = 1.0 - up_fraction;
}

bool Beam::checkPolarization(const Eigen::Matrix2cd &polarization) const
{
    if (std::imag( (complex_t)polarization(0,0) ) != 0.0) return false;
    if (polarization(0,0)+polarization(1,1) != 1.0) return false;
    if (polarization(0,1) != std::conj( (complex_t)polarization(1,0))) return false;
    if (std::abs( (complex_t)polarization.determinant() ) < 0.0) return false;

    return true;
}

void Beam::init_parameters()
{
    clearParameterPool();
    registerParameter("intensity", &m_intensity);
    registerParameter("wavelength", &m_lambda, AttLimits::positive());
    registerParameter("alpha", &m_alpha);
    registerParameter("phi", &m_phi);
}

void Beam::swapContent(Beam& other)
{
    std::swap(this->m_lambda, other.m_lambda);
    std::swap(this->m_alpha, other.m_alpha);
    std::swap(this->m_phi, other.m_phi);
    std::swap(this->m_intensity, other.m_intensity);
    std::swap(this->m_polarization, other.m_polarization);
}

void Beam::initPolarization()
{
    m_polarization.setZero();
    m_polarization(0,0) = 0.5;
    m_polarization(1,1) = 0.5;
}

void Beam::print(std::ostream& ostr) const
{
    ostr << "Beam: '" << getName() << "' " << m_parameters;
}
