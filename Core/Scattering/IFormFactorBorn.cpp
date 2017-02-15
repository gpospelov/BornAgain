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
#include "Dot.h"
#include "Exceptions.h"
#include "Rotations.h"
#include "WavevectorInfo.h"

IFormFactorBorn::IFormFactorBorn()
    : mP_shape(new Dot())
{}

complex_t IFormFactorBorn::evaluate(const WavevectorInfo& wavevectors) const
{
    return evaluate_for_q(wavevectors.getQ());
}

Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const WavevectorInfo &wavevectors) const
{
    return evaluate_for_q_pol(wavevectors.getQ());
}

double IFormFactorBorn::bottomZ(const IRotation& rotation) const
{
    return BottomZ(mP_shape->vertices(), rotation.getTransform3D());
}

Eigen::Matrix2cd IFormFactorBorn::evaluate_for_q_pol(const cvector_t q) const
{
    return evaluate_for_q(q) * Eigen::Matrix2cd::Identity();
}
