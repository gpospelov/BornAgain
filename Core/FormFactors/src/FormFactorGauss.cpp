// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorGauss.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorGauss::FormFactorGauss(double volume)
{
    setName("FormFactorGauss");
    m_height = std::pow(volume, 1.0/3.0);
    m_width = m_height;
    check_initialization();
    init_parameters();
    m_max_ql = std::sqrt(-4.0*M_PI*std::log(Numeric::double_epsilon)
               / 3.0);
}

FormFactorGauss::FormFactorGauss(double width, double height)
{
    setName("FormFactorGauss");
    m_width = width;
    m_height = height;
    check_initialization();
    init_parameters();
    m_max_ql = std::sqrt(-4.0*M_PI*std::log(Numeric::double_epsilon)
               / 3.0);
}

bool FormFactorGauss::check_initialization() const
{
    return true;
}

void FormFactorGauss::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_width, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
}

FormFactorGauss* FormFactorGauss::clone() const
{
    FormFactorGauss *result = new FormFactorGauss(m_width, m_height);
    result->setName(getName());
    return result;
}

complex_t FormFactorGauss::evaluate_for_q(const cvector_t& q) const
{
    complex_t qzHdiv2 = m_height*q.z()/2.0;
    double qzh = q.z().real()*m_height;
    if (std::abs(qzh)>m_max_ql) return 0.0;
    double qxr = q.x().real()*m_width;
    if (std::abs(qxr)>m_max_ql) return 0.0;
    double qyr = q.y().real()*m_width;
    if (std::abs(qyr)>m_max_ql) return 0.0;


    complex_t z_part = std::exp(complex_t(0.,1.)*qzHdiv2) * m_height
            * std::exp(-qzh*qzh/4.0/M_PI);
    double radial_part = m_width * m_width
            * std::exp(-(qxr*qxr+qyr*qyr)/4.0/M_PI);
    complex_t result = radial_part * z_part;
    return result;
}

