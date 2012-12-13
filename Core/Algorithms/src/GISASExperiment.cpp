#include "GISASExperiment.h"
#include "Units.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "DoubleToComplexInterpolatingFunction.h"
#include "MathFunctions.h"
#include "ProgramOptions.h"
#include "ConvolutionDetectorResolution.h"

#include <boost/thread.hpp>


/* ************************************************************************* */
// c-tors
/* ************************************************************************* */
GISASExperiment::GISASExperiment()
{
    setName("GISASExperiment");
    m_beam.setCentralK(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree); ///< Set default beam parameters
    setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree);
}

GISASExperiment::GISASExperiment(ProgramOptions *p_options)
: Experiment(p_options)
{
    setName("GISASExperiment");
    m_beam.setCentralK(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree); ///< Set default beam parameters
    setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree);
}

GISASExperiment::GISASExperiment(const GISASExperiment &other) : Experiment(other)
{

}


/* ************************************************************************* */
// clone method
/* ************************************************************************* */
GISASExperiment *GISASExperiment::clone() const
{
    return new GISASExperiment(*this);
}


/* ************************************************************************* */
// run simulation
/* ************************************************************************* */
void GISASExperiment::runSimulation()
{
    Experiment::runSimulation();
    if( !mp_sample) throw NullPointerException( "GISASExperiment::runSimulation() -> Error! No sample set.");

    int n_threads_total=0;
    if (mp_options) {
        n_threads_total = (*mp_options)["threads"].as<int>();
        //std::cout << "GISASExperiment::runSimulation() -> Info. Number of threads defined in program options " << n_threads_total << std::endl;
    }

    m_intensity_map.setAllTo(0.0);
    if(n_threads_total<0) {
        DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
        if (!p_dwba_simulation) throw NullPointerException("GISASExperiment::runSimulation() -> No dwba simulation");
        p_dwba_simulation->init(*this);
        p_dwba_simulation->run();
        m_intensity_map += p_dwba_simulation->getDWBAIntensity();
        delete p_dwba_simulation;
    } else {
        // if n_threads=0, take optimal number of threads from the hardware
        if(n_threads_total == 0 )  {
            n_threads_total = boost::thread::hardware_concurrency();
            std::cout << "GISASExperiment::runSimulation() -> Info. Number of threads " << n_threads_total << " (taken from hardware concurrency)" << std::endl;
        }else {
            std::cout << "GISASExperiment::runSimulation() -> Info. Number of threads " << n_threads_total << " (hardware concurrency: " << boost::thread::hardware_concurrency() << " )"<< std::endl;
        }
        std::vector<boost::thread *> threads;
        std::vector<DWBASimulation *> simulations;

        // first make sure every thread's objects are properly initialized...
        ThreadInfo thread_info;
        thread_info.n_threads = n_threads_total;
        for(int i_thread=0; i_thread<n_threads_total; ++i_thread){
            DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
            if (!p_dwba_simulation) throw NullPointerException("GISASExperiment::runSimulation() -> No dwba simulation");
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
    m_detector.applyDetectorResolution(&m_intensity_map);
}



void GISASExperiment::runSimulationElement(size_t index)
{
    (void)index;
    Experiment::runSimulation();
    if( !mp_sample) throw NullPointerException( "GISASExperiment::runSimulation() -> Error! No sample set.");

    m_intensity_map.setAllTo(0.0);
    DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
    if (!p_dwba_simulation) throw NullPointerException("GISASExperiment::runSimulation() -> No dwba simulation");
    p_dwba_simulation->init(*this);
    p_dwba_simulation->run();
    m_intensity_map += p_dwba_simulation->getDWBAIntensity();
    delete p_dwba_simulation;
}



void GISASExperiment::normalize()
{
    // This normalization assumes that the intensity map contains total differential scattering cross sections
    // (so not the cross section per scattering particle as is usual)
    if (!m_is_normalized) {
        double incident_intensity = m_beam.getIntensity(); // Actually, this is the total number of neutrons hitting the sample
        double sin_alpha_i = std::abs(m_beam.getCentralK().cosTheta());
        for (OutputData<double>::iterator it = m_intensity_map.begin(); it != m_intensity_map.end(); ++it) {
            double factor = incident_intensity*getSolidAngle(it.getIndex())/sin_alpha_i;
            (*it) *= factor;
        }
        m_is_normalized = true;
    }
}

// TODO : refactor to take detector parameter object
void GISASExperiment::setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
                                            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style)
{
    const std::string s_phi_f("phi_f");
    const std::string s_alpha_f("alpha_f");

    m_detector.clear();
    AxisDouble phi_axis(s_phi_f);
    AxisDouble alpha_axis(s_alpha_f);
    if (isgisaxs_style) {
        initializeAnglesIsgisaxs(&phi_axis, phi_f_min, phi_f_max, n_phi);
        initializeAnglesIsgisaxs(&alpha_axis, alpha_f_min, alpha_f_max, n_alpha);
    }
    else {
        phi_axis.initElements(n_phi, phi_f_min, phi_f_max);
        alpha_axis.initElements(n_alpha, alpha_f_min, alpha_f_max);
    }
    m_detector.addAxis(phi_axis);
    m_detector.addAxis(alpha_axis);
    updateIntensityMapAxes();
}


void GISASExperiment::setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function)
{
    m_detector.setDetectorResolution( new ConvolutionDetectorResolution(p_resolution_function) );
}

void GISASExperiment::smearIntensityFromZAxisTilting()
{
    const std::string s_phi_f("phi_f");
    const std::string s_alpha_f("alpha_f");

    size_t nbr_zetas = 5;
    double zeta_sigma = 45.0*Units::degree;
    std::vector<double> zetas;
    std::vector<double> probs;
    createZetaAndProbVectors(zetas, probs, nbr_zetas, zeta_sigma);

    OutputData<double> *p_clone = m_intensity_map.clone();
    m_intensity_map.setAllTo(0.0);
    OutputData<double>::const_iterator it_clone = p_clone->begin();
    while (it_clone != p_clone->end()) {
        double old_phi = p_clone->getValueOfAxis(s_phi_f, it_clone.getIndex());
        double old_alpha = p_clone->getValueOfAxis(s_alpha_f, it_clone.getIndex());
        for (size_t zeta_index=0; zeta_index<zetas.size(); ++zeta_index) {
            double newphi = old_phi + deltaPhi(old_alpha, old_phi, zetas[zeta_index]);
            double newalpha = old_alpha + deltaAlpha(old_alpha, zetas[zeta_index]);
            double prob = probs[zeta_index];
            addToIntensityMap(newalpha, newphi, prob*(*it_clone++));
        }
    }
}

void GISASExperiment::init_parameters()
{
}

void GISASExperiment::initializeAnglesIsgisaxs(AxisDouble *p_axis, double start, double end, size_t size) {
    double start_sin = std::sin(start);
    double end_sin = std::sin(end);
    double step = (end_sin-start_sin)/(size-1);
    for(size_t i=0; i<size; ++i) {
        p_axis->push_back(std::asin(start_sin + step*i));
    }
    return;
}


double GISASExperiment::getSolidAngle(size_t index) const
{
    const std::string s_phi_f("phi_f");
    const std::string s_alpha_f("alpha_f");

    const AxisDouble *p_alpha_axis = m_intensity_map.getAxis(s_alpha_f);
    const AxisDouble *p_phi_axis = m_intensity_map.getAxis(s_phi_f);
    size_t alpha_index = m_intensity_map.getIndexOfAxis(s_alpha_f, index);
    size_t alpha_size = p_alpha_axis->getSize();
    size_t phi_index = m_intensity_map.getIndexOfAxis(s_phi_f, index);
    size_t phi_size = p_phi_axis->getSize();
    if (alpha_size<2 && phi_size<2) {
        // Cannot determine detector cell size!
        throw LogicErrorException("GISASExperiment::getSolidAngle() -> Error! Can't determine size of detector cell.");
    }
    double dalpha(0), dphi(0);

    double alpha_f = m_intensity_map.getValueOfAxis(s_alpha_f, index);
    double cos_alpha_f = std::cos(alpha_f);

    if(alpha_size>1) {
        if (alpha_index==0) {
            dalpha = p_alpha_axis->operator[](1) - p_alpha_axis->operator[](0);
        }
        else if (alpha_index==alpha_size-1) {
            dalpha = p_alpha_axis->operator[](alpha_size-1) - p_alpha_axis->operator[](alpha_size-2);
        }
        else {
            dalpha = (p_alpha_axis->operator[](alpha_index+1) - p_alpha_axis->operator[](alpha_index-1))/2.0;
        }
        dalpha = std::abs(dalpha);
    } else {
        //std::cout << "GISASExperiment::getSolidAngle() -> Warning! Only one bin on alpha_f axis, size of the bin will be taken from phi_f axis" << std::endl;
    }
    if(phi_size > 1) {
        if (phi_index==0) {
            dphi = p_phi_axis->operator[](1) - p_phi_axis->operator[](0);
        }
        else if (phi_index==phi_size-1) {
            dphi = p_phi_axis->operator[](phi_size-1) - p_phi_axis->operator[](phi_size-2);
        }
        else {
            dphi = (p_phi_axis->operator[](phi_index+1) - p_phi_axis->operator[](phi_index-1))/2.0;
        }
        dphi = std::abs(dphi);
    } else {
        //std::cout << "GISASExperiment::getSolidAngle() -> Warning! Only one bin on phi_f axis, size of the bin will be taken from alpha_f axis" << std::endl;
    }
    if(!dalpha || !dphi) {
        std::cout << "GISASExperiment::getSolidAngle() -> Warning! Not defined normalization" << std::endl;
        return 1;
    } else {
        return cos_alpha_f*dalpha*dphi;
    }
}


double GISASExperiment::deltaAlpha(double alpha, double zeta) const
{
    return std::sin(alpha)*(1.0/std::cos(zeta)-1.0);
}

double GISASExperiment::deltaPhi(double alpha, double phi, double zeta)
{
    double qy2 = std::sin(phi)*std::sin(phi) - std::sin(alpha)*std::sin(alpha)*std::tan(zeta)*std::tan(zeta);
    return std::sqrt(qy2) - std::sin(phi);
}

void GISASExperiment::createZetaAndProbVectors(std::vector<double>& zetas,
        std::vector<double>& probs, size_t nbr_zetas, double zeta_sigma)
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
    for (size_t i=0; i<nbr_zetas; ++i) {
        probs[i] /= prob_total;
    }
}

void GISASExperiment::addToIntensityMap(double alpha, double phi, double value)
{
    const AxisDouble *p_alpha_axis = m_intensity_map.getAxis("alpha_f");
    const AxisDouble *p_phi_axis = m_intensity_map.getAxis("phi_f");
    std::vector<int> coordinates;
    coordinates.push_back(findClosestIndex(p_alpha_axis, alpha));
    coordinates.push_back(findClosestIndex(p_phi_axis, phi));
    m_intensity_map[m_intensity_map.toIndex(coordinates)] += value;
}

int GISASExperiment::findClosestIndex(const AxisDouble *p_axis, double value)
{
    int result = 0;
    double smallest_diff = std::abs(value-(*p_axis)[0]);
    for (size_t i=1; i<p_axis->getSize(); ++i) {
        double new_diff = std::abs(value-(*p_axis)[i]);
        if (new_diff > smallest_diff) break;
        result = (int)i;
        smallest_diff = new_diff;
    }
    return result;
}
