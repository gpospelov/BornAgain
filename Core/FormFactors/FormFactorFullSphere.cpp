// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSphere.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorFullSphere::FormFactorFullSphere(double radius)
: m_radius(radius)
{
    setName(FFFullSphereType);
    check_initialization();
    init_parameters();
}

bool FormFactorFullSphere::check_initialization() const
{
    return true;
}

void FormFactorFullSphere::init_parameters()
{
    clearParameterPool();
    registerParameter(Radius, &m_radius, AttLimits::n_positive());
}


FormFactorFullSphere* FormFactorFullSphere::clone() const
{
    return new FormFactorFullSphere(m_radius);
}

void FormFactorFullSphere::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorFullSphere::evaluate_for_q(const cvector_t q) const
{
    complex_t qz = q.z();
    double R = m_radius;

    complex_t iqzR = complex_t(0.0, 1.0)*qz*R;
    complex_t z_part = std::exp(iqzR);

    complex_t qR = std::sqrt( q.x()*q.x() + q.y()*q.y() + qz*qz )*R;
    double volume = 4*Units::PI*R*R*R/3;
    complex_t radial;
    if (std::abs(qR) < Numeric::double_epsilon) {
        radial = volume;
    }
    else {
        radial = 3*volume*(sin(qR) - qR*cos(qR))/(qR*qR*qR);
    }

    return radial*z_part;
}
