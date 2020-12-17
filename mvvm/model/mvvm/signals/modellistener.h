//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/signals/modellistener.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_MODELLISTENER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_MODELLISTENER_H

#include "mvvm/signals/modellistenerbase.h"

namespace ModelView {

class SessionItem;

//! Templated class for all objects willing to listen for changes in concrete SessionModel.

template <typename T> class ModelListener : public ModelListenerBase {
public:
    ModelListener(T* session_model) : ModelListenerBase(session_model) {}

    T* model() const { return static_cast<T*>(m_model); }
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_SIGNALS_MODELLISTENER_H
