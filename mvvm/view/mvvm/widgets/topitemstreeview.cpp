//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/topitemstreeview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/widgets/topitemstreeview.h"
#include "mvvm/factories/viewmodelfactory.h"
#include "mvvm/viewmodel/viewmodel.h"

namespace ModelView {
TopItemsTreeView::TopItemsTreeView(SessionModel* model, QWidget* parent) : ItemsTreeView(parent)
{
    setViewModel(Factory::CreateTopItemsViewModel(model));
}

TopItemsTreeView::~TopItemsTreeView() = default;

} // namespace ModelView
