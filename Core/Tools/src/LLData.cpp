// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/LLData.cpp
//! @brief     Implements template specializations for LLData.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "LLData.h"
#include "EigenCore.h"

template <>
Eigen::Matrix2d LLData<Eigen::Matrix2d>::getZeroElement() const
{
    Eigen::Matrix2d result = Eigen::Matrix2d::Zero();
    return result;
}

