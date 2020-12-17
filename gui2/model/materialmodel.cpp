//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/materialmodel.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/materialmodel.h"
#include "gui2/model/item_constants.h"
#include "gui2/model/materialitems.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/itemcatalogue.h"
#include "mvvm/widgets/widgetutils.h"
#include <QColor>

using namespace ModelView;

namespace {

std::unique_ptr<ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<gui2::MaterialContainerItem>();
    result->registerItem<gui2::SLDMaterialItem>();
    return result;
}

const double rho_si = 2.0704e-06;
const double mu_si = 5.96e-07;

const double rho_default = 9.4245e-06;
const double mu_default = 0.0;

const std::string air_material_name = "Air";
const std::string substrate_material_name = "Si";
const std::string default_material_name = "Default";

//! Returns map of good looking colors for standard material names.

std::map<std::string, QColor> name_to_color_map()
{
    std::map<std::string, QColor> result = {{air_material_name, QColor(179, 242, 255)},
                                            {substrate_material_name, QColor(205, 102, 0)},
                                            {default_material_name, QColor(Qt::green)}};
    return result;
}

QColor suggestMaterialColor(const std::string& name)
{
    static auto color_map = name_to_color_map();
    auto it = color_map.find(name);
    return it != color_map.end() ? it->second : Utils::RandomColor();
}

} // namespace

namespace gui2 {

MaterialModel::MaterialModel(std::shared_ptr<ModelView::ItemPool> pool)
    : SessionModel("MaterialModel", pool)
{
    init_model();
}

//! Returns vector of properties representing possible choice of materials for the given container.
//! Here we assume that all materials seats in top level material containers.
//! If no container_id was given, the very first container is examined.

// TODO Simplify and cover with unit tests.

std::vector<ExternalProperty> MaterialModel::material_data(std::string container_id) const
{
    std::vector<ExternalProperty> result;
    const auto containers = rootItem()->children();
    if (!containers.empty() && container_id.empty())
        container_id = topItem<MaterialContainerItem>()->identifier();

    for (auto container : containers) {
        if (container->identifier() != container_id)
            continue;
        for (auto item : container->children()) {
            if (auto material = dynamic_cast<MaterialBaseItem*>(item))
                result.push_back(material->external_property());
        }
    }
    return result;
}

//! Returns property from given material id.

ExternalProperty MaterialModel::material_property(const std::string& id)
{
    for (const auto& prop : material_data())
        if (prop.identifier() == id)
            return prop;

    return ExternalProperty::undefined();
}

//! Clones material and adds it at the bottom of MaterialContainerItem.

MaterialBaseItem* MaterialModel::cloneMaterial(const MaterialBaseItem* item)
{
    auto tagrow = item->tagRow().next();
    return static_cast<MaterialBaseItem*>(SessionModel::copyItem(item, item->parent(), tagrow));
}

//! Adds default material.

SLDMaterialItem* MaterialModel::addDefaultMaterial(const ModelView::TagRow& tagrow)
{
    auto material = insertItem<SLDMaterialItem>(materialContainer(), tagrow);
    material->set_properties("Default", QColor(Qt::green), rho_default, mu_default);
    return material;
}

//! Populates the model with some default content.

void MaterialModel::init_model()
{
    setItemCatalogue(CreateItemCatalogue());

    auto container = insertItem<MaterialContainerItem>();
    auto material = insertItem<SLDMaterialItem>(container);
    material->set_properties(air_material_name, suggestMaterialColor(air_material_name), 0.0, 0.0);
    material = insertItem<SLDMaterialItem>(container);
    material->set_properties(default_material_name, suggestMaterialColor(default_material_name),
                             rho_default, mu_default);
    material = insertItem<SLDMaterialItem>(container);
    material->set_properties(substrate_material_name, suggestMaterialColor(substrate_material_name),
                             rho_si, mu_si);
}

MaterialContainerItem* MaterialModel::materialContainer()
{
    return topItem<MaterialContainerItem>();
}

} // namespace gui2
