// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Assembly/InterferenceFunctionNone.cpp
//! @brief     Implements class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunctionNone.h"
#include "BornAgainNamespace.h"


InterferenceFunctionNone::InterferenceFunctionNone()
{
    setName(BornAgain::InterferenceFunctionNoneType);
}

InterferenceFunctionNone *InterferenceFunctionNone::clone() const
{
    return new InterferenceFunctionNone();
}

void InterferenceFunctionNone::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

double InterferenceFunctionNone::evaluate(const kvector_t ) const
{
    return 1.0;
}
