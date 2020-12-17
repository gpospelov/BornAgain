//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/core/uniqueidgenerator.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_CORE_UNIQUEIDGENERATOR_H
#define BORNAGAIN_MVVM_MODEL_MVVM_CORE_UNIQUEIDGENERATOR_H

#include "mvvm/core/types.h"
#include "mvvm/model_export.h"

namespace ModelView {

/*!
@class UniqueIdGenerator
@brief Provides generation of unique SessionItem itentifier.

In the future might be turned to singleton to keep track of all generated identifier
and make sure, that SessionItem identifiers loaded from disk, are different from those
generated during dynamic session. For the moment though, we rely on zero-probability of
such event.
*/

class MVVM_MODEL_EXPORT UniqueIdGenerator {
public:
    static identifier_type generate();
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_CORE_UNIQUEIDGENERATOR_H
