// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPrism3.cpp
//! @brief     Implements class FormFactorPrism3.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorPrism3.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"

FormFactorPrism3::FormFactorPrism3(double height, double half_side)
{
    setName("FormFactorPrism3");
    m_height = height;
    m_half_side = half_side;
    m_root3 = std::sqrt(3.0);
    init_parameters();
}

void FormFactorPrism3::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height",& m_height);
    getParameterPool()->registerParameter("half_side",& m_half_side);
}

FormFactorPrism3* FormFactorPrism3::clone() const
{
    FormFactorPrism3 *p_clone = new FormFactorPrism3(m_height, m_half_side );
    return p_clone;
}

complex_t FormFactorPrism3::evaluate_for_q(const cvector_t& q) const
{
    complex_t qz = q.z();
    double R = m_half_side;
    double H = m_height;

    complex_t qzH_half = qz*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half)*
        std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (std::abs(q.x())==0.0 && std::abs(q.y())==0.0) {
        xy_part = m_root3*R*R;
    }
    else {
        complex_t r3qyR = m_root3*q.y()*R;
        complex_t expminiqyRdivr3 =
            std::exp(-complex_t(0.0, 1.0)*q.y()*R/m_root3);
        if (std::abs(q.x()*q.x()-3.0*q.y()*q.y())==0.0) {
            xy_part = complex_t(0.0, 1.0)*m_root3*expminiqyRdivr3*
                   (std::sin(r3qyR)-r3qyR*std::exp(complex_t(0.0, 1.0)*r3qyR))/
                q.x()/q.x();
        } else {
            complex_t qxR = q.x()*R;
            xy_part = std::exp(complex_t(0.0, 1.0)*r3qyR) -
                std::cos(qxR)-complex_t(0.0, 1.0)*r3qyR*
                MathFunctions::Sinc(qxR);
            xy_part *= 2.0*m_root3*expminiqyRdivr3/
                (q.x()*q.x()-3.0*q.y()*q.y());
        }
    }

    return xy_part*z_part;
}
