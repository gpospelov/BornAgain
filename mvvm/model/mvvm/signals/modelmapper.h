//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/signals/modelmapper.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_MODELMAPPER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_MODELMAPPER_H

#include "mvvm/interfaces/modellistenerinterface.h"
#include <memory>

namespace ModelView {

class SessionItem;
class SessionModel;

//! Provides notifications on various SessionModel changes.
//! Allows to subscribe to SessionModel's changes, and triggers notifications.

class MVVM_MODEL_EXPORT ModelMapper : public ModelListenerInterface {
public:
    ModelMapper(SessionModel* model);
    ~ModelMapper();

    ModelMapper(const ModelMapper& other) = delete;
    ModelMapper& operator=(const ModelMapper& other) = delete;

    void setOnDataChange(Callbacks::item_int_t f, Callbacks::slot_t client) override;
    void setOnItemInserted(Callbacks::item_tagrow_t f, Callbacks::slot_t client) override;
    void setOnItemRemoved(Callbacks::item_tagrow_t f, Callbacks::slot_t client) override;
    void setOnAboutToRemoveItem(Callbacks::item_tagrow_t f, Callbacks::slot_t client) override;
    void setOnModelDestroyed(Callbacks::model_t f, Callbacks::slot_t client) override;
    void setOnModelAboutToBeReset(Callbacks::model_t f, Callbacks::slot_t client) override;
    void setOnModelReset(Callbacks::model_t f, Callbacks::slot_t client) override;

    void setActive(bool value);

    void unsubscribe(Callbacks::slot_t client) override;

private:
    friend class SessionModel;
    friend class SessionItem;

    void callOnDataChange(SessionItem* item, int role);
    void callOnItemInserted(SessionItem* parent, const TagRow& tagrow);
    void callOnItemRemoved(SessionItem* parent, const TagRow& tagrow);
    void callOnItemAboutToBeRemoved(SessionItem* parent, const TagRow& tagrow);
    void callOnModelDestroyed();
    void callOnModelAboutToBeReset();
    void callOnModelReset();

    struct ModelMapperImpl;
    std::unique_ptr<ModelMapperImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_MODELMAPPER_H
