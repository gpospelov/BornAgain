// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorTrivial.cpp
//! @brief     Implements class FormFactorTrivial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTrivial.h"

FormFactorTrivial::FormFactorTrivial()
{
    setName("FormFactorTrivial");
    init_parameters();
}

FormFactorTrivial* FormFactorTrivial::clone() const
{
    FormFactorTrivial *result = new FormFactorTrivial();
    result->setName(getName());
    return result;
}

complex_t FormFactorTrivial::evaluate_for_q(const cvector_t& q) const
{
    (void)q;
    return complex_t(1.0, 0.0);
}

void FormFactorTrivial::init_parameters()
{
    clearParameterPool();
}
