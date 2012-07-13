#include "GISASExperiment.h"
#include "Units.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "DoubleToComplexInterpolatingFunction.h"

GISASExperiment::GISASExperiment()
{
    m_beam.setCentralK(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree); ///< Set default beam parameters
    setDetectorParameters(0.0*Units::degree, 2.0*Units::degree, 100,
            0.0*Units::degree, 2.0*Units::degree, 100);
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
}

void GISASExperiment::setDetectorParameters(double phi_f_min, double phi_f_max,
        size_t n_phi, double alpha_f_min, double alpha_f_max, size_t n_alpha,
        bool isgisaxs_style)
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
