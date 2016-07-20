// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/IMaterial.cpp
//! @brief     Implements class IMaterial.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMaterial.h"

Eigen::Matrix2cd IMaterial::getScatteringMatrix(double k_mag2) const
{
    (void)k_mag2;
    return Eigen::Matrix2cd::Identity();
}

