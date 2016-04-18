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
#include "BornAgainNamespace.h"


FormFactorTrivial::FormFactorTrivial()
{
    setName(BornAgain::FormFactorTrivialType);
    check_initialization();
    init_parameters();
}

FormFactorTrivial* FormFactorTrivial::clone() const
{
    return new FormFactorTrivial();
}

void FormFactorTrivial::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double FormFactorTrivial::getRadius() const
{
    return 1.0;
}

complex_t FormFactorTrivial::evaluate_for_q(const cvector_t q) const
{
    (void)q;
    return complex_t(1.0, 0.0);
}

bool FormFactorTrivial::check_initialization() const
{
    return true;
}

void FormFactorTrivial::init_parameters()
{
    clearParameterPool();
}
