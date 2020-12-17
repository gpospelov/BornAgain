//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/experimentaldatacontroller.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/model/experimentaldatacontroller.h"
#include "gui2/model/experimentaldataitems.h"
#include "gui2/model/experimentaldatamodel.h"
#include "gui2/model/instrumentitems.h"
#include "gui2/model/instrumentmodel.h"
#include "gui2/model/modelutils.h"
#include "mvvm/model/externalproperty.h"
#include "mvvm/model/modelutils.h"

namespace gui2 {

ExperimentalDataController::ExperimentalDataController(ExperimentalDataModel* data_model,
                                                       InstrumentModel* instrument_model)
    : ModelListener(data_model), m_instrument_model(instrument_model)
{
    setOnDataChange([this](auto, auto) { update_all(); });
    setOnItemInserted([this](auto, auto) { update_all(); });
    setOnItemRemoved([this](auto, auto) { update_all(); });
    setOnModelReset([this](auto) { update_all(); });

    update_all();
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void ExperimentalDataController::update_all()
{
    for (auto scan : ModelView::Utils::FindItems<ExperimentalScanItem>(m_instrument_model)) {
        auto property =
            scan->property<ModelView::ExternalProperty>(ExperimentalScanItem::P_IMPORTED_DATA);
        auto updated =
            Utils::FindProperty(Utils::CreateGraphProperties(model()), property.identifier());
        if (property != updated)
            scan->setProperty(ExperimentalScanItem::P_IMPORTED_DATA, updated);
    }
}

} // namespace gui2
