// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPrism3.cpp
//! @brief     Implements class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism3.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"

using namespace  BornAgain;

FormFactorPrism3::FormFactorPrism3(double length, double height)
{
    setName(FFPrism3Type);
    m_length = length;
    m_height = height;
    m_root3 = std::sqrt(3.0);
    check_initialization();
    init_parameters();
}

bool FormFactorPrism3::check_initialization() const
{
    return true;
}

void FormFactorPrism3::init_parameters()
{
    clearParameterPool();
    registerParameter(Length, &m_length, AttLimits::n_positive());
    registerParameter(Height, &m_height, AttLimits::n_positive());
}

FormFactorPrism3* FormFactorPrism3::clone() const
{
    return new FormFactorPrism3(m_length, m_height);
}

void FormFactorPrism3::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorPrism3::getRadius() const
{
    return m_length/2.0;
}

complex_t FormFactorPrism3::evaluate_for_q(const cvector_t& q) const
{
    complex_t qz = q.z();
    double R = m_length/2.0;
    double H = m_height;

    complex_t qzH_half = qz*H/2.0;
    complex_t z_part = H*MathFunctions::sinc(qzH_half)*
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
                MathFunctions::sinc(qxR);
            xy_part *= 2.0*m_root3*expminiqyRdivr3/
                (q.x()*q.x()-3.0*q.y()*q.y());
        }
    }
    return xy_part*z_part;
}


