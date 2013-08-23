// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/Simulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Simulation.h"

#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "DWBASimulation.h"
#include "MessageService.h"

#include "Macros.h"
GCC_DIAG_OFF(unused-local-typedefs);
#include <boost/thread.hpp>
GCC_DIAG_ON(unused-local-typedefs);
#include <gsl/gsl_errno.h>

Simulation::Simulation()
: IParameterized("Simulation")
, mp_sample(0)
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_polarization_output()
, m_is_normalized(false)
, mp_options(0)
{
    init_parameters();
}

Simulation::Simulation(const Simulation& other)
: IParameterized(other), ICloneable()
, mp_sample(0)
, mp_sample_builder(other.mp_sample_builder)
, m_instrument(other.m_instrument)
, m_sim_params(other.m_sim_params)
, m_intensity_map()
, m_polarization_output()
, m_is_normalized(other.m_is_normalized)
, mp_options(other.mp_options)
{
    if(other.mp_sample) mp_sample = other.mp_sample->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);
    m_polarization_output.copyFrom(other.m_polarization_output);

    init_parameters();
}

Simulation::Simulation(const ProgramOptions *p_options)
: IParameterized("Simulation")
, mp_sample(0)
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_polarization_output()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(
    const ISample& p_sample, const ProgramOptions *p_options)
: IParameterized("Simulation")
, mp_sample(p_sample.clone())
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_polarization_output()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Simulation::Simulation(
    const ISampleBuilder* p_sample_builder, const ProgramOptions *p_options)
: IParameterized("Simulation")
, mp_sample(0)
, mp_sample_builder(p_sample_builder)
, m_instrument()
, m_intensity_map()
, m_polarization_output()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Simulation *Simulation::clone() const
{
    return new Simulation(*this);
}

void Simulation::prepareSimulation()
{
    gsl_set_error_handler_off();
    m_is_normalized = false;
    updateSample();
}

//! Run simulation. Manage threads.

void Simulation::runSimulation()
{
    prepareSimulation();
    if( !mp_sample)
        throw NullPointerException(
            "Simulation::runSimulation() -> Error! No sample set.");
    m_intensity_map.setAllTo(0.);
    m_polarization_output.setAllTo(Eigen::Matrix2d::Zero());

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

    msglog(MSG::DEBUG) << "Simulation::runSimulation(): n_batches = " <<
//    std::cout << "Simulation::runSimulation(): n_batches = " <<
            m_thread_info.n_batches <<
            ", current batch = " << m_thread_info.current_batch <<
            ", n_threads = " << m_thread_info.n_threads <<
            ", sample: " << *mp_sample;

    if (m_thread_info.n_threads<0) m_thread_info.n_threads = 1;
    if(m_thread_info.n_threads==1) {
        // Single thread.
        DWBASimulation *p_dwba_simulation =
                mp_sample->createDWBASimulation();
        if (!p_dwba_simulation)
            throw NullPointerException(
                "Simulation::runSimulation() -> No dwba simulation");
        p_dwba_simulation->init(*this);
        p_dwba_simulation->setThreadInfo(m_thread_info);
        p_dwba_simulation->run();  // the work is done here
        addToIntensityMaps(p_dwba_simulation);
        delete p_dwba_simulation;
    } else {
        // Multithreading.
        if(m_thread_info.n_threads == 0 )  {
            // Take optimal number of threads from the hardware.
            m_thread_info.n_threads =
                    (int)boost::thread::hardware_concurrency();
            msglog(MSG::INFO) <<
                "Simulation::runSimulation() -> Info. Number of threads " <<
                m_thread_info.n_threads << " (taken from hardware concurrency)";
        } else {
            msglog(MSG::INFO) <<
                "Simulation::runSimulation() -> Info. Number of threads " <<
                m_thread_info.n_threads;
        }
        std::vector<boost::thread*> threads;
        std::vector<DWBASimulation*> simulations;

        // Initialize n simulations.
        for(int i_thread=0; i_thread<m_thread_info.n_threads; ++i_thread){
            DWBASimulation *p_dwba_simulation =
                mp_sample->createDWBASimulation();
            if (!p_dwba_simulation) throw NullPointerException(
                "Simulation::runSimulation() -> No dwba simulation");
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
        for(size_t i=0; i<simulations.size(); ++i) {
            addToIntensityMaps(simulations[i]);
            delete simulations[i];
            delete threads[i];
        }
    }
    m_instrument.applyDetectorResolution(&m_intensity_map);
}

void Simulation::runSimulationElement(size_t index)
{
    (void)index;  // to suppress unused-variable warning

    prepareSimulation();
    if( !mp_sample)
        throw NullPointerException(
            "Simulation::runSimulation() -> Error! No sample set.");
    m_intensity_map.setAllTo(0);
    m_polarization_output.setAllTo(Eigen::Matrix2d::Zero());

    DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
    if (!p_dwba_simulation)
        throw NullPointerException("Simulation::runSimulation() -> "
                                   "No dwba simulation");
    p_dwba_simulation->init(*this);
    p_dwba_simulation->run();
    m_intensity_map += p_dwba_simulation->getDWBAIntensity();
    delete p_dwba_simulation;
}

void Simulation::normalize()
{
    if (!m_is_normalized) {
        m_instrument.normalize(&m_intensity_map, &m_polarization_output);
        m_is_normalized = true;
    }
}

//! The ISample object will not be owned by the Simulation object
void Simulation::setSample(const ISample& sample)
{
    delete mp_sample;
    mp_sample = sample.clone();
}

void Simulation::setSampleBuilder(const ISampleBuilder *p_sample_builder)
{
    if( !p_sample_builder )
        throw NullPointerException(
            "Simulation::setSampleBuilder() -> "
            "Error! Attempt to set null sample builder.");
    mp_sample_builder = p_sample_builder;
    delete mp_sample;
    mp_sample = 0;
}

void Simulation::setInstrument(const Instrument& instrument)
{
    m_instrument = instrument;
    updateIntensityMapAxes();
}

void Simulation::setBeamParameters(double lambda, double alpha_i, double phi_i)
{
    m_instrument.setBeamParameters(lambda, alpha_i, phi_i);
}

void Simulation::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
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

    if (mp_sample_builder) {
       // add parameters of the sample builder
        mp_sample_builder->addParametersToExternalPool(
            new_path, external_pool, -1);
    } else if (mp_sample) {
        // add parameters of directly the sample
        mp_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Simulation::smearIntensityFromZAxisTilting()
{
    size_t nbr_zetas = 5;
    double zeta_sigma = 45*Units::degree;
    std::vector<double> zetas;
    std::vector<double> probs;
    createZetaAndProbVectors(zetas, probs, nbr_zetas, zeta_sigma);

    OutputData<double> *p_clone = m_intensity_map.clone();
    m_intensity_map.setAllTo(0.);
    OutputData<double>::const_iterator it_clone = p_clone->begin();
    while (it_clone != p_clone->end()) {
        double old_phi = p_clone->getValueOfAxis(
            "phi_f", it_clone.getIndex());
        double old_alpha = p_clone->getValueOfAxis(
            "alpha_f", it_clone.getIndex());
        for (size_t zeta_index=0; zeta_index<zetas.size(); ++zeta_index) {
            double newphi =
                old_phi + deltaPhi(old_alpha, old_phi, zetas[zeta_index]);
            double newalpha =
                old_alpha + deltaAlpha(old_alpha, zetas[zeta_index]);
            double prob = probs[zeta_index];
            addToIntensityMap(newalpha, newphi, prob*(*it_clone++));
        }
    }
}

void Simulation::init_parameters()
{
}

void Simulation::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    m_polarization_output.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
        m_polarization_output.addAxis(m_instrument.getDetectorAxis(dim));
    }
    m_intensity_map.setAllTo(0.);
    m_polarization_output.setAllTo(Eigen::Matrix2d::Zero());
}

void Simulation::updateSample()
{
    if (mp_sample_builder) {
        ISample *p_new_sample = mp_sample_builder->buildSample();
        std::string builder_type = typeid(*mp_sample_builder).name();
        if( builder_type.find("ISampleBuilder_wrapper") != std::string::npos ) {
            msglog(MSG::INFO) << "Simulation::updateSample() -> "
                "OMG, some body has called me from python, what an idea... ";
            // p_new_sample belongs to python, don't delete it
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

    m_polarization_output.clear();
    m_polarization_output.copyShapeFrom(output_data);
    m_polarization_output.setAllTo(Eigen::Matrix2d::Zero());
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
    IResolutionFunction2D *p_resolution_function)
{
    m_instrument.setDetectorResolutionFunction(p_resolution_function);
}
void Simulation::setDetectorResolutionFunction(
    const IResolutionFunction2D &p_resolution_function)
{
    m_instrument.setDetectorResolutionFunction(p_resolution_function);
}

double Simulation::deltaAlpha(double alpha, double zeta) const
{
    return std::sin(alpha)*(1.0/std::cos(zeta)-1);
}

double Simulation::deltaPhi(double alpha, double phi, double zeta) const
{
    double qy2 = std::sin(phi)*std::sin(phi) -
        std::sin(alpha)*std::sin(alpha)*std::tan(zeta)*std::tan(zeta);
    return std::sqrt(qy2) - std::sin(phi);
}

void Simulation::createZetaAndProbVectors(
    std::vector<double>& zetas,
    std::vector<double>& probs, size_t nbr_zetas, double zeta_sigma) const
{
    double zeta_step;
    if (nbr_zetas<2) {
        zeta_step = 0;
    } else {
        zeta_step = 2*zeta_sigma/(nbr_zetas-1);
    }
    double zeta_start = -zeta_sigma;
    double prob_total = 0;
    for (size_t i=0; i<nbr_zetas; ++i) {
        double zeta = zeta_start + i*zeta_step;
        double prob = MathFunctions::Gaussian(zeta, 0., zeta_sigma);
        zetas.push_back(zeta);
        probs.push_back(prob);
        prob_total += prob;
    }
    assert(prob_total != 0);
    for (size_t i=0; i<nbr_zetas; ++i) {
        probs[i] /= prob_total;
    }
}

void Simulation::addToIntensityMaps(DWBASimulation* p_dwba_simulation)
{
    m_intensity_map += p_dwba_simulation->getDWBAIntensity();
    if (p_dwba_simulation->hasPolarizedOutputData()) {
        m_polarization_output += p_dwba_simulation->getPolarizedDWBAIntensity();
    }
}

void Simulation::addToIntensityMap(double alpha, double phi, double value)
{
    const IAxis *p_alpha_axis = m_intensity_map.getAxis("alpha_f");
    const IAxis *p_phi_axis = m_intensity_map.getAxis("phi_f");
    std::vector<int> coordinates;
    coordinates.push_back((int)p_alpha_axis->findClosestIndex(alpha));
    coordinates.push_back((int)p_phi_axis->findClosestIndex(phi));
    m_intensity_map[m_intensity_map.toIndex(coordinates)] += value;
}



