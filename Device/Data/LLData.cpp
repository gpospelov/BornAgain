//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Device/Data/LLData.cpp
//! @brief     Implements template specializations for LLData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Data/LLData.h"

template <> Eigen::Matrix2d LLData<Eigen::Matrix2d>::getZeroElement() const {
    Eigen::Matrix2d result = Eigen::Matrix2d::Zero();
    return result;
}
