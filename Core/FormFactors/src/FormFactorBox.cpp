// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorBox.cpp
//! @brief     Implements class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorBox.h"
#include "MathFunctions.h"


FormFactorBox *FormFactorBox::clone() const
{
    FormFactorBox *result = new FormFactorBox(m_length, m_width, m_height);
    result->setName(getName());
    return result;
}


complex_t FormFactorBox::evaluate_for_q(const cvector_t& q) const
{
    complex_t qxRdiv2 = m_length*q.x()/2.0;
    complex_t qyWdiv2 = m_width*q.y()/2.0;
    complex_t qzHdiv2 = m_height*q.z()/2.0;

    return m_height*m_length*m_width*
        std::exp(complex_t(0.,1.)*qzHdiv2) *
        MathFunctions::Sinc(qxRdiv2) *
        MathFunctions::Sinc(qyWdiv2) *
        MathFunctions::Sinc(qzHdiv2);
}

void FormFactorBox::init_parameters()
{
    clearParameterPool();
    registerParameter("length", &m_length);
    registerParameter( "width", &m_width);
    registerParameter("height", &m_height);
}


