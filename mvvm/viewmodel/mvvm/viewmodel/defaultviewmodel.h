//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/defaultviewmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H

#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show content of SessionModel in Qt widgets: two column tree with label/data.

//! Provides two column tree with label/data, with one-to-one child/parent
//! correspondence as in the original SessionModel.

class MVVM_VIEWMODEL_EXPORT DefaultViewModel : public ViewModel {
    Q_OBJECT
public:
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
