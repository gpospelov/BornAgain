// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/quicksimeditor/simplotcontroller.h"
#include "gui2/model/applicationmodels.h"
#include "gui2/model/instrumentitems.h"
#include "gui2/model/instrumentmodel.h"
#include "gui2/model/jobitem.h"
#include "gui2/model/jobmodel.h"
#include "mvvm/project/modelhaschangedcontroller.h"

namespace DaRefl {

SimPlotController::SimPlotController(QObject* parent) : QObject(parent) {}

void SimPlotController::setModels(ApplicationModels* models) {
    m_models = models;

    auto on_model_change = [this]() { onInstrumentChange(); };
    m_instrumentChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->instrumentModel(), on_model_change);
}

void SimPlotController::onInstrumentChange() {
    auto instrument = m_models->instrumentModel()->topItem<SpecularInstrumentItem>();
    auto graph = instrument->beamItem()->experimentalGraphItem();
    m_models->jobModel()->updateReferenceGraph(graph);
}

SimPlotController::~SimPlotController() = default;

} // namespace DaRefl
