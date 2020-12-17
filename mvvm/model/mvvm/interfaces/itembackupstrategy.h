//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/interfaces/itembackupstrategy.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_ITEMBACKUPSTRATEGY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_ITEMBACKUPSTRATEGY_H

#include "mvvm/model_export.h"
#include <memory>

namespace ModelView {

class SessionItem;

//! Interface to backup items for later restore.

class MVVM_MODEL_EXPORT ItemBackupStrategy {
public:
    virtual ~ItemBackupStrategy() = default;

    //! Restore item from saved content.
    virtual std::unique_ptr<SessionItem> restoreItem() const = 0;

    //! Save item's content.
    virtual void saveItem(const SessionItem*) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_ITEMBACKUPSTRATEGY_H
