//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/interfaces/projectinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_PROJECTINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_PROJECTINTERFACE_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

//! Interface to manipulate projects on disk.
//! Project represents content of all application models in a folder on disk.

class MVVM_MODEL_EXPORT ProjectInterface {
public:
    virtual ~ProjectInterface() = default;
    virtual std::string projectDir() const = 0;
    virtual bool save(const std::string& dirname) const = 0;
    virtual bool load(const std::string& dirname) = 0;
    virtual bool isModified() const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_PROJECTINTERFACE_H
