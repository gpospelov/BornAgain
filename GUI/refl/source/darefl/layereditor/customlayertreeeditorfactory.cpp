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
#include <darefl/layereditor/customlayertreeeditorfactory.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/materialmodel.h>
#include <mvvm/editors/externalpropertycomboeditor.h>
#include <mvvm/model/externalproperty.h>

using namespace ModelView;

namespace DaRefl
{

namespace
{
//! Return list of possible choices for material properties in MaterialModel.
//! Use "undefined material" as a first item in a list.
std::vector<ModelView::ExternalProperty> get_choice_of_materials(MaterialModel* model)
{
    std::vector<ModelView::ExternalProperty> result{ModelView::ExternalProperty::undefined()};
    auto other_data = model->material_data();
    std::copy(other_data.begin(), other_data.end(), std::back_inserter(result));
    return result;
}
} // namespace

CustomLayerTreeEditorFactory::~CustomLayerTreeEditorFactory() = default;

CustomLayerTreeEditorFactory::CustomLayerTreeEditorFactory(ApplicationModels* models)
    : m_models(models)
{
}

std::unique_ptr<CustomEditor>
CustomLayerTreeEditorFactory::createEditor(const QModelIndex& index) const
{
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

} // namespace DaRefl
