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

IsotropicLorentzPeakShape *IsotropicLorentzPeakShape::clone() const
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
