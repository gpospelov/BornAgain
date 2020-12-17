//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/utils/binutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_UTILS_BINUTILS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_UTILS_BINUTILS_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView ::Utils {

//! Returns true if file is binary
MVVM_MODEL_EXPORT bool is_binary(const std::string& filename);

//! Returns true if file is text/ascii
MVVM_MODEL_EXPORT bool is_text(const std::string& filename);

} // namespace ModelView::Utils

#endif // BORNAGAIN_MVVM_MODEL_MVVM_UTILS_BINUTILS_H
