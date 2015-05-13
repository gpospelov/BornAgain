// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Simulation.h"

#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "DWBASimulation.h"
#include "MessageService.h"
#include "OutputDataFunctions.h"
#include "BornAgainNamespace.h"
#include "ProgressHandlerDWBA.h"
#include "OMPISimulation.h"

#include "Macros.h"
GCC_DIAG_OFF(strict-aliasing);
#include <boost/thread.hpp>
GCC_DIAG_ON(strict-aliasing);
#include <gsl/gsl_errno.h>
#include <boost/scoped_ptr.hpp>

Simulation::Simulation()
    : IParameterized("Simulation"), mp_sample(0), m_is_normalized(false), mp_options(0)
{
    init_parameters();
}

Simulation::Simulation(const ProgramOptions *p_options)
    : IParameterized("Simulation"), mp_sample(0), m_is_normalized(false), mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(const ISample &p_sample, const ProgramOptions *p_options)
    : IParameterized("Simulation"), mp_sample(p_sample.clone()), m_is_normalized(false),
      mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(SampleBuilder_t p_sample_builder, const ProgramOptions *p_options)
    : IParameterized("Simulation"), mp_sample(0), mp_sample_builder(p_sample_builder),
      m_is_normalized(false), mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(const Simulation &other)
    : ICloneable(), IParameterized(other), mp_sample(0), mp_sample_builder(other.mp_sample_builder),
      m_sim_params(other.m_sim_params), m_thread_info(other.m_thread_info),
      m_is_normalized(other.m_is_normalized), mp_options(other.mp_options),
      m_distribution_handler(other.m_distribution_handler), m_progress(other.m_progress)
{
    if (other.mp_sample)
        mp_sample = other.mp_sample->clone();

    init_parameters();
}

void Simulation::init_parameters()
{
}

void Simulation::prepareSimulation()
{
    gsl_set_error_handler_off();
    m_is_normalized = false;
    updateSample();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    prepareSimulation();
    if (!mp_sample)
        throw NullPointerException("Simulation::runSimulation() -> Error! No sample set.");

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    initSimulationElementVector();
    if (m_progress)
        // TODO:       m_progress->init(this, param_combinations);

        // Initialize vector of simulation elements

    // no averaging needed:
    if (param_combinations == 1) {
        boost::scoped_ptr<ParameterPool> p_param_pool(createParameterTree());
        m_distribution_handler.setParameterValues(p_param_pool.get(), 0);
        updateSample();
        runSingleSimulation();
        transferResultsToIntensityMap();
        return;
    }

    // average over parameter distributions:
    std::vector<SimulationElement> total_intensity = m_sim_elements;
    boost::scoped_ptr<ParameterPool> p_param_pool(createParameterTree());
    for (size_t index = 0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(p_param_pool.get(), index);
        updateSample();
        runSingleSimulation();
        AddElementsWithWeight(m_sim_elements.begin(), m_sim_elements.end(), total_intensity.begin(),
                              weight);
    }
    m_sim_elements = total_intensity;
    transferResultsToIntensityMap();
}

void Simulation::runOMPISimulation()
{
    OMPISimulation ompi;
    ompi.runSimulation(this);
}

//! The ISample object will not be owned by the Simulation object
void Simulation::setSample(const ISample &sample)
{
    delete mp_sample;
    mp_sample = sample.clone();
}

void Simulation::setSampleBuilder(SampleBuilder_t p_sample_builder)
{
    if (!p_sample_builder.get())
        throw NullPointerException("Simulation::setSampleBuilder() -> "
                                   "Error! Attempt to set null sample builder.");

    mp_sample_builder = p_sample_builder;
    delete mp_sample;
    mp_sample = 0;
}

std::string Simulation::addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    if (mp_sample_builder.get()) {
        // add parameters of the sample builder
        mp_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    } else if (mp_sample) {
        // add parameters of directly the sample
        mp_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Simulation::addParameterDistribution(const std::string &param_name,
                                          const IDistribution1D &distribution, size_t nbr_samples,
                                          double sigma_factor, const AttLimits &limits)
{
    m_distribution_handler.addParameterDistribution(param_name, distribution, nbr_samples,
                                                    sigma_factor, limits);
}

void Simulation::addParameterDistribution(const ParameterDistribution &par_distr)
{
    m_distribution_handler.addParameterDistribution(par_distr);
}

const DistributionHandler &Simulation::getDistributionHandler() const
{
    return m_distribution_handler;
}

double Simulation::getWavelength() const
{
    throw RuntimeErrorException(
        "Simulation::getWavelength: not uniquely defined for this type of Simulation");
}

void Simulation::updateSample()
{
    if (mp_sample_builder.get()) {
        ISample *p_new_sample = mp_sample_builder->buildSample();
        std::string builder_type = typeid(*mp_sample_builder).name();
        if (builder_type.find("ISampleBuilder_wrapper") != std::string::npos) {
            msglog(MSG::DEBUG2) << "Simulation::updateSample() -> "
                                   "OMG, some body has called me from python, what an idea... ";
            setSample(*p_new_sample);
        } else {
            delete mp_sample;
            mp_sample = p_new_sample;
        }
    }
}

//! Run single simulation with fixed parameter values.
//! Also manage threads.
void Simulation::runSingleSimulation()
{
    // retrieve batch and threading information
    if (mp_options) {
        if (mp_options->find("nbatches")) {
            m_thread_info.n_batches = (*mp_options)["nbatches"].as<int>();
        }
        if (mp_options->find("currentbatch")) {
            m_thread_info.current_batch = (*mp_options)["currentbatch"].as<int>();
        }
        if (mp_options->find("threads")) {
            m_thread_info.n_threads = (*mp_options)["threads"].as<int>();
        }
    }

    if (m_thread_info.n_threads < 0)
        m_thread_info.n_threads = 1;
    if (m_thread_info.n_threads == 1) {
        // Single thread.
        DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
        verifyDWBASimulation(p_dwba_simulation);
        p_dwba_simulation->init(*this, m_sim_elements.begin(), m_sim_elements.end());
        p_dwba_simulation->run(); // the work is done here
        if (!p_dwba_simulation->isCompleted()) {
            std::string message = p_dwba_simulation->getRunMessage();
            delete p_dwba_simulation;
            throw Exceptions::RuntimeErrorException("Simulation::runSimulation() -> Simulation has "
                                                    "terminated unexpectedly with following error "
                                                    "message.\n" + message);
        }
        delete p_dwba_simulation;
    } else {
        // Multithreading.
        if (m_thread_info.n_threads == 0) {
            // Take optimal number of threads from the hardware.
            m_thread_info.n_threads = (int)boost::thread::hardware_concurrency();
            msglog(MSG::DEBUG) << "Simulation::runSimulation() -> Info. Number of threads "
                               << m_thread_info.n_threads << " (taken from hardware concurrency)"
                               << ", n_batches = " << m_thread_info.n_batches
                               << ", current_batch = " << m_thread_info.current_batch;
        } else {
            msglog(MSG::DEBUG) << "Simulation::runSimulation() -> Info. Number of threads "
                               << m_thread_info.n_threads << " (ordered by user)"
                               << ", n_batches = " << m_thread_info.n_batches
                               << ", current_batch = " << m_thread_info.current_batch;
        }
        std::vector<boost::thread *> threads;
        std::vector<DWBASimulation *> simulations;

        // Initialize n simulations.
        int total_nbr_elements = m_sim_elements.size();
        int element_thread_step = total_nbr_elements / m_thread_info.n_threads;
        for (int i_thread = 0; i_thread < m_thread_info.n_threads; ++i_thread) {
            DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
            verifyDWBASimulation(p_dwba_simulation);
            std::vector<SimulationElement>::iterator begin_it = m_sim_elements.begin()
                                                                + i_thread * element_thread_step;
            std::vector<SimulationElement>::iterator end_it;
            if (i_thread == m_thread_info.n_threads - 1) {
                end_it = m_sim_elements.end();
            } else {
                end_it = m_sim_elements.begin() + (i_thread + 1) * element_thread_step;
            }
            p_dwba_simulation->init(*this, begin_it, end_it);
            simulations.push_back(p_dwba_simulation);
        }

        // Run simulations in n threads.
        for (std::vector<DWBASimulation *>::iterator it = simulations.begin();
             it != simulations.end(); ++it) {
            threads.push_back(new boost::thread(boost::bind(&DWBASimulation::run, *it)));
        }

        // Wait for threads to complete.
        for (size_t i = 0; i < threads.size(); ++i) {
            threads[i]->join();
        }

        // Merge simulated data.
        bool isSuccess(true);
        std::string failure_message;
        for (size_t i = 0; i < simulations.size(); ++i) {
            if (!simulations[i]->isCompleted()) {
                isSuccess = false;
                failure_message = simulations[i]->getRunMessage();
            }
            delete simulations[i];
            delete threads[i];
        }
        if (!isSuccess) {
            throw Exceptions::RuntimeErrorException(
                "Simulation::runSingleSimulation() -> Simulation has terminated unexpectedly "
                "with the following error message.\n" + failure_message);
        }
    }
}

void Simulation::initProgressHandlerDWBA(ProgressHandlerDWBA *dwba_progress)
{
    // if we have external ProgressHandler (which is normally coming from GUI),
    // then we will create special callbacks for every DWBASimulation.
    // These callback will be used to report DWBASimulation progress to the Simulation.
    if (m_progress) {
        ProgressHandler::Callback_t callback
            = boost::bind(&ProgressHandler::update, m_progress.get(), _1);
        dwba_progress->setCallback(callback);
    }
}

void Simulation::verifyDWBASimulation(DWBASimulation *dwbaSimulation)
{
    if (!dwbaSimulation)
        throw RuntimeErrorException(
            "Simulation::runSimulation() -> Can't create the simulation for given sample."
            "It should be either the MultiLayer with more than one layer (with or without "
            "particles),"
            "or MultiLayer with single Layer containing particles.");
}
