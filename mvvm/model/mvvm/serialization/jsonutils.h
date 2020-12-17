//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonutils.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONUTILS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONUTILS_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

class SessionModel;
class RealLimits;

namespace JsonUtils {

//! Returns multiline string representing model content as json.
MVVM_MODEL_EXPORT std::string ModelToJsonString(const SessionModel& model);

//! Returns string representation of RealLimits.
MVVM_MODEL_EXPORT std::string ToString(const RealLimits& limits);

MVVM_MODEL_EXPORT RealLimits CreateLimits(const std::string& text, double min = 0.0,
                                          double max = 0.0);

} // namespace JsonUtils

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONUTILS_H
