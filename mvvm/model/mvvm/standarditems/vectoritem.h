//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/vectoritem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_VECTORITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_VECTORITEM_H

#include "mvvm/model/compounditem.h"

namespace ModelView {

//! Vector item with three x,y,z property items.

class MVVM_MODEL_EXPORT VectorItem : public CompoundItem {
public:
    static inline const std::string P_X = "P_X";
    static inline const std::string P_Y = "P_Y";
    static inline const std::string P_Z = "P_Z";

    VectorItem();

    void activate() override;

private:
    void update_label();
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_VECTORITEM_H
