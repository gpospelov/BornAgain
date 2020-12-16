// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QModelIndex>
#include <algorithm>
#include "gui2/model/applicationmodels.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/experimentaldatamodel.h"
#include "gui2/model/materialmodel.h"
#include "gui2/model/modelutils.h"
#include "gui2/quicksimeditor/custombeampropertyeditorfactory.h"
#include "mvvm/editors/externalpropertycomboeditor.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/modelutils.h"
#include "mvvm/standarditems/graphitem.h"

using namespace ModelView;

namespace DaRefl {

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

} // namespace DaRefl
