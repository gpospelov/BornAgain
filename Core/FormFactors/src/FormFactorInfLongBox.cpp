// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorInfLongBox.cpp
//! @brief     Implements class FormFactorInfLongBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorInfLongBox.h"
#include "MathFunctions.h"


FormFactorInfLongBox *FormFactorInfLongBox::clone() const
{
    FormFactorInfLongBox *result = new FormFactorInfLongBox(m_width, m_height);
    result->setName(getName());
    return result;
}


complex_t FormFactorInfLongBox::evaluate(const WavevectorInfo& wavevectors) const
{
    double qxmin = wavevectors.getQ().x().real();
    double qxmax = wavevectors.getQ().x().real();

    if (qxmin < 0.0 && qxmax < 0.0)
        return 0;

    if (qxmin > 0.0 && qxmax > 0.0)
        return 0;

    cvector_t q = wavevectors.getQ();
    complex_t qyWdiv2 = m_width*q.y()/2.0;
    complex_t qzHdiv2 = m_height*q.z()/2.0;

    return Units::PI2*m_height*m_width*
        std::exp(complex_t(0.,1.)*qzHdiv2) *
        MathFunctions::Sinc(qyWdiv2) *
        MathFunctions::Sinc(qzHdiv2);
}

bool FormFactorInfLongBox::check_initialization() const
{
    return true;
}

void FormFactorInfLongBox::init_parameters()
{
    clearParameterPool();
    registerParameter( "width", & m_width, AttLimits::n_positive());
    registerParameter("height", &m_height, AttLimits::n_positive());
}

complex_t FormFactorInfLongBox::evaluate_for_q(const cvector_t& q) const
{
    (const cvector_t) q;  // to avoid unused-variable warning
    throw NotImplementedException(
        "FormFactorInfLongBox::evaluate_for_q(q) -> Error: not implemented exception.");
}

double FormFactorInfLongBox::getVolume() const {
    // volume of the infinite object is infinite
    throw NotImplementedException(
                "FormFactorInfLongBox::getVolume() -> Error: not implemented exception. Volume of the infinite object is infinite.");
}
