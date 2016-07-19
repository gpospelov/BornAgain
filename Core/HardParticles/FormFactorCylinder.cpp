// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticles/FormFactorCylinder.cpp
//! @brief     Implements class FormFactorCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCylinder.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorCylinder::FormFactorCylinder(double radius, double height)
{
    setName(FFCylinderType);
    m_radius = radius;
    m_height = height;
    check_initialization();
    init_parameters();
}

bool FormFactorCylinder::check_initialization() const
{
    return true;
}

void FormFactorCylinder::init_parameters()
{
    clearParameterPool();
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}

FormFactorCylinder* FormFactorCylinder::clone() const
{
    return new FormFactorCylinder(m_radius, m_height);
}

void FormFactorCylinder::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorCylinder::evaluate_for_q(const cvector_t q) const
{
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = q.z() * H / 2.0;
    complex_t z_part = H * MathFunctions::sinc(qzH_half) * exp_I(qzH_half);
    complex_t qxy = std::sqrt(q.x() * q.x() + q.y() * q.y());
    complex_t radial_part = Units::PI2 * R * R * MathFunctions::Bessel_J1c(qxy * R);
    complex_t result = radial_part * z_part;

    return result;
}
