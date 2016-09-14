// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactorBorn.cpp
//! @brief     Implements interface class IFormFactorBorn.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFormFactorBorn.h"
#include "Exceptions.h"
#include "ISampleVisitor.h"
#include "WavevectorInfo.h"

complex_t IFormFactorBorn::evaluate(const WavevectorInfo& wavevectors) const
{
    return evaluate_for_q(wavevectors.getQ());
}

complex_t IFormFactorBorn::evaluate_for_q(const cvector_t) const
{
    throw Exceptions::NotImplementedException(
        "Bug: erroneous call of IFormFactorBorn::evaluate_for_q. ");
}

double IFormFactorBorn::getRadialExtension() const
{
    throw Exceptions::NotImplementedException(
        "Bug: erroneous call of IFormFactorBorn::evaluate_for_q. ");
}
