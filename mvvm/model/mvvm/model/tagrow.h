//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/model/tagrow.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_MODEL_TAGROW_H
#define BORNAGAIN_MVVM_MODEL_MVVM_MODEL_TAGROW_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

//! Aggregate to hold (tag, row) information for SessionModel.

class MVVM_MODEL_EXPORT TagRow {
public:
    std::string tag = {};
    int row = -1;

    TagRow() {}

    TagRow(const std::string& name, int row = -1) : tag(name), row(row) {}
    TagRow(const char* name, int row = -1) : tag(name), row(row) {}

    TagRow next() const;

    TagRow prev() const;

    static TagRow append(const std::string& tag_name = {});

    static TagRow prepend(const std::string& tag_name = {});

    bool operator==(const TagRow& other) const;
    bool operator!=(const TagRow& other) const;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_MODEL_TAGROW_H
