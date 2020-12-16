// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/materialeditor/materialselectionmodel.h"
#include "gui2/model/materialitems.h"
#include "mvvm/viewmodel/viewmodel.h"
#include "mvvm/viewmodel/viewmodelutils.h"

namespace gui2 {

MaterialSelectionModel::MaterialSelectionModel(ModelView::ViewModel* view_model, QObject* parent)
    : QItemSelectionModel(view_model, parent) {
    // FIXME cover with unit tests after implementing ViewItemSelectionModel
    connect(view_model, &ModelView::ViewModel::modelAboutToBeReset, [this]() { clearSelection(); });
}

void MaterialSelectionModel::selectItem(ModelView::SessionItem* item) {
    selectItems({item});
}

void MaterialSelectionModel::selectItems(std::vector<ModelView::SessionItem*> items) {
    QModelIndexList indexes;
    for (auto item : items)
        indexes << viewModel()->indexOfSessionItem(item->getItem(MaterialBaseItem::P_NAME));

    if (indexes.empty())
        return;

    clearSelection();

    QItemSelection selection(indexes.front(), indexes.back());
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    select(selection, flags);
}

//! Returns vector of selected materials.

std::vector<MaterialBaseItem*> MaterialSelectionModel::selectedMaterials() const {
    std::vector<MaterialBaseItem*> result;
    auto selected_items = ModelView::Utils::ParentItemsFromIndex(selectedIndexes());
    std::transform(std::begin(selected_items), std::end(selected_items), std::back_inserter(result),
                   [](auto item) { return dynamic_cast<MaterialBaseItem*>(item); });
    return result;
}

const ModelView::ViewModel* MaterialSelectionModel::viewModel() const {
    return static_cast<const ModelView::ViewModel*>(model());
}

} // namespace gui2
