// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/core/app_constants.h>
#include <darefl/model/applicationmodels.h>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/instrumentmodel.h>
#include <darefl/model/jobitem.h>
#include <darefl/model/jobmodel.h>
#include <darefl/model/materialmodel.h>
#include <darefl/model/sampleitems.h>
#include <darefl/model/samplemodel.h>
#include <darefl/quicksimeditor/jobmanager.h>
#include <darefl/quicksimeditor/quicksimcontroller.h>
#include <darefl/quicksimeditor/quicksimutils.h>
#include <darefl/quicksimeditor/speculartoysimulation.h>
#include <mvvm/project/modelhaschangedcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>

namespace
{
const int profile_points_count = 1000;
}

namespace DaRefl
{

QuickSimController::QuickSimController(QObject* parent)
    : QObject(parent)
    , m_jobManager(new JobManager(this))
    , m_isRealTimeMode(Constants::live_simulation_default_on)
{
}

QuickSimController::~QuickSimController() = default;

void QuickSimController::setModels(ApplicationModels* models)
{
    m_models = models;

    auto on_model_change = [this]() { onMultiLayerChange(); };
    m_materialChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->materialModel(), on_model_change);
    m_sampleChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->sampleModel(), on_model_change);
    m_instrumentChangedController = std::make_unique<ModelView::ModelHasChangedController>(
        m_models->instrumentModel(), on_model_change);

    setup_jobmanager_connections();

    onMultiLayerChange();
    jobModel()->sldViewport()->setViewportToContent();
}

//! Requests interruption of running simulaitons.

void QuickSimController::onInterruptRequest()
{
    m_jobManager->onInterruptRequest();
}

void QuickSimController::onRealTimeRequest(bool status)
{
    m_isRealTimeMode = status;
}

//! Processes multilayer on request. Doesn't work in real time mode.

void QuickSimController::onRunSimulationRequest()
{
    process_multilayer(/*submit_simulation*/ true);
}

//! Processes multilayer on any model change. Works only in realtime mode.

void QuickSimController::onMultiLayerChange()
{
    process_multilayer(/*submit_simulation*/ m_isRealTimeMode);
}

//! Takes simulation results from JobManager and write into the model.

void QuickSimController::onSimulationCompleted()
{
    jobModel()->updateSpecularData(m_jobManager->simulationResult());
}

//! Constructs multislice, calculates profile and submits specular simulation.

void QuickSimController::process_multilayer(bool submit_simulation)
{
    auto multilayer = m_models->sampleModel()->topItem<MultiLayerItem>();
    auto slices = Utils::CreateMultiSlice(*multilayer);
    update_sld_profile(slices);
    if (submit_simulation)
        submit_specular_simulation(slices);
}

//! Calculates sld profile from slice and immediately update data items.

void QuickSimController::update_sld_profile(const multislice_t& multislice)
{
    auto data = SpecularToySimulation::sld_profile(multislice, profile_points_count);
    jobModel()->updateSLDProfile(data);
}

//! Submit data to JobManager for consequent specular simulation in a separate thread.

void QuickSimController::submit_specular_simulation(const multislice_t& multislice)
{
    auto instrument = instrumentModel()->topItem<SpecularInstrumentItem>();
    auto beam = instrument->beamItem();
    m_jobManager->requestSimulation(multislice, beam->qScanValues(), beam->intensity());
}

//! Connect signals going from JobManager. Connections are made queued since signals are emitted
//! from non-GUI thread and we want to deal with widgets.

void QuickSimController::setup_jobmanager_connections()
{

    // Simulation progress is propagated from JobManager to this controller for further forwarding.
    connect(m_jobManager, &JobManager::progressChanged, this, &QuickSimController::progressChanged,
            Qt::QueuedConnection);

    // Notification about completed simulation from jobManager to this controller.
    connect(m_jobManager, &JobManager::simulationCompleted, this,
            &QuickSimController::onSimulationCompleted, Qt::QueuedConnection);
}

JobModel* QuickSimController::jobModel() const
{
    return m_models->jobModel();
}

InstrumentModel* QuickSimController::instrumentModel() const
{
    return m_models->instrumentModel();
}

} // namespace DaRefl
