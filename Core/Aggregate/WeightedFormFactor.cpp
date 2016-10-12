// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/WeightedFormFactor.cpp
//! @brief     Implements class WeightedFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "WeightedFormFactor.h"
#include "IFormFactor.h"

WeightedFormFactor::~WeightedFormFactor() { delete mp_ff; }

WeightedFormFactor* WeightedFormFactor::clone() const
{
    return new WeightedFormFactor(mp_ff->clone(), m_abundance);
}
