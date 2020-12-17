//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/datarole.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_DATAROLE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_DATAROLE_H

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"

namespace ModelView {

//! Represents pair of data,role for SessionItemData.

class MVVM_MODEL_EXPORT DataRole {
public:
    DataRole(Variant data = Variant(), int role = -1);
    Variant m_data;
    int m_role;
    bool operator==(const DataRole& other) const;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_DATAROLE_H
