// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <darefl/quicksimeditor/jobmanager.h>
#include <darefl/quicksimeditor/speculartoysimulation.h>

namespace DaRefl {

JobManager::JobManager(QObject* parent) : QObject(parent), m_isRunning(true) {
    // starting thread to run consequent simulations
    m_simThread = std::thread{&JobManager::wait_and_run, this};
}

JobManager::~JobManager() {
    m_isRunning = false;
    // making stack throw to stops waiting in JobManager::wait_and_run
    m_requestedInputValues.stop();
    m_simThread.join();
}

//! Returns vector representing results of a simulation.

SimulationResult JobManager::simulationResult() {
    auto result = m_simulationResult.try_pop();
    return result ? *result.get() : SimulationResult();
}

//! Performs simulation request. Given multislice will be stored in a stack of values to trigger
//! a waiting thread.

void JobManager::requestSimulation(const multislice_t& multislice,
                                   const std::vector<double>& qvalues, double intensity) {
    // At this point, non-empty stack means that currently simulation thread is busy.
    // Replacing top value in a stack, meaning that we are droping previous request.
    SimulationInput input_data;
    input_data.slice_data = multislice;
    input_data.qvalues = qvalues;
    input_data.intensity = intensity;
    m_requestedInputValues.update_top(input_data);
}

//! Processes interrupt request by setting corresponding flag.

void JobManager::onInterruptRequest() {
    m_interruptRequest = true;
}

//! Performs concequent simulations for given simulation parameter. Waits for simulation input
//! parameter to appear in a stack, starts new simulation as soon as input data is ready.
//! Method is intended for execution in a thread.

void JobManager::wait_and_run() {
    while (m_isRunning) {
        try {
            // Waiting here for the value which we will use as simulation input parameter.
            auto value = m_requestedInputValues.wait_and_pop();

            // preparing simulation
            SpecularToySimulation simulation(*value.get());
            auto on_progress = [this](int value) {
                progressChanged(value);
                return m_interruptRequest;
            };
            simulation.setProgressCallback(on_progress);

            // running simulation
            simulation.runSimulation();

            // Saving simulation result, overwrite previous if exists. If at this point stack
            // with results is not empty it means that plotting is disabled or running too slow.
            m_simulationResult.update_top(simulation.simulationResult());
            simulationCompleted();

        } catch (std::exception& ex) {
            // Exception is thrown
            // a) If waiting on stack was stopped my calling threadsafe_stack::stop.
            // b) If simulation was interrupted via interrupt_request
            m_interruptRequest = false;
            progressChanged(0);
        }
    }
}

} // namespace DaRefl
