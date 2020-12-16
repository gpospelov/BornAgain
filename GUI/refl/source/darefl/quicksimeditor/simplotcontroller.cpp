// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/model/applicationmodels.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <darefl/model/jobitem.h>
#include <darefl/model/jobmodel.h>
#include <darefl/quicksimeditor/simplotcontroller.h>
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
