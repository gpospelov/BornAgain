// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorGauss.cpp
//! @brief     Implements class FormFactorGauss.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
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
}

FormFactorGauss::FormFactorGauss(double height, double width)
{
    setName("FormFactorGauss");
    m_height = height;
    m_width = width;
    init_parameters();
}

FormFactorGauss::~FormFactorGauss()
{
}

//! initialize pool parameters, i.e. register some of class members for later access via parameter pool

void FormFactorGauss::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("width", &m_width);
}


FormFactorGauss* FormFactorGauss::clone() const
{
    FormFactorGauss *p_clone = new FormFactorGauss(m_height, m_width);
    return p_clone;
}

complex_t FormFactorGauss::evaluate_for_q(const cvector_t &q) const
{
    double R = m_width;
    double H = m_height;

    complex_t z_part = H*std::exp(-q.z()*q.z()*H*H/8.0/M_PI);
    complex_t radial_part = R*R*
        std::exp(-(q.x()*q.x()+q.y()*q.y())*R*R/8.0/M_PI);
    return radial_part*z_part;
}
