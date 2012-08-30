#include "GISASExperiment.h"
#include "Units.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "DoubleToComplexInterpolatingFunction.h"

GISASExperiment::GISASExperiment()
{
    m_beam.setCentralK(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree); ///< Set default beam parameters
    setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
            100, 0.0*Units::degree, 2.0*Units::degree);
}

void GISASExperiment::runSimulation()
{
    m_intensity_map.setAllTo(0.0);
    DWBASimulation *p_dwba_simulation = mp_sample->createDWBASimulation();
    if (p_dwba_simulation) {
        p_dwba_simulation->init(*this);
        p_dwba_simulation->run();
        //m_intensity_map += (*p_dwba_simulation->getDWBAIntensity());
        m_intensity_map += p_dwba_simulation->getDWBAIntensity();
    }
    m_detector.applyDetectorResolution(&m_intensity_map);
    delete p_dwba_simulation;
    Experiment::runSimulation();
}


void GISASExperiment::normalize()
{
    // This normalization assumes that the intensity map contains total differential scattering cross sections
    // (so not the cross section per scattering particle as is usual)
    if (!m_is_normalized) {
        double incident_intensity = m_beam.getIntensity(); // Actually, this is the total number of neutrons hitting the sample
        double sin_alpha_i = std::abs(m_beam.getCentralK().cosTheta().real());
        m_intensity_map.resetIndex();
        while (m_intensity_map.hasNext()) {
            double old_value = m_intensity_map.currentValue();
            double factor = incident_intensity*getCurrentSolidAngle()/sin_alpha_i;
            m_intensity_map.next() = factor*old_value;
        }
        m_is_normalized = true;
    }
}

void GISASExperiment::setDetectorParameters(size_t n_phi, double phi_f_min, double phi_f_max,
                                            size_t n_alpha, double alpha_f_min, double alpha_f_max, bool isgisaxs_style)
{
    m_detector.clear();
    NamedVector<double> phi_axis("phi_f");
    NamedVector<double> alpha_axis("alpha_f");
    if (isgisaxs_style) {
        initializeAnglesIsgisaxs(&phi_axis, phi_f_min, phi_f_max, n_phi);
        initializeAnglesIsgisaxs(&alpha_axis, alpha_f_min, alpha_f_max, n_alpha);
    }
    else {
        phi_axis.initElements(phi_f_min, phi_f_max, n_phi);
        alpha_axis.initElements(alpha_f_min, alpha_f_max, n_alpha);
    }
    m_detector.addAxis(phi_axis);
    m_detector.addAxis(alpha_axis);
    updateIntensityMapAxes();
}

void GISASExperiment::setDetectorResolutionFunction(
        ConvolutionDetectorResolution::cumulative_DF_2d resolution_function)
{
    m_detector.setDetectorResolution(new ConvolutionDetectorResolution(resolution_function));
}

void GISASExperiment::initializeAnglesIsgisaxs(NamedVector<double> *p_axis, double start, double end, size_t size) {
    double start_sin = std::sin(start);
    double end_sin = std::sin(end);
    double step = (end_sin-start_sin)/(size-1);
    for(size_t i=0; i<size; ++i) {
        p_axis->push_back(std::asin(start_sin + step*i));
    }
    return;
}

double GISASExperiment::getCurrentSolidAngle() const
{
    const NamedVector<double> *p_alpha_axis = dynamic_cast<const NamedVector<double>* >(m_intensity_map.getAxis("alpha_f"));
    const NamedVector<double> *p_phi_axis = dynamic_cast<const NamedVector<double>* >(m_intensity_map.getAxis("phi_f"));
    size_t alpha_index = m_intensity_map.getCurrentIndexOfAxis("alpha_f");
    size_t alpha_size = p_alpha_axis->getSize();
    size_t phi_index = m_intensity_map.getCurrentIndexOfAxis("phi_f");
    size_t phi_size = p_phi_axis->getSize();
    if (alpha_size<2 || phi_size<2) {
        // Cannot determine detector cell size!
        return 0.0;
    }
    double alpha_f = m_intensity_map.getCurrentValueOfAxis<double>("alpha_f");
    double cos_alpha_f = std::cos(alpha_f);
    double dalpha, dphi;
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
    return cos_alpha_f*dalpha*dphi;
}
