//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/interfaces/itemcopystrategy.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_ITEMCOPYSTRATEGY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_ITEMCOPYSTRATEGY_H

#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionItem;

//! Interface for deep item copying.

class MVVM_MODEL_EXPORT ItemCopyStrategy {
public:
    virtual ~ItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. SessionItem identifiers will be regenerated.
    virtual std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_ITEMCOPYSTRATEGY_H
