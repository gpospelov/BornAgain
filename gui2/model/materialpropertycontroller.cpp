//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/materialpropertycontroller.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/materialpropertycontroller.h"
#include "gui2/model/materialmodel.h"
#include "gui2/model/sampleitems.h"
#include "gui2/model/samplemodel.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/modelutils.h"

using namespace ModelView;

namespace gui2 {

MaterialPropertyController::MaterialPropertyController(MaterialModel* material_model,
                                                       SampleModel* sample_model)
    : ModelListener(material_model), m_sample_model(sample_model)
{
    setOnDataChange([this](auto, auto) { update_all(); });
    setOnItemInserted([this](auto, auto) { update_all(); });
    setOnItemRemoved([this](auto, auto) { update_all(); });
    setOnModelReset([this](auto) { update_all(); });

    update_all();
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void MaterialPropertyController::update_all()
{
    for (auto layer : Utils::FindItems<LayerItem>(m_sample_model)) {
        auto property = layer->property<ExternalProperty>(LayerItem::P_MATERIAL);
        auto updated = model()->material_property(property.identifier());
        if (property != updated)
            layer->setProperty(LayerItem::P_MATERIAL, updated);
    }
}

} // namespace gui2
