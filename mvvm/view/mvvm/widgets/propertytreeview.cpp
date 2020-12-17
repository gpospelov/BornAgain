//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/widgets/propertytreeview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "mvvm/widgets/propertytreeview.h"
#include "mvvm/factories/viewmodelfactory.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/viewmodel/viewmodel.h"
#include <QTreeView>

using namespace ModelView;

PropertyTreeView::PropertyTreeView(QWidget* parent) : ItemsTreeView(parent) {
    treeView()->setHeaderHidden(false);
    // provide one click editing
    treeView()->setEditTriggers(QAbstractItemView::AllEditTriggers);
    treeView()->setAlternatingRowColors(true);
}

void PropertyTreeView::setItem(SessionItem* item) {
    if (!item) {
        treeView()->setModel(nullptr);
        return;
    }

    setViewModel(Factory::CreatePropertyViewModel(item->model()));
    viewModel()->setRootSessionItem(item);
    treeView()->setRootIsDecorated(false);
    treeView()->expandAll();
}

PropertyTreeView::~PropertyTreeView() = default;
