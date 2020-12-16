// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/importdataview/dataselectionmodel.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/item_constants.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/mvvm_types.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/standarditems/graphitem.h"
#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/viewmodel/viewmodelutils.h"

namespace DaRefl {

//! The constructor
DataSelectionModel::DataSelectionModel(ModelView::ViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent) {
    // FIXME cover with unit tests after implementing ViewItemSelectionModel
    connect(view_model, &ModelView::ViewModel::modelAboutToBeReset, [this]() { clearSelection(); });
}

//! Set the selection on a single item
void DataSelectionModel::selectItem(ModelView::SessionItem* item) {
    selectItems({item});
}

//! Set the selection on a list of items
void DataSelectionModel::selectItems(std::vector<ModelView::SessionItem*> items) {
    QModelIndexList indexes;
    for (auto item : items)
        indexes << viewModel()->indexOfSessionItem(item);

    if (indexes.empty())
        return;

    clearSelection();

    QItemSelection selection(indexes.front(), indexes.back());
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(selection, flags);
}

//! Return the selected items
std::vector<ModelView::SessionItem*> DataSelectionModel::selectedItems() const {
    auto items = ModelView::Utils::ItemsFromIndex(selectedIndexes());
    return ModelView::Utils::UniqueItems(items);
}

const ModelView::ViewModel* DataSelectionModel::viewModel() const {
    return static_cast<const ModelView::ViewModel*>(model());
}

//! Returns active canvas. The canvas is active when it is either selected, or one of its own
//! graph is selected. If more than one canvas is selected, will return the first one.

CanvasItem* DataSelectionModel::activeCanvas() const {
    for (auto item : selectedItems()) {
        if (item->modelType() == Constants::CanvasItemType)
            return static_cast<CanvasItem*>(item);
        else if (item->modelType() == ModelView::Constants::GraphItemType)
            return static_cast<CanvasItem*>(item->parent());
    }
    return nullptr;
}

//! Returns currently selected graph. If more than one graph is selected, will return first one.

ModelView::GraphItem* DataSelectionModel::selectedGraph() const {
    auto graphs = selectedGraphs();
    return graphs.empty() ? nullptr : graphs.at(0);
}

//! Returns vector of currently slected canvas.

std::vector<CanvasItem*> DataSelectionModel::selectedCanvas() const {
    return ModelView::Utils::CastedItems<CanvasItem>(selectedItems());
}

std::vector<ModelView::GraphItem*> DataSelectionModel::selectedGraphs() const {
    return ModelView::Utils::CastedItems<ModelView::GraphItem>(selectedItems());
}

} // namespace DaRefl
