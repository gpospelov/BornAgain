//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/itempool.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_ITEMPOOL_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_ITEMPOOL_H

#include "mvvm/model/mvvm_types.h"
#include "mvvm/model_export.h"
#include <map>

namespace ModelView {

class SessionItem;

//! Provides registration of SessionItem pointers and their unique identifiers
//! in global memory pool.

class MVVM_MODEL_EXPORT ItemPool {
public:
    ItemPool() = default;
    ItemPool(const ItemPool&) = delete;
    ItemPool(ItemPool&&) = delete;
    ItemPool& operator=(const ItemPool&) = delete;
    ItemPool& operator=(ItemPool&&) = delete;

    size_t size() const;

    identifier_type register_item(SessionItem* item, identifier_type key = {});
    void unregister_item(SessionItem* item);

    identifier_type key_for_item(const SessionItem* item) const;

    SessionItem* item_for_key(const identifier_type& key) const;

private:
    std::map<identifier_type, SessionItem*> m_key_to_item;
    std::map<const SessionItem*, identifier_type> m_item_to_key;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_ITEMPOOL_H
