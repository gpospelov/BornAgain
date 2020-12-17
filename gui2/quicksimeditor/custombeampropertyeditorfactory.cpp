//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/quicksimeditor/custombeampropertyeditorfactory.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/quicksimeditor/custombeampropertyeditorfactory.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/experimentaldatamodel.h"
#include "gui2/model/materialmodel.h"
#include "gui2/model/modelutils.h"
#include "mvvm/editors/externalpropertycomboeditor.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/graphitem.h"
#include <QModelIndex>
#include <algorithm>

using namespace ModelView;

namespace gui2 {

namespace {

//! Returns vector of ExternalProperty representing imported graphs.
//! Use "Undefined graph" as a first item in a list.

std::vector<ModelView::ExternalProperty> available_graph_properties(ExperimentalDataModel* model) {
    std::vector<ModelView::ExternalProperty> result{ExternalProperty::undefined()};
    auto properties = Utils::CreateGraphProperties(model);
    std::copy(properties.begin(), properties.end(), std::back_inserter(result));
    return result;
}
} // namespace

CustomBeamPropertyEditorFactory::~CustomBeamPropertyEditorFactory() = default;

CustomBeamPropertyEditorFactory::CustomBeamPropertyEditorFactory(ApplicationModels* models)
    : m_models(models) {}

std::unique_ptr<CustomEditor>
CustomBeamPropertyEditorFactory::createEditor(const QModelIndex& index) const {
    auto value = index.data(Qt::EditRole);
    if (ModelView::Utils::IsExtPropertyVariant(value)) {
        auto choice_callback = [this]() {
            return available_graph_properties(m_models->experimentalDataModel());
        };
        return std::make_unique<ExternalPropertyComboEditor>(choice_callback);
    } else {
        return DefaultEditorFactory::createEditor(index);
    }
}

} // namespace gui2
