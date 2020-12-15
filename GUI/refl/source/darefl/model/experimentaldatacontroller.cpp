// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/experimentaldatacontroller.h>
#include <darefl/model/experimentaldataitems.h>
#include <darefl/model/experimentaldatamodel.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <darefl/model/modelutils.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/modelutils.h>

namespace DaRefl {

ExperimentalDataController::ExperimentalDataController(ExperimentalDataModel* data_model,
                                                       InstrumentModel* instrument_model)
    : ModelListener(data_model), m_instrument_model(instrument_model) {
    setOnDataChange([this](auto, auto) { update_all(); });
    setOnItemInserted([this](auto, auto) { update_all(); });
    setOnItemRemoved([this](auto, auto) { update_all(); });
    setOnModelReset([this](auto) { update_all(); });

    update_all();
}

//! Updates all material properties in LayerItems to get new material colors and labels.

void ExperimentalDataController::update_all() {
    for (auto scan : ModelView::Utils::FindItems<ExperimentalScanItem>(m_instrument_model)) {
        auto property =
            scan->property<ModelView::ExternalProperty>(ExperimentalScanItem::P_IMPORTED_DATA);
        auto updated =
            Utils::FindProperty(Utils::CreateGraphProperties(model()), property.identifier());
        if (property != updated)
            scan->setProperty(ExperimentalScanItem::P_IMPORTED_DATA, updated);
    }
}

} // namespace DaRefl
