//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/topitemstreeview.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_TOPITEMSTREEVIEW_H
#define BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_TOPITEMSTREEVIEW_H

#include "mvvm/widgets/itemstreeview.h"

namespace ModelView {

class SessionModel;

//! Widget holding standard QTreeView and intended for displaying all top level
//! items of SessionModel.

//! All property items (i.e. "thickness", "color" etc) will be filtered out, top level items
//! (i.e. Layer, MultiLayer, ...) will be presented as simple parent/child tree.

class MVVM_VIEW_EXPORT TopItemsTreeView : public ItemsTreeView {
    Q_OBJECT

public:
    TopItemsTreeView(SessionModel* model, QWidget* parent = nullptr);
    ~TopItemsTreeView();
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_WIDGETS_TOPITEMSTREEVIEW_H
