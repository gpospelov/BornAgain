// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorBox.cpp
//! @brief     Implements class FormFactorBox.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorBox.h"
#include "MathFunctions.h"

complex_t FormFactorBox::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxR = m_radius*q.x();
    complex_t qyW = m_width*q.y();
    complex_t qzHdiv2 = m_height/2*q.z();

    return getVolume() *
        std::exp(complex_t(0.,1.)*qzHdiv2) *
        MathFunctions::Sinc(qxR) *
        MathFunctions::Sinc(qyW) *
        MathFunctions::Sinc(qzHdiv2);
}

void FormFactorBox::init_parameters()
{
    clearParameterPool();
    registerParameter("radius", &m_radius);
    registerParameter( "width", & m_width);
    registerParameter("height", &m_height);
}


