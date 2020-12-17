//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/utils/numericutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_UTILS_NUMERICUTILS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_UTILS_NUMERICUTILS_H

#include "mvvm/model_export.h"

namespace ModelView {

namespace Utils {

//! Returns true if two doubles agree within epsilon*tolerance.
MVVM_MODEL_EXPORT bool AreAlmostEqual(double a, double b, double tolerance_factor = 1.0);

//! Produces random integer values uniformly distributed on the closed interval [low, high].
MVVM_MODEL_EXPORT int RandInt(int low, int high);

//! Produces random FLOAT values uniformly distributed on the  interval [low, high).
MVVM_MODEL_EXPORT double RandDouble(double low, double high);

} // namespace Utils

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_UTILS_NUMERICUTILS_H
