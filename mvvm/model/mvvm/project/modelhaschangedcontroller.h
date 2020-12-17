//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/project/modelhaschangedcontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_MODELHASCHANGEDCONTROLLER_H
#define BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_MODELHASCHANGEDCONTROLLER_H

#include "mvvm/signals/modellistener.h"
#include <functional>

namespace ModelView {

//! Tracks changes in the model.
//! Allows to check if model has been changed (e.g. modified, inserted or removed items) since last
//! call of ::resetChanged().

class MVVM_MODEL_EXPORT ModelHasChangedController : public ModelListener<SessionModel> {
public:
    using callback_t = std::function<void()>;
    ModelHasChangedController(SessionModel* model, callback_t callback = {});

    bool hasChanged() const;

    void resetChanged();

private:
    void process_change();
    bool m_has_changed{false};
    callback_t m_callback; //! informs the user about change in the model
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_PROJECT_MODELHASCHANGEDCONTROLLER_H
