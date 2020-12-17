//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/interfaces/modeldocumentinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

//! Pure virtual interface to save and restore session models to/from disk.

class MVVM_MODEL_EXPORT ModelDocumentInterface {
public:
    virtual ~ModelDocumentInterface() = default;

    virtual void save(const std::string& file_name) const = 0;
    virtual void load(const std::string& file_name) = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H
