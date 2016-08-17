// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/IInterferenceFunction.cpp
//! @brief     Implements interface class IInterferenceFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IInterferenceFunction.h"
#include "ISampleVisitor.h"
#include "RealParameter.h"

IInterferenceFunction::~IInterferenceFunction() {}

void IInterferenceFunction::accept(ISampleVisitor *visitor) const { visitor->visit(this); }
