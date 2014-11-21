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

#include "MathFunctions.h"

FormFactorPrism6::FormFactorPrism6(double radius, double height)
{
    setName("FormFactorPrism6");
    m_height = height;
    m_radius = radius;
    m_root3 = std::sqrt(3.0);
    init_parameters();
}

void FormFactorPrism6::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("radius", &m_radius);
}

FormFactorPrism6* FormFactorPrism6::clone() const
{
      FormFactorPrism6 *result = new FormFactorPrism6(m_radius, m_height);
      result->setName(getName());
      return result;
}

complex_t FormFactorPrism6::evaluate_for_q(const cvector_t& q) const
{
    complex_t qz = q.z();
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = qz*H/2.0;
    complex_t z_part = H*MathFunctions::Sinc(qzH_half)*
        std::exp(complex_t(0.0, 1.0)*qzH_half);

    complex_t xy_part = complex_t(0.0, 0.0);
    if (std::abs(q.x())==0.0 && std::abs(q.y())==0.0) {

        xy_part = 3.*m_root3/2.*R*R;

    } else {

        if (std::abs(3.0*q.y()*q.y()-q.x()*q.x())==0.0) {

            complex_t qyRr3_half = q.y()*R*m_root3/2.;
            xy_part = R*R*m_root3/2.0*MathFunctions::Sinc(qyRr3_half)*(
                        MathFunctions::Sinc(qyRr3_half)
                        + 2.0*std::cos(qyRr3_half)
                        );

        } else {

            complex_t qxR_half = (q.x()*R)/2.0;
            complex_t qyRr3_half = q.y()*R*m_root3/2.;

            xy_part = (4.0*m_root3*(
                      3.0/4.0*q.y()*R*q.y()*R*MathFunctions::Sinc(qxR_half) *
                      MathFunctions::Sinc(qyRr3_half)
                      + std::cos(2.0*qxR_half) -
                       std::cos(qyRr3_half) * std::cos(qxR_half)
                          ) )/(3.0*q.y()*q.y()-q.x()*q.x());
        }
    }

    return xy_part*z_part;
}


