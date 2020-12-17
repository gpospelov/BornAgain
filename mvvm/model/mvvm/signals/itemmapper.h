//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/signals/itemmapper.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_ITEMMAPPER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_ITEMMAPPER_H

#include "mvvm/interfaces/itemlistenerinterface.h"
#include "mvvm/signals/modellistener.h"
#include <memory>

namespace ModelView {

class SessionItem;

//! Provides notifications on various changes for a specific item.
//! ItemMapper listens signals coming from the model (i.e. via ModelMapper) and processes only whose
//! signals which are related to the given item. Notifies all interested subscribers about things
//! going with the item and its relatives.

class MVVM_MODEL_EXPORT ItemMapper : public ItemListenerInterface,
                                     private ModelListener<SessionModel> {
public:
    ItemMapper(SessionItem* item);
    ~ItemMapper();

    void setOnItemDestroy(Callbacks::item_t f, Callbacks::slot_t owner) override;
    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t owner) override;
    void setOnPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner) override;
    void setOnChildPropertyChange(Callbacks::item_str_t f, Callbacks::slot_t owner) override;
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) override;
    void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) override;
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t owner) override;

    void unsubscribe(Callbacks::slot_t client) override;

    void setActive(bool value);

private:
    friend class SessionItem;
    void callOnItemDestroy();

    struct ItemMapperImpl;
    std::unique_ptr<ItemMapperImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_ITEMMAPPER_H
