//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/allitemstreeview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ALLITEMSTREEVIEW_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ALLITEMSTREEVIEW_H

#include "mvvm/widgets/itemstreeview.h"

namespace ModelView {

class SessionModel;

//! Widget holding standard QTreeView and intended for displaying all items of SessionModel.

class MVVM_VIEW_EXPORT AllItemsTreeView : public ItemsTreeView {
    Q_OBJECT

public:
    AllItemsTreeView(SessionModel* model, QWidget* parent = nullptr);
    ~AllItemsTreeView() override;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_ALLITEMSTREEVIEW_H
