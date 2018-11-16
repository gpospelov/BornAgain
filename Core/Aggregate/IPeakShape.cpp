// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IPeakShape.cpp
//! @brief     Implements the interface IPeakShape and subclasses.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IPeakShape.h"
#include "MathConstants.h"

#include <limits>

namespace {
double KentDistribution(double x, double kappa);
}

IPeakShape::~IPeakShape() =default;

IsotropicGaussPeakShape::IsotropicGaussPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity)
    , m_domainsize(domainsize)
{}

IsotropicGaussPeakShape::~IsotropicGaussPeakShape() =default;

IsotropicGaussPeakShape* IsotropicGaussPeakShape::clone() const
{
    return new IsotropicGaussPeakShape(m_max_intensity, m_domainsize);
}

double IsotropicGaussPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    double exponent = -q_norm*m_domainsize*m_domainsize/2.0;
    return m_max_intensity * std::exp(exponent);
}

double IsotropicGaussPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    return evaluate(q - q_lattice_point);
}

IsotropicLorentzPeakShape::IsotropicLorentzPeakShape(double max_intensity, double domainsize)
    : m_max_intensity(max_intensity)
    , m_domainsize(domainsize)
{}

IsotropicLorentzPeakShape::~IsotropicLorentzPeakShape() =default;

IsotropicLorentzPeakShape* IsotropicLorentzPeakShape::clone() const
{
    return new IsotropicLorentzPeakShape(m_max_intensity, m_domainsize);
}

double IsotropicLorentzPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    double lorentz = 1.0 / (1.0 + m_domainsize*m_domainsize*q_norm);
    return m_max_intensity * lorentz * lorentz;
}

double IsotropicLorentzPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    return evaluate(q - q_lattice_point);
}

GaussKentPeakShape::GaussKentPeakShape(double max_intensity, double radial_size, double kappa)
    : m_max_intensity(max_intensity)
    , m_radial_size(radial_size)
    , m_kappa(kappa)
{}

GaussKentPeakShape::~GaussKentPeakShape() =default;

GaussKentPeakShape* GaussKentPeakShape::clone() const
{
    return new GaussKentPeakShape(m_max_intensity, m_radial_size, m_kappa);
}

double GaussKentPeakShape::evaluate(const kvector_t q, const kvector_t q_lattice_point) const
{
    double q_r = q.mag();
    double q_lat_r = q_lattice_point.mag();
    double dq2 = (q_r - q_lat_r)*(q_r - q_lat_r);
    double radial_part = m_max_intensity * std::exp(-dq2*m_radial_size*m_radial_size/2.0);
    double angular_part = 1.0;
    if (q_r*q_lat_r > 0.0) {
        double dot_norm = q.dot(q_lattice_point)/q_r/q_lat_r;
        angular_part = KentDistribution(dot_norm, m_kappa);
    }
    return radial_part*angular_part;
}

namespace {
double KentDistribution(double x, double kappa) {
    static double maxkappa = std::log(1.0/std::numeric_limits<double>::epsilon())/2.0;
    if (kappa<=0.0) {
        return 1.0/(4.0*M_PI);
    }
    double prefactor = kappa / (4.0*M_PI);
    if (kappa>maxkappa) {
        return 2.0*prefactor*std::exp(kappa*(x-1.0));
    }
    return prefactor*std::exp(kappa*x)/std::sinh(kappa);
}
}
