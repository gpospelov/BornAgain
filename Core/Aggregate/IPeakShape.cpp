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

GaussPeakShape::GaussPeakShape(double domainsize)
    : m_domainsize(domainsize)
{}

GaussPeakShape::~GaussPeakShape() =default;

GaussPeakShape* GaussPeakShape::clone() const
{
    return new GaussPeakShape(m_domainsize);
}

double GaussPeakShape::evaluate(const kvector_t q) const
{
    double q_norm = q.mag2();
    double exponent = -q_norm*m_domainsize*m_domainsize/2.0;
    return m_domainsize * std::sqrt(M_TWOPI) * std::exp(exponent);
}
