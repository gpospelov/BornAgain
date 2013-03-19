// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorParallelepiped.cpp
//! @brief     Implements class FormFactorParallelepiped.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "FormFactorParallelepiped.h"
#include "MathFunctions.h"

FormFactorParallelepiped::FormFactorParallelepiped(double height, double radius)
: m_height(height)
, m_radius(radius)
{
}

FormFactorParallelepiped::~FormFactorParallelepiped()
{
}

FormFactorParallelepiped* FormFactorParallelepiped::clone() const
{
    FormFactorParallelepiped *p_clone = new FormFactorParallelepiped(m_height, m_radius);
    return p_clone;
}

complex_t FormFactorParallelepiped::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxR = q.x()*m_radius;
    complex_t qyR = q.y()*m_radius;
    complex_t qzHdiv2 = q.z()*m_height/2.0;

    complex_t phase_factor = std::exp(complex_t(0.0, 1.0)*qzHdiv2);
    return getVolume()*phase_factor*MathFunctions::Sinc(qxR)*MathFunctions::Sinc(qyR)
        *MathFunctions::Sinc(qzHdiv2);
}

void FormFactorParallelepiped::init_parameters()
{
    getParameterPool()->clear();
    getParameterPool()->registerParameter("height", &m_height);
    getParameterPool()->registerParameter("radius", &m_radius);
}
