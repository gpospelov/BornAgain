// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/IFormFactor.cpp
//! @brief     Implements interface class IFormFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFormFactor.h"
#include "Exceptions.h"
#include "WavevectorInfo.h"

IFormFactor::~IFormFactor() {}

Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo&) const
{
    // Throws to prevent unanticipated behaviour
    throw Exceptions::NotImplementedException(
        "IFormFactor::evaluatePol: is not implemented by default");
}

double IFormFactor::getVolume() const
{
    WavevectorInfo zero_wavevectors;
    return std::abs(evaluate(zero_wavevectors));
}
