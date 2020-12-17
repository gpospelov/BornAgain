//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitembackupstrategy.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H

#include "mvvm/interfaces/itembackupstrategy.h"
#include <memory>

namespace ModelView {

class SessionItem;
class ItemFactoryInterface;

//! Provide backup of SessionItem using json strategy.

class MVVM_MODEL_EXPORT JsonItemBackupStrategy : public ItemBackupStrategy {
public:
    JsonItemBackupStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemBackupStrategy() override;

    std::unique_ptr<SessionItem> restoreItem() const override;

    void saveItem(const SessionItem* item) override;

private:
    struct JsonItemBackupStrategyImpl;
    std::unique_ptr<JsonItemBackupStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMBACKUPSTRATEGY_H
