#include "GISASExperiment.h"

GISASExperiment::GISASExperiment()
{
    m_beam.setCentralK(1.0, 2.0, 0.0); ///< Set default beam parameters
    setDetectorParameters(0.0, 2.0, 100, 0.0, 2.0, 100);
}

void GISASExperiment::runSimulation()
{
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

void GISASExperiment::initializeAnglesIsgisaxs(NamedVector<double> *p_axis, double start, double end, size_t size) {
    double start_sin = std::sin(start*M_PI/180);
    double end_sin = std::sin(end*M_PI/180);
    double step = (end_sin-start_sin)/(size-1);
    for(size_t i=0; i<size; ++i) {
        p_axis->push_back(std::asin(start_sin + step*i)*180/M_PI);
    }
    return;
}
