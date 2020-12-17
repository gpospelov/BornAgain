//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/sessionitemdata.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_SESSIONITEMDATA_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_SESSIONITEMDATA_H

#include "mvvm/model/datarole.h"
#include "mvvm/model_export.h"
#include <vector>

namespace ModelView {

//! Handles data roles for SessionItem.

class MVVM_MODEL_EXPORT SessionItemData {
public:
    using container_type = std::vector<DataRole>;
    using const_iterator = container_type::const_iterator;

    std::vector<int> roles() const;

    Variant data(int role) const;

    bool setData(const Variant& value, int role);

    const_iterator begin() const;
    const_iterator end() const;

    bool hasData(int role) const;

private:
    void assure_validity(const Variant& variant, int role);
    container_type m_values;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_SESSIONITEMDATA_H
