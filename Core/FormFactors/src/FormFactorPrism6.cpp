// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorPrism6.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"

FormFactorPrism6::FormFactorPrism6(double height, double half_side)
{
    setName("FormFactorPrism6");
    m_height = height;
    m_half_side = half_side;
    m_root3 = std::sqrt(3.0);
    init_parameters();
}

void FormFactorPrism6::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("half_side", &m_half_side);
}

FormFactorPrism6* FormFactorPrism6::clone() const
{
      return new FormFactorPrism6(m_height, m_half_side);
}

complex_t FormFactorPrism6::evaluate_for_q(const cvector_t &q) const
{
    complex_t qz = q.z();
    double R = m_half_side;
    double H = m_height;

    complex_t qzH_half = qz*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half)*
        std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (std::abs(q.x())==0.0 && std::abs(q.y())==0.0) {
        xy_part = 2*m_root3*R*R;
    } else {
      complex_t qxRdivr3 = (q.x()*R)/m_root3;
        if (std::abs(3.0*q.y()*q.y()-q.x()*q.x())==0.0) {
            xy_part = m_root3 * (q.y()*R*q.y()*R*
                                 MathFunctions::Sinc(qxRdivr3) *
                                 MathFunctions::Sinc(q.y()*R) +
                      std::cos(qxRdivr3) -
                      std::cos(q.y()*R) * std::cos(qxRdivr3));
        } else {

            xy_part = (4.0*m_root3*(q.y()*R*q.y()*R*
                                    MathFunctions::Sinc(qxRdivr3) *
                                    MathFunctions::Sinc(q.y()*R) +
                       std::cos(qxRdivr3) -
                       std::cos(q.y()*R) * std::cos(qxRdivr3)))/
                                    (3.0*q.y()*q.y()-q.x()*q.x());
        }
    }

    return xy_part*z_part;
}
