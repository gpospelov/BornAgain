//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/interfaces/applicationmodelsinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_APPLICATIONMODELSINTERFACE_H
#define BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_APPLICATIONMODELSINTERFACE_H

#include "mvvm/model_export.h"
#include <vector>

namespace ModelView {

class SessionModel;

//! Interface to access application's model list for further manipulation.
//! Used in the context of save/load projects.

class MVVM_MODEL_EXPORT ApplicationModelsInterface {
public:
    //! Returns vector of models intended for saving on disk.
    virtual std::vector<SessionModel*> persistent_models() const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_INTERFACES_APPLICATIONMODELSINTERFACE_H
