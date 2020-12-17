//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/propertyviewmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_PROPERTYVIEWMODEL_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_PROPERTYVIEWMODEL_H

#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show content of SessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class MVVM_VIEWMODEL_EXPORT PropertyViewModel : public ViewModel {
    Q_OBJECT
public:
    PropertyViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_PROPERTYVIEWMODEL_H
