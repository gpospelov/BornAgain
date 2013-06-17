// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorCylinder.cpp
//! @brief     Implements class FormFactorCylinder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCylinder.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorCylinder::FormFactorCylinder(double height, double radius)
{
    setName("FormFactorCylinder");
    m_height = height;
    m_radius = radius;
    init_parameters();
}

//! Registers some class members for later access via parameter pool

void FormFactorCylinder::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("radius", &m_radius);
}

FormFactorCylinder* FormFactorCylinder::clone() const
{
    return new FormFactorCylinder(m_height, m_radius);
}

complex_t FormFactorCylinder::evaluate_for_q(const cvector_t& q) const
{
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = q.z()*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half) *
        std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t qrR = q.magxy()*R;
    complex_t J1_qrR_div_qrR = std::abs(qrR) > Numeric::double_epsilon ?
        MathFunctions::Bessel_J1(std::abs(qrR))/(std::abs(qrR)) :
        0.5;
    complex_t radial_part = 2*M_PI*R*R*J1_qrR_div_qrR;

    return radial_part*z_part;
}


