//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/layereditor/layertreeview.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/layereditor/layertreeview.h"
#include <QHeaderView>
#include <QMouseEvent>

namespace gui2 {

LayerTreeView::~LayerTreeView() = default;

LayerTreeView::LayerTreeView(QWidget* parent) : QTreeView(parent) {
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    //    setTabKeyNavigation(true);
    header()->setSectionResizeMode(QHeaderView::Stretch);
}

void LayerTreeView::setModel(QAbstractItemModel* model) {
    QTreeView::setModel(model);
    expandAll();
}

} // namespace gui2
