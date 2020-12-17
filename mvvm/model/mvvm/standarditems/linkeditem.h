//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/linkeditem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_LINKEDITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_LINKEDITEM_H

#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"

namespace ModelView {

//! Item to store a persistent link to other arbitrary items.

//! The identifier of the item intended for linking is stored as DataRole on board of LinkedItem
//! and can be used to find the corresponding item via SessionModel::findItem machinery.
//! Provided mechanism is persistent and outlive serialization. Can be used to find items in
//! different models. For that being the case, models should use same ItemPool.

class MVVM_MODEL_EXPORT LinkedItem : public SessionItem {
public:
    LinkedItem();

    void setLink(const SessionItem* item);

    template <typename T = SessionItem> T* get() const;
};

//! Returns item linked to given item. Works only in model context.

template <typename T> T* LinkedItem::get() const
{
    return model() ? dynamic_cast<T*>(model()->findItem(data<std::string>())) : nullptr;
}

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_LINKEDITEM_H
