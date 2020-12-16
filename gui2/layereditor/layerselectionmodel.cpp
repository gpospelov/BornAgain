// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QItemSelection>
#include "gui2/layereditor/layerselectionmodel.h"
#include "gui2/model/sampleitems.h"
#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/viewmodel/viewmodelutils.h"

namespace DaRefl {

LayerSelectionModel::LayerSelectionModel(ModelView::ViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent) {
    // FIXME cover with unit tests after implementing ViewItemSelectionModel
    connect(view_model, &ModelView::ViewModel::modelAboutToBeReset, [this]() { clearSelection(); });
}

//! Selects all rows corresponding to given items.

void LayerSelectionModel::selectItems(std::vector<ModelView::SessionItem*> items) {
    QModelIndexList indexes;
    for (auto item : items)
        indexes << viewModel()->indexOfSessionItem(item->getItem(LayerItem::P_NAME));

    if (indexes.empty())
        return;

    clearSelection();

    QItemSelection selection(indexes.front(), indexes.back());
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(selection, flags);
    //    setCurrentIndex(id, flags); What to do?
}

//! Selects whole row corresponding to given item.

void LayerSelectionModel::selectItem(ModelView::SessionItem* item) {
    selectItems({item});
}

//! Returns vector of selected layers or multilayers.
//! We assume, that there is a single line selection mode switched on, and that
//! the columns contains property items related to either LayerItem or MultiLayerItem.

std::vector<ModelView::SessionItem*> LayerSelectionModel::selectedItems() const {
    const QModelIndexList& selection = selectedRows();
    if (selection.empty())
        return {};

    std::vector<ModelView::SessionItem*> result;
    for (const auto& index : selection)
        if (auto item = viewModel()->sessionItemFromIndex(index); item)
            result.push_back(item->parent());

    return result;
}

//! Return the casted view model
const ModelView::ViewModel* LayerSelectionModel::viewModel() const {
    return static_cast<const ModelView::ViewModel*>(model());
}

//! Checks if the first row is presen in the selection
bool LayerSelectionModel::firstSelected() const {
    const QModelIndexList& selection = selectedRows();
    for (const auto& index : selection) {
        if (index.row() == 0)
            return true;
    }
    return false;
}

//! checks if the last row is present in the selection
bool LayerSelectionModel::lastSelected() const {
    const QModelIndexList& selection = selectedRows();
    for (const auto& index : selection) {
        if (index.row() == viewModel()->rowCount() - 1)
            return true;
    }
    return false;
}

} // namespace DaRefl
