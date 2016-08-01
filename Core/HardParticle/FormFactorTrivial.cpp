// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTrivial.cpp
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
}

FormFactorTrivial* FormFactorTrivial::clone() const
{
    return new FormFactorTrivial();
}

void FormFactorTrivial::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

double FormFactorTrivial::getRadialExtension() const
{
    return 1.0;
}

complex_t FormFactorTrivial::evaluate_for_q(const cvector_t) const
{
    return 1.0;
}
