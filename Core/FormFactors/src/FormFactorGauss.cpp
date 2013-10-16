// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGauss.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorGauss.h"
#include "StochasticDiracDelta.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorGauss::FormFactorGauss(double volume)
{
    setName("FormFactorGauss");
    double R = std::pow(volume, 1.0/3.0);
    m_height = R;
    m_width = R;
    init_parameters();
    m_max_ql = std::sqrt(-4.0*M_PI*std::log(Numeric::double_epsilon)
               / 3.0);
}

FormFactorGauss::FormFactorGauss(double height, double width)
{
    setName("FormFactorGauss");
    m_height = height;
    m_width = width;
    init_parameters();
    m_max_ql = std::sqrt(-4.0*M_PI*std::log(Numeric::double_epsilon)
               / 3.0);
}

//! Registers some class members for later access via parameter pool

void FormFactorGauss::init_parameters()
{
    clearParameterPool();
    registerParameter("height", &m_height);
    registerParameter("width", &m_width);
}

FormFactorGauss* FormFactorGauss::clone() const
{
    FormFactorGauss *result = new FormFactorGauss(m_height, m_width);
    result->setName(getName());
    return result;
}

complex_t FormFactorGauss::evaluate_for_q(const cvector_t& q) const
{
    complex_t qzHdiv2 = m_height*q.z()/2.0;
    complex_t qzh = q.z()*m_height;
    if (std::abs(qzh.real())>m_max_ql) return 0.0;
    complex_t qxr = q.x()*m_width;
    if (std::abs(qxr.real())>m_max_ql) return 0.0;
    complex_t qyr = q.y()*m_width;
    if (std::abs(qyr.real())>m_max_ql) return 0.0;


    complex_t z_part = std::exp(complex_t(0.,1.)*qzHdiv2) * m_height
            * std::exp(-qzh*qzh/4.0/M_PI);
    complex_t radial_part = m_width * m_width
            * std::exp(-(qxr*qxr+qyr*qyr)/4.0/M_PI);
    return radial_part * z_part;
}

bool FormFactorGauss::useLargeBinApproximation(const Bin1DCVector& q_bin) const
{
    (void)q_bin;
    return false;
}
