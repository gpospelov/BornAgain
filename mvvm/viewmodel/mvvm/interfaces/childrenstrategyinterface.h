//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/interfaces/childrenstrategyinterface.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <vector>

namespace ModelView {

class SessionItem;

//! Base class for strategies to find children, actual of fictional, of given item.

//! Reported vector of children might be different from actual children of given item.
//! The strategy is used in context of AbstractViewModel while exposing SessionModel to Qt.
//! Thanks to this strategy ViewModel decides which items to visit.

class MVVM_VIEWMODEL_EXPORT ChildrenStrategyInterface {
public:
    virtual ~ChildrenStrategyInterface() = default;

    //! Returns vector of children of given item.
    virtual std::vector<SessionItem*> children(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H
