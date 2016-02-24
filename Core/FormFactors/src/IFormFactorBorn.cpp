// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/IFormFactorBorn.cpp
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
#include "MathFunctions.h"


complex_t IFormFactorBorn::evaluate(const WavevectorInfo& wavevectors) const
{
    return evaluate_for_q(wavevectors.getQ());
}

Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const WavevectorInfo& wavevectors) const
{
    Eigen::Matrix2cd unit_matrix = Eigen::Matrix2cd::Identity();
    return evaluate(wavevectors) * unit_matrix;
}

bool IFormFactorBorn::check_initialization() const
{
    return true;
}
