// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorLorentz.cpp
//! @brief     Implements class FormFactorLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLorentz.h"

#include "MathFunctions.h"
#include "Numeric.h"

FormFactorLorentz::FormFactorLorentz(double volume)
{
    setName("FormFactorLorentz");
    double R = std::pow(volume, 1.0/3.0);
    m_height = R;
    m_width = R;
    check_initialization();
    init_parameters();
}

FormFactorLorentz::FormFactorLorentz(double width, double height)
{
    setName("FormFactorLorentz");
    m_width = width;
    m_height = height;
    check_initialization();
    init_parameters();
}

bool FormFactorLorentz::check_initialization() const
{
    return true;
}

void FormFactorLorentz::init_parameters()
{
    clearParameterPool();
    registerParameter("width", &m_width, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
}

FormFactorLorentz* FormFactorLorentz::clone() const
{
    FormFactorLorentz *result = new FormFactorLorentz(m_width, m_height);
    result->setName(getName());
    return result;
}

complex_t FormFactorLorentz::evaluate_for_q(const cvector_t& q) const
{
    static const double sigma2 = 4.0*std::pow(M_PI, 2.0/3.0);
    double R = m_width;
    double H = m_height;

    complex_t xnorm = R*R*q.x()*q.x()/sigma2;
    complex_t ynorm = R*R*q.y()*q.y()/sigma2;
    complex_t znorm = H*H*q.z()*q.z()/sigma2;

    complex_t result = H*R*R/(1.0 + xnorm + ynorm + znorm);

    return result;
}


