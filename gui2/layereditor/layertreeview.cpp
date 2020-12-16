// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QHeaderView>
#include <QMouseEvent>
#include "gui2/layereditor/layertreeview.h"

namespace DaRefl {

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

} // namespace DaRefl
