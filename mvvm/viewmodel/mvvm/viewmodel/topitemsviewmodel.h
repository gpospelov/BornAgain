//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/viewmodel/topitemsviewmodel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H

#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {

//! View model to show top level items of SessionModel in Qt trees and tables.
//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class MVVM_VIEWMODEL_EXPORT TopItemsViewModel : public ViewModel {
    Q_OBJECT
public:
    TopItemsViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_VIEWMODEL_TOPITEMSVIEWMODEL_H
