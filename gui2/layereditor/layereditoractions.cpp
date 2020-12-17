//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/layereditor/layereditoractions.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/layereditor/layereditoractions.h"
#include "gui2/layereditor/layerselectionmodel.h"
#include "gui2/model/item_constants.h"
#include "gui2/model/sampleitems.h"
#include "gui2/model/samplemodel.h"
#include "mvvm/model/itemutils.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/viewmodel/viewmodel.h"
#include <QAction>

using namespace ModelView;

namespace gui2 {

struct LayerEditorActions::LayerEditorActionsImpl {
    SampleModel* sample_model{nullptr};
    LayerSelectionModel* selection_model{nullptr};
    LayerEditorActionsImpl() {}

    //! Finds parent and tagrow to insert new item

    std::pair<SessionItem*, TagRow> locateInsertPlace() {
        auto all_selected = selection_model->selectedItems();
        auto selected = all_selected.empty() ? nullptr : all_selected.back();
        if (selected)
            return {selected->parent(), selected->tagRow().next()};
        return {root_item(), TagRow{}};
    }

    //! Returns a multi layer playing the role of invisible root item.

    ModelView::SessionItem* root_item() {
        return selection_model->viewModel()->sessionItemFromIndex(QModelIndex());
    }
};

LayerEditorActions::LayerEditorActions(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<LayerEditorActionsImpl>()) {}

void LayerEditorActions::setModel(SampleModel* model) {
    p_impl->sample_model = model;
}

//! Adds layer after selected item. If more than one item is selected, adds after the last one.

void LayerEditorActions::onAddLayer() {
    if (!p_impl->sample_model)
        return;

    auto [parent, tagrow] = p_impl->locateInsertPlace();
    auto new_item = p_impl->sample_model->insertItem<LayerItem>(parent, tagrow);
    p_impl->selection_model->selectItem(new_item);
}

void LayerEditorActions::onAddMultiLayer() {
    if (!p_impl->sample_model)
        return;

    auto [parent, tagrow] = p_impl->locateInsertPlace();
    auto multilayer = p_impl->sample_model->insertItem<MultiLayerItem>(parent, tagrow);
    p_impl->sample_model->insertItem<LayerItem>(multilayer);
    p_impl->sample_model->insertItem<LayerItem>(multilayer);
    p_impl->selection_model->selectItem(multilayer);
}

void LayerEditorActions::onClone() {
    if (!p_impl->sample_model)
        return;

    auto items = p_impl->selection_model->selectedItems();
    if (items.empty())
        return;

    std::vector<ModelView::SessionItem*> new_selection;
    for (auto to_clone : items)
        new_selection.push_back(p_impl->sample_model->copyItem(to_clone, to_clone->parent(),
                                                               to_clone->tagRow().next()));

    p_impl->selection_model->selectItems(new_selection);
}

void LayerEditorActions::onRemove() {
    auto items = p_impl->selection_model->selectedItems();
    if (items.empty())
        return;

    auto prev_to_select = ModelView::Utils::FindPreviousSibling(items.front());
    auto next_to_select = ModelView::Utils::FindNextSibling(items.back());

    for (auto item : items)
        ModelView::Utils::DeleteItemFromModel(item);
    if (next_to_select) {
        p_impl->selection_model->selectItem(next_to_select);
    } else if (prev_to_select) {
        p_impl->selection_model->selectItem(prev_to_select);
    }
}

void LayerEditorActions::onMoveUp() {
    auto selected = p_impl->selection_model->selectedItems();

    for (auto item : selected)
        ModelView::Utils::MoveUp(item);

    p_impl->selection_model->selectItems(selected);
}

void LayerEditorActions::onMoveDown() {
    auto selected = p_impl->selection_model->selectedItems();

    for (auto item : selected)
        ModelView::Utils::MoveDown(item);

    p_impl->selection_model->selectItems(selected);
}

void LayerEditorActions::setSelectionModel(LayerSelectionModel* selection_model) {
    p_impl->selection_model = selection_model;
}

LayerEditorActions::~LayerEditorActions() = default;

} // namespace gui2
