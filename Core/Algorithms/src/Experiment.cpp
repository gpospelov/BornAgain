#include "Experiment.h"

#include "ExperimentConstants.h"
#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "DWBASimulation.h"

#include <boost/thread.hpp>


Experiment::Experiment()
: IParameterized("Experiment")
, mp_sample(0)
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(0)
{
    init_parameters();
}

Experiment::Experiment(const Experiment &other)
: IParameterized(other), ICloneable()
, mp_sample(0)
, mp_sample_builder(other.mp_sample_builder)
, m_instrument(other.m_instrument)
, m_intensity_map()
, m_is_normalized(other.m_is_normalized)
, mp_options(other.mp_options)
, m_sim_params(other.m_sim_params)
{
    if(other.mp_sample) mp_sample = other.mp_sample->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);
    init_parameters();
}

Experiment::Experiment(const ProgramOptions *p_options)
: IParameterized("Experiment")
, mp_sample(0)
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Experiment::Experiment(const ISample &p_sample, const ProgramOptions *p_options)
: IParameterized("Experiment")
, mp_sample(p_sample.clone())
, mp_sample_builder(0)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}

Experiment::Experiment(const ISampleBuilder* p_sample_builder, const ProgramOptions *p_options)
: IParameterized("Experiment")
, mp_sample(0)
, mp_sample_builder(p_sample_builder)
, m_instrument()
, m_intensity_map()
, m_is_normalized(false)
, mp_options(p_options)
{
    init_parameters();
}


/* ************************************************************************* */
// clone method
/* ************************************************************************* */
Experiment *Experiment::clone() const
{
    return new Experiment(*this);
}

void Experiment::prepareSimulation()
{
    m_is_normalized = false;
    updateSample();
}

/* ************************************************************************* */
// run simulation
/* ************************************************************************* */
void Experiment::runExperiment()
{
    prepareSimulation();
    if( !mp_sample) throw NullPointerException( "Experiment::runExperiment() -> Error! No sample set.");

    // retrieve threading information
    int n_threads_total=0;
    if (mp_options) {
        n_threads_total = (*mp_options)["threads"].as<int>();
    }

    m_intensity_map.setAllTo(0.0);
    if(n_threads_total<0) {
        DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
        if (!p_dwba_simulation) throw NullPointerException("Experiment::runExperiment() -> No dwba simulation");
        p_dwba_simulation->init(*this);
        p_dwba_simulation->run();
        m_intensity_map += p_dwba_simulation->getDWBAIntensity();
        delete p_dwba_simulation;
    } else {
        // if n_threads=0, take optimal number of threads from the hardware
        if(n_threads_total == 0 )  {
            n_threads_total = (int)boost::thread::hardware_concurrency();
            std::cout << "Experiment::runExperiment() -> Info. Number of threads " << n_threads_total << " (taken from hardware concurrency)" << std::endl;
        }else {
            std::cout << "Experiment::runExperiment() -> Info. Number of threads " << n_threads_total << " (hardware concurrency: " << boost::thread::hardware_concurrency() << " )"<< std::endl;
        }
        std::vector<boost::thread *> threads;
        std::vector<DWBASimulation *> simulations;

        // first make sure every thread's objects are properly initialized...
        ThreadInfo thread_info;
        thread_info.n_threads = n_threads_total;
        for(int i_thread=0; i_thread<n_threads_total; ++i_thread){
            DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
            if (!p_dwba_simulation) throw NullPointerException("Experiment::runExperiment() -> No dwba simulation");
            p_dwba_simulation->init(*this);
            thread_info.i_thread = i_thread;
            p_dwba_simulation->setThreadInfo(thread_info);
            simulations.push_back(p_dwba_simulation);
        }
        // ... and then execute the threads
        for (std::vector<DWBASimulation *>::iterator it=simulations.begin(); it!=simulations.end(); ++it) {
            threads.push_back( new boost::thread(boost::bind(&DWBASimulation::run, *it)) );
        }

        // waiting for threads to be complete
        for(size_t i=0; i<threads.size(); ++i) {
            threads[i]->join();
        }

        // saving data
        for(size_t i=0; i<simulations.size(); ++i) {
            m_intensity_map += simulations[i]->getDWBAIntensity();
            delete simulations[i];
            delete threads[i];
        }
    }
    m_instrument.applyDetectorResolution(&m_intensity_map);
}

void Experiment::runExperimentElement(size_t index)
{
    //TODO: use index
    (void)index;
    prepareSimulation();

    if( !mp_sample) throw NullPointerException( "Experiment::runExperiment() -> Error! No sample set.");

    m_intensity_map.setAllTo(0.0);
    DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
    if (!p_dwba_simulation) throw NullPointerException("Experiment::runExperiment() -> No dwba simulation");
    p_dwba_simulation->init(*this);
    p_dwba_simulation->run();
    m_intensity_map += p_dwba_simulation->getDWBAIntensity();
    delete p_dwba_simulation;
}

void Experiment::normalize()
{
    if (!m_is_normalized) {
        m_instrument.normalize(&m_intensity_map);
        m_is_normalized = true;
    }
}


//! The ISample object will not be owned by the Experiment object
void Experiment::setSample(const ISample &p_sample)
{
    delete mp_sample;
    mp_sample = p_sample.clone();
}

void Experiment::setSampleBuilder(const ISampleBuilder *p_sample_builder)
{
    if( !p_sample_builder ) throw NullPointerException("Experiment::setSampleBuilder() -> Error! Attempt to set null sample builder.");
    mp_sample_builder = p_sample_builder;
    delete mp_sample;
    mp_sample = 0;
}

OutputData<double>* Experiment::getOutputDataClone() const
{
	return m_intensity_map.clone();
}

const OutputData<double>* Experiment::getOutputData() const
{
    return &m_intensity_map;
}

void Experiment::setBeamParameters(double lambda, double alpha_i, double phi_i)
{
    m_instrument.setBeamParameters(lambda, alpha_i, phi_i);
}

void Experiment::setBeamIntensity(double intensity)
{
    m_instrument.setBeamIntensity(intensity);
}

std::string Experiment::addParametersToExternalPool(std::string path,
        ParameterPool* external_pool, int copy_number) const
{
    // add own parameters
    std::string  new_path = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the instrument
    m_instrument.addParametersToExternalPool(new_path, external_pool, -1);

    // add parameters of the sample builder
    if (mp_sample_builder) {
        mp_sample_builder->addParametersToExternalPool(new_path, external_pool, -1);
    }
    // add parameters of the sample (only in the case without sample builder)
    else if (mp_sample) {
//        std::string sample_path = new_path + mp_sample->getName();
//        mp_sample->addParametersToExternalPool(sample_path, external_pool, -1);
        mp_sample->addParametersToExternalPool(new_path, external_pool, -1);
    }

    return new_path;
}

void Experiment::smearIntensityFromZAxisTilting()
{
    size_t nbr_zetas = 5;
    double zeta_sigma = 45.0*Units::degree;
    std::vector<double> zetas;
    std::vector<double> probs;
    createZetaAndProbVectors(zetas, probs, nbr_zetas, zeta_sigma);

    OutputData<double> *p_clone = m_intensity_map.clone();
    m_intensity_map.setAllTo(0.0);
    OutputData<double>::const_iterator it_clone = p_clone->begin();
    while (it_clone != p_clone->end()) {
        double old_phi = p_clone->getValueOfAxis(NDetector2d::PHI_AXIS_NAME, it_clone.getIndex());
        double old_alpha = p_clone->getValueOfAxis(NDetector2d::ALPHA_AXIS_NAME, it_clone.getIndex());
        for (size_t zeta_index=0; zeta_index<zetas.size(); ++zeta_index) {
            double newphi = old_phi + deltaPhi(old_alpha, old_phi, zetas[zeta_index]);
            double newalpha = old_alpha + deltaAlpha(old_alpha, zetas[zeta_index]);
            double prob = probs[zeta_index];
            addToIntensityMap(newalpha, newphi, prob*(*it_clone++));
        }
    }
}

void Experiment::init_parameters()
{
}

void Experiment::updateIntensityMapAxes()
{
    m_intensity_map.clear();
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(dim));
    }
    m_intensity_map.setAllTo(0.0);
}

void Experiment::updateSample()
{
    if (mp_sample_builder) {
        ISample *p_new_sample = mp_sample_builder->buildSample();
        std::string builder_type = typeid(*mp_sample_builder).name();
        if( builder_type.find("ISampleBuilder_wrapper") != std::string::npos ) {
            std::cout << "Experiment::updateSample() -> OMG, some body has called me from python, going to collapse in a second... " << std::endl;
            setSample(*p_new_sample); // p_new_sample belongs to python, don't delete it
        } else {
            delete mp_sample;
            mp_sample = p_new_sample;
        }
    }
}

void Experiment::setDetectorParameters(const OutputData<double > &output_data)
{
    m_instrument.matchDetectorParameters(output_data);

    //updateIntensityMapAxes();
    m_intensity_map.clear();
    m_intensity_map.copyFrom(output_data); // to copy mask too
    m_intensity_map.setAllTo(0.0);
}

void Experiment::setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
                                            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style)
{
    m_instrument.setDetectorParameters(n_phi, phi_f_min, phi_f_max, n_alpha, alpha_f_min, alpha_f_max, isgisaxs_style);
    updateIntensityMapAxes();
}

void Experiment::setDetectorParameters(const DetectorParameters &params)
{
    m_instrument.setDetectorParameters(params);
    updateIntensityMapAxes();
}

void Experiment::setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function)
{
    m_instrument.setDetectorResolutionFunction(p_resolution_function);
}

double Experiment::deltaAlpha(double alpha, double zeta) const
{
    return std::sin(alpha)*(1.0/std::cos(zeta)-1.0);
}

double Experiment::deltaPhi(double alpha, double phi, double zeta) const
{
    double qy2 = std::sin(phi)*std::sin(phi) - std::sin(alpha)*std::sin(alpha)*std::tan(zeta)*std::tan(zeta);
    return std::sqrt(qy2) - std::sin(phi);
}

void Experiment::createZetaAndProbVectors(std::vector<double>& zetas,
        std::vector<double>& probs, size_t nbr_zetas, double zeta_sigma) const
{
    double zeta_step;
    if (nbr_zetas<2) {
        zeta_step = 0.0;
    }
    else {
        zeta_step = 2.0*zeta_sigma/(nbr_zetas-1);
    }
    double zeta_start = -1.0*zeta_sigma;
    double prob_total = 0.0;
    for (size_t i=0; i<nbr_zetas; ++i) {
        double zeta = zeta_start + i*zeta_step;
        double prob = MathFunctions::Gaussian(zeta, 0.0, zeta_sigma);
        zetas.push_back(zeta);
        probs.push_back(prob);
        prob_total += prob;
    }
    assert(prob_total != 0);
    for (size_t i=0; i<nbr_zetas; ++i) {
        probs[i] /= prob_total;
    }
}

void Experiment::addToIntensityMap(double alpha, double phi, double value)
{
    const IAxis *p_alpha_axis = m_intensity_map.getAxis(NDetector2d::ALPHA_AXIS_NAME);
    const IAxis *p_phi_axis = m_intensity_map.getAxis(NDetector2d::PHI_AXIS_NAME);
    std::vector<int> coordinates;
    coordinates.push_back((int)p_alpha_axis->findClosestIndex(alpha));
    coordinates.push_back((int)p_phi_axis->findClosestIndex(phi));
    m_intensity_map[m_intensity_map.toIndex(coordinates)] += value;
}
