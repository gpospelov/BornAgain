//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/serialization/jsonitemcopystrategy.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H

#include "mvvm/interfaces/itemcopystrategy.h"
#include <memory>

namespace ModelView {

class SessionItem;
class ItemFactoryInterface;

//! Provide SessionItem copying using json based strategy.

class MVVM_MODEL_EXPORT JsonItemCopyStrategy : public ItemCopyStrategy {
public:
    JsonItemCopyStrategy(const ItemFactoryInterface* item_factory);
    ~JsonItemCopyStrategy();

    std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const;

private:
    struct JsonItemCopyStrategyImpl;
    std::unique_ptr<JsonItemCopyStrategyImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SERIALIZATION_JSONITEMCOPYSTRATEGY_H
