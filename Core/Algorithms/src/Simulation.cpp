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
: IParameterized("Simulation")
, mp_sample(0)
//, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(0)
{
    init_parameters();
}

Simulation::Simulation(const ProgramOptions *p_options)
: IParameterized("Simulation")
, mp_sample(0)
//, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(
    const ISample& p_sample, const ProgramOptions *p_options)
: IParameterized("Simulation")
, mp_sample(p_sample.clone())
//, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(
    SampleBuilder_t p_sample_builder, const ProgramOptions *p_options)
: IParameterized("Simulation")
, mp_sample(0)
, mp_sample_builder(p_sample_builder)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(const Simulation& other)
: ICloneable(), IParameterized(other)
, mp_sample(0)
, mp_sample_builder(other.mp_sample_builder)
, m_instrument(other.m_instrument)
, m_sim_params(other.m_sim_params)
, m_thread_info(other.m_thread_info)
, m_intensity_map()
, m_is_normalized(other.m_is_normalized)
, mp_options(other.mp_options)
, m_distribution_handler(other.m_distribution_handler)
, m_progress(other.m_progress)
{
    if(other.mp_sample) mp_sample = other.mp_sample->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);

    init_parameters();
}

void Simulation::init_parameters()
{
}

Simulation *Simulation::clone() const
{
    return new Simulation(*this);
}

void Simulation::prepareSimulation()
{
    if(!m_instrument.getDetectorDimension()) {
        throw LogicErrorException("Simulation::prepareSimulation() "
                "-> Error. The detector was not configured.");
    }
    gsl_set_error_handler_off();
    m_is_normalized = false;
    updateSample();
}

//! Run simulation with possible averaging over parameter distributions
void Simulation::runSimulation()
{
    prepareSimulation();
    if( !mp_sample)
        throw NullPointerException(
            "Simulation::runSimulation() -> Error! No sample set.");

    size_t param_combinations = m_distribution_handler.getTotalNumberOfSamples();

    if(m_progress) m_progress->init(this, param_combinations);

    // no averaging needed:
    if (param_combinations == 1) {
        boost::scoped_ptr<ParameterPool > p_param_pool(createParameterTree());
        m_distribution_handler.setParameterValues(p_param_pool.get(), 0);
        updateSample();
        runSingleSimulation();
        //std::cout << "Simulation::runSimulation() -> about to exit " << m_progress.getProgress() << " " << m_progress.getNitems() << std::endl;
        return;
    }

    // average over parameter distributions:
    OutputData<double> total_intensity;
    total_intensity.copyShapeFrom(m_intensity_map);
    total_intensity.setAllTo(0.);
    boost::scoped_ptr<ParameterPool > p_param_pool(createParameterTree());
    for (size_t index=0; index < param_combinations; ++index) {
        double weight = m_distribution_handler.setParameterValues(
                p_param_pool.get(), index);
        updateSample();
        runSingleSimulation();
        m_intensity_map.scaleAll(weight);
        total_intensity += m_intensity_map;
    }
    m_intensity_map.copyFrom(total_intensity);
}

void Simulation::runOMPISimulation()
{
    OMPISimulation ompi;
    ompi.runSimulation(this);
}


void Simulation::normalize()
{
    if (!m_is_normalized) {
        m_instrument.normalize(&m_intensity_map);
        m_is_normalized = true;
    }
}

//! The ISample object will not be owned by the Simulation object
void Simulation::setSample(const ISample& sample)
{
    delete mp_sample;
    mp_sample = sample.clone();
}

void Simulation::setSampleBuilder(SampleBuilder_t p_sample_builder)
{
    if( !p_sample_builder.get() )
        throw NullPointerException(
            "Simulation::setSampleBuilder() -> "
            "Error! Attempt to set null sample builder.");

    mp_sample_builder = p_sample_builder;
    delete mp_sample;
    mp_sample = 0;
}

OutputData<double> *Simulation::getIntensityData() const
{
    OutputData<double> *result = m_intensity_map.clone();
    m_instrument.applyDetectorResolution(result);
    return result;
}

void Simulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMapAxes();
}

void Simulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength<=0.0) {
        throw ClassInitializationException(
                "Simulation::setBeamParameters() "
                "-> Error. Incoming wavelength <= 0.");
    }

    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
}

void Simulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

void Simulation::setBeamPolarization(const kvector_t &bloch_vector)
{
    m_instrument.setBeamPolarization(bloch_vector);
}

std::string Simulation::addParametersToExternalPool(
    std::string path, ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path =
        IParameterized::addParametersToExternalPool(
            path, external_pool, copy_number);

    // add parameters of the instrument
    m_instrument.addParametersToExternalPool(new_path, external_pool, -1);

    if (mp_sample_builder.get()) {
       // add parameters of the sample builder
        mp_sample_builder->addParametersToExternalPool(
            new_path, external_pool, -1);
    } else if (mp_sample) {
        // add parameters of directly the sample
        mp_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Simulation::addParameterDistribution(const std::string &param_name,
                                          const IDistribution1D &distribution,
                                          size_t nbr_samples,
                                          double sigma_factor,
                                          const AttLimits &limits) {
    m_distribution_handler.addParameterDistribution(param_name,
                                                    distribution, nbr_samples, sigma_factor, limits);
}

void Simulation::addParameterDistribution(const ParameterDistribution &par_distr)
{
    m_distribution_handler.addParameterDistribution(par_distr);
}

const DistributionHandler &Simulation::getDistributionHandler() const
{
    return m_distribution_handler;
}

void Simulation::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
    }
    m_intensity_map.setAllTo(0.);
}

void Simulation::updateSample()
{
    if (mp_sample_builder.get()) {
        ISample *p_new_sample = mp_sample_builder->buildSample();
        std::string builder_type = typeid(*mp_sample_builder).name();
        if( builder_type.find("ISampleBuilder_wrapper") != std::string::npos ) {
            msglog(MSG::DEBUG2) << "Simulation::updateSample() -> "
                "OMG, some body has called me from python, what an idea... ";
            setSample(*p_new_sample);
        } else {
            delete mp_sample;
            mp_sample = p_new_sample;
        }
    }
}

void Simulation::setDetectorParameters(const OutputData<double >& output_data)
{
    m_instrument.matchDetectorParameters(output_data);

    m_intensity_map.clear();
    m_intensity_map.copyShapeFrom(output_data); // to copy mask too
    m_intensity_map.setAllTo(0.);
}

void Simulation::setDetectorParameters(
    size_t n_phi, double phi_f_min, double phi_f_max,
    size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style)
{
    m_instrument.setDetectorParameters(
        n_phi, phi_f_min, phi_f_max,
        n_alpha, alpha_f_min, alpha_f_max, isgisaxs_style);
    updateIntensityMapAxes();
}

void Simulation::setDetectorParameters(const DetectorParameters& params)
{
    m_instrument.setDetectorParameters(params);
    updateIntensityMapAxes();
}

void Simulation::setDetectorResolutionFunction(
    const IResolutionFunction2D &p_resolution_function)
{
    m_instrument.setDetectorResolutionFunction(p_resolution_function);
}

void Simulation::removeDetectorResolutionFunction()
{
    m_instrument.setDetectorResolutionFunction(0);
}

void Simulation::setDetectorPolarization(const kvector_t &bloch_vector)
{
    m_instrument.setDetectorPolarization(bloch_vector);
}

void Simulation::addToIntensityMap(DWBASimulation* p_dwba_simulation)
{
    m_intensity_map += p_dwba_simulation->getDWBAIntensity();
}

//! Run single simulation with fixed parameter values.
//! Also manage threads.
void Simulation::runSingleSimulation()
{
    m_intensity_map.setAllTo(0.);
    // retrieve batch and threading information
    if (mp_options) {
        if (mp_options->find("nbatches")) {
            m_thread_info.n_batches = (*mp_options)["nbatches"].as<int>();
        }
        if (mp_options->find("currentbatch")) {
            m_thread_info.current_batch =
                    (*mp_options)["currentbatch"].as<int>();
        }
        if (mp_options->find("threads")) {
            m_thread_info.n_threads = (*mp_options)["threads"].as<int>();
        }
    }

    if (m_thread_info.n_threads<0) m_thread_info.n_threads = 1;
    if(m_thread_info.n_threads==1) {
        // Single thread.
        DWBASimulation *p_dwba_simulation =
                mp_sample->createDWBASimulation();
        verifyDWBASimulation(p_dwba_simulation);
        p_dwba_simulation->init(*this);
        p_dwba_simulation->setThreadInfo(m_thread_info);
        p_dwba_simulation->run();  // the work is done here
        if(p_dwba_simulation->isCompleted()) {
            addToIntensityMap(p_dwba_simulation);
            delete p_dwba_simulation;
        } else {
            std::string message = p_dwba_simulation->getRunMessage();
            delete p_dwba_simulation;
            throw Exceptions::RuntimeErrorException("Simulation::runSimulation() -> Simulation has terminated unexpectedly with following error message.\n"+message);
        }
    } else {
        // Multithreading.
        if(m_thread_info.n_threads == 0 )  {
            // Take optimal number of threads from the hardware.
            m_thread_info.n_threads =
                    (int)boost::thread::hardware_concurrency();
            msglog(MSG::DEBUG)
                << "Simulation::runSimulation() -> Info. Number of threads "
                << m_thread_info.n_threads << " (taken from hardware concurrency)"
                << ", n_batches = " << m_thread_info.n_batches
                << ", current_batch = " << m_thread_info.current_batch;
        } else {
            msglog(MSG::DEBUG)
                << "Simulation::runSimulation() -> Info. Number of threads "
                << m_thread_info.n_threads << " (ordered by user)"
                << ", n_batches = " << m_thread_info.n_batches
                << ", current_batch = " << m_thread_info.current_batch;
        }
        std::vector<boost::thread*> threads;
        std::vector<DWBASimulation*> simulations;

        // Initialize n simulations.
        for(int i_thread=0; i_thread<m_thread_info.n_threads; ++i_thread){
            DWBASimulation *p_dwba_simulation =
                mp_sample->createDWBASimulation();
            verifyDWBASimulation(p_dwba_simulation);
            p_dwba_simulation->init(*this);
            m_thread_info.current_thread = i_thread;
            p_dwba_simulation->setThreadInfo(m_thread_info);
            simulations.push_back(p_dwba_simulation);
        }

        // Run simulations in n threads.
        for (std::vector<DWBASimulation*>::iterator it=
                 simulations.begin(); it!=simulations.end(); ++it) {
            threads.push_back
                (new boost::thread(boost::bind(&DWBASimulation::run, *it)) );
        }

        // Wait for threads to complete.
        for(size_t i=0; i<threads.size(); ++i) {
            threads[i]->join();
        }

        // Merge simulated data.
        bool isSuccess(true);
        std::string failure_message;
        for(size_t i=0; i<simulations.size(); ++i) {
            if(simulations[i]->isCompleted()) {
                addToIntensityMap(simulations[i]);
            } else {
                isSuccess = false;
                failure_message = simulations[i]->getRunMessage();
            }
            delete simulations[i];
            delete threads[i];
        }
        if(!isSuccess) {
            throw Exceptions::RuntimeErrorException(
                "Simulation::runSingleSimulation() -> Simulation has terminated unexpectedly "
                "with the following error message.\n" + failure_message);
        }
    }
//    if( mp_sample->containsMagneticMaterial() ) {
//        m_instrument.applyDetectorResolution(&m_intensity_map,
//                &m_polarization_output);
//    }
//    else {
//        m_instrument.applyDetectorResolution(&m_intensity_map);
//    }

}


void Simulation::verifyDWBASimulation(DWBASimulation *dwbaSimulation)
{
    if (!dwbaSimulation)
        throw RuntimeErrorException(
            "Simulation::runSimulation() -> Can't create the simulation for given sample."
            "It should be either the MultiLayer with more than one layer (with or without particles),"
            "or MultiLayer with single Layer containing particles.");
}


//! initializes DWBA progress handler
void Simulation::initProgressHandlerDWBA(ProgressHandlerDWBA *dwba_progress)
{
    // if we have external ProgressHandler (which is normally coming from GUI),
    // then we will create special callbacks for every DWBASimulation.
    // These callback will be used to report DWBASimulation progress to the Simulation.
    if(m_progress) {
        ProgressHandler::Callback_t callback = boost::bind(&ProgressHandler::update, m_progress.get(), _1);
        dwba_progress->setCallback(callback);
    }
}
