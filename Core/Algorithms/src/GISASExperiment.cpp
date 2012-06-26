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
    // TODO: This code should be moved to a more appropriate place
    // Ideally, here, one creates an ISimulation by calling a builder
    // BTW: the dynamic_cast to MultiLayer shows why this code needs refactoring
    m_intensity_map.setAllTo(0.0);
    MultiLayer *p_multi_layer = dynamic_cast<MultiLayer*>(mp_sample);
    if(p_multi_layer==0) {
        return;
    }
    NamedVector<double> alpha_axis = m_detector.getAxis(1);
    double lambda = 2.0*M_PI/getBeam().getCentralK().mag();
    std::map<double, OpticalFresnel::MultiLayerCoeff_t> fresnel_coeff_map;
    for (size_t i=0; i<alpha_axis.getSize(); ++i) {
        double angle = alpha_axis[i];
        kvector_t kvec = kvector_t::LambdaAlphaPhi(lambda, -angle, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        OpticalFresnel::execute(*p_multi_layer, kvec, coeffs);
        fresnel_coeff_map[angle] = coeffs;
    }
    // Also add input angle
    kvector_t kvec = m_beam.getCentralK();
    double angle = -std::asin(kvec.z()/kvec.mag());
    OpticalFresnel::MultiLayerCoeff_t coeffs;
    OpticalFresnel::execute(*p_multi_layer, kvec, coeffs);
    fresnel_coeff_map[angle] = coeffs;
    // Run through layers for DWBA corrections
    for (size_t i=0; i<p_multi_layer->getNumberOfLayers(); ++i) {
        Layer *p_l = p_multi_layer->getLayer(i)->clone();
        if (p_l->containsDWBATerms()) {
            // Construct kz, T and R functions for use inside layer i
            std::map<double, complex_t> kz_map;
            std::map<double, complex_t> T_map;
            std::map<double, complex_t> R_map;
            for (std::map<double, OpticalFresnel::MultiLayerCoeff_t>::const_iterator it=fresnel_coeff_map.begin();
                    it!=fresnel_coeff_map.end(); ++it) {
                double angle = (*it).first;
                complex_t kz = (*it).second[i].kz;
                complex_t T = (*it).second[i].T;
                complex_t R = (*it).second[i].R;
                kz_map[angle] = kz;
                T_map[angle] = T;
                R_map[angle] = R;
            }
            DoubleToComplexInterpolatingFunction kz_function(kz_map);
            DoubleToComplexInterpolatingFunction T_function(T_map);
            DoubleToComplexInterpolatingFunction R_function(R_map);
            LayerDWBASimulation *p_dwba_sim = p_l->getDWBASimulation();
            p_dwba_sim->setKzTAndRFunctions(kz_function, T_function, R_function);
            p_dwba_sim->init(*this);
            p_dwba_sim->run();
            // TODO: this must be a += statement when this is implemented in OutputData<double>
            m_intensity_map += (*p_dwba_sim->getDWBAIntensity());
        }
    }
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
    double start_sin = std::sin(start);
    double end_sin = std::sin(end);
    double step = (end_sin-start_sin)/(size-1);
    for(size_t i=0; i<size; ++i) {
        p_axis->push_back(std::asin(start_sin + step*i));
    }
    return;
}
