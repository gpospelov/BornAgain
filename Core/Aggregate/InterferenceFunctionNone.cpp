// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionNone.cpp
//! @brief     Implements class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InterferenceFunctionNone.h"
#include "BornAgainNamespace.h"

InterferenceFunctionNone::InterferenceFunctionNone()
{
    setName(BornAgain::InterferenceFunctionNoneType);
}

InterferenceFunctionNone* InterferenceFunctionNone::clone() const
{
    return new InterferenceFunctionNone(*this);
}

InterferenceFunctionNone::InterferenceFunctionNone(const InterferenceFunctionNone& other)
    : IInterferenceFunction(other)
{
    setName(other.getName());
}
