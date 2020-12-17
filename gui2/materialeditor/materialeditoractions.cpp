//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/materialeditor/materialeditoractions.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/materialeditor/materialeditoractions.h"
#include "gui2/materialeditor/materialselectionmodel.h"
#include "gui2/model/materialitems.h"
#include "gui2/model/materialmodel.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/model/sessionitemdata.h"
#include "mvvm/viewmodel/viewmodel.h"
#include <QFile>
#include <QTextStream>

using namespace ModelView;

namespace gui2 {

struct MaterialEditorActions::MaterialEditorActionsImpl {
    MaterialModel* material_model{nullptr};
    MaterialSelectionModel* selection_model{nullptr};
    MaterialEditorActionsImpl() {}

    //! Finds parent and tagrow to insert new item

    std::pair<SessionItem*, TagRow> locateInsertPlace() {
        auto all_selected = selection_model->selectedMaterials();
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

MaterialEditorActions::MaterialEditorActions(QObject* parent)
    : QObject(parent), p_impl(std::make_unique<MaterialEditorActionsImpl>()) {}

void MaterialEditorActions::setModel(MaterialModel* model) {
    p_impl->material_model = model;
}

void MaterialEditorActions::setMaterialSelectionModel(MaterialSelectionModel* selection_model) {
    p_impl->selection_model = selection_model;
}

void MaterialEditorActions::onAddMaterial() {
    if (!p_impl->material_model)
        return;

    auto [parent, tagrow] = p_impl->locateInsertPlace();
    auto material = p_impl->material_model->addDefaultMaterial(tagrow);
    p_impl->selection_model->selectItem(material);
}

//! Processes request to clone selected materials.

void MaterialEditorActions::onCloneMaterial() {
    if (!p_impl->material_model)
        return;

    std::vector<ModelView::SessionItem*> new_selection;
    for (const auto item : p_impl->selection_model->selectedMaterials())
        new_selection.push_back(p_impl->material_model->cloneMaterial(item));
    p_impl->selection_model->selectItems(new_selection);
}

void MaterialEditorActions::onRemoveMaterial() {
    if (!p_impl->selection_model)
        return;

    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::DeleteItemFromModel(item);
}

void MaterialEditorActions::onMoveUp() {
    if (!p_impl->selection_model)
        return;

    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::MoveUp(item);
}

void MaterialEditorActions::onMoveDown() {
    if (!p_impl->selection_model)
        return;

    auto items = p_impl->selection_model->selectedMaterials();
    std::reverse(items.begin(), items.end()); // to correctly move multiple selections
    for (auto item : p_impl->selection_model->selectedMaterials())
        ModelView::Utils::MoveDown(item);
}

void MaterialEditorActions::onExport() {
    auto item = p_impl->root_item();
    const auto containers = item->children();

    bool title = true; // print title only once in ascii file
    QString tableData;
    QString titleData;

    for (auto container : containers) {
        auto data = container->modelType();
        for (auto fields : dynamic_cast<MaterialBaseItem*>(container)->children()) {
            if (title) {
                titleData += (fields->displayName()).c_str();
                titleData += " ";
            }
            auto val = fields->data<QVariant>(1); // role 1 has the values.
            if (strcmp(val.typeName(), "std::string") == 0) {
                tableData += val.value<std::string>().c_str();
                tableData += " ";
            } else if (strcmp(val.typeName(), "int") == 0) {
                auto int_val = val.value<int>();
                tableData += QString::number(int_val);
                tableData += " ";
            } else if (strcmp(val.typeName(), "double") == 0) {
                auto double_val = val.value<double>();
                tableData += QString::number(double_val);
                tableData += " ";
            } else if (strcmp(val.typeName(), "float") == 0) {
                auto float_val = val.value<float>();
                tableData += QString::number(float_val);
                tableData += " ";
            } else {
                auto color_str = val.toString();
                tableData += color_str;
                tableData += " ";
            }
        }
        if (title) {
            titleData += "\n";
            tableData = titleData + tableData;
        }
        title = false;
        tableData += "\n";
    }
    /*for text file*/
    QFile txtFile("materialdata");
    if (txtFile.open(QIODevice::WriteOnly)) {

        QTextStream out(&txtFile);
        out << tableData;

        txtFile.close();
    }
}

void MaterialEditorActions::onImport() {}

MaterialEditorActions::~MaterialEditorActions() = default;

} // namespace gui2
