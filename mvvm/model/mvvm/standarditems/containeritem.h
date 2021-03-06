//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/containeritem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_CONTAINERITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_CONTAINERITEM_H

#include "mvvm/model/compounditem.h"

namespace ModelView {

//! Simple container to store any type of children.
//! Used as convenience item to create branch with uniform children beneath.

class MVVM_MODEL_EXPORT ContainerItem : public CompoundItem {
public:
    static inline const std::string T_ITEMS = "T_ITEMS";

    ContainerItem(const std::string& modelType = Constants::ContainerItemType);

    bool empty() const;

    size_t size() const;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_CONTAINERITEM_H
