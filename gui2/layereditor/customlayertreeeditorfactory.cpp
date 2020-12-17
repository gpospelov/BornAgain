//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/layereditor/customlayertreeeditorfactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/layereditor/customlayertreeeditorfactory.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/materialmodel.h"
#include "mvvm/editors/externalpropertycomboeditor.h"
#include "mvvm/model/externalproperty.h"
#include <QModelIndex>
#include <algorithm>

using namespace ModelView;

namespace gui2 {

namespace {
//! Return list of possible choices for material properties in MaterialModel.
//! Use "undefined material" as a first item in a list.
std::vector<ModelView::ExternalProperty> get_choice_of_materials(MaterialModel* model) {
    std::vector<ModelView::ExternalProperty> result{ModelView::ExternalProperty::undefined()};
    auto other_data = model->material_data();
    std::copy(other_data.begin(), other_data.end(), std::back_inserter(result));
    return result;
}
} // namespace

CustomLayerTreeEditorFactory::~CustomLayerTreeEditorFactory() = default;

CustomLayerTreeEditorFactory::CustomLayerTreeEditorFactory(ApplicationModels* models)
    : m_models(models) {}

std::unique_ptr<CustomEditor>
CustomLayerTreeEditorFactory::createEditor(const QModelIndex& index) const {
    auto value = index.data(Qt::EditRole);
    if (Utils::IsExtPropertyVariant(value)) {
        auto material_choice_callback = [this]() {
            return get_choice_of_materials(m_models->materialModel());
        };
        return std::make_unique<ExternalPropertyComboEditor>(material_choice_callback);
    } else {
        return DefaultEditorFactory::createEditor(index);
    }
}

} // namespace gui2
