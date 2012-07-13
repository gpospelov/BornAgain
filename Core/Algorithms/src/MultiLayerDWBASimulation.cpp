#include "MultiLayerDWBASimulation.h"
#include "OpticalFresnel.h"
#include "DoubleToComplexInterpolatingFunction.h"

MultiLayerDWBASimulation::MultiLayerDWBASimulation(
        const MultiLayer* p_multi_layer)
{
    mp_multi_layer = p_multi_layer->clone();
}

MultiLayerDWBASimulation::~MultiLayerDWBASimulation()
{
    delete mp_multi_layer;
    for(std::map<size_t, LayerDWBASimulation*>::iterator it=m_layer_dwba_simulation_map.begin(); it!=m_layer_dwba_simulation_map.end(); it++)
    {
        delete (*it).second;
    }
}

void MultiLayerDWBASimulation::init(const Experiment& experiment)
{
    DWBASimulation::init(experiment);
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        LayerDWBASimulation *p_layer_dwba_sim = mp_multi_layer->getLayer(i)->createDWBASimulation();
        if (p_layer_dwba_sim) {
            m_layer_dwba_simulation_map[i] = p_layer_dwba_sim;
            p_layer_dwba_sim->init(experiment);
        }
    }
}

void MultiLayerDWBASimulation::run()
{
    OpticalFresnel fresnelCalculator;

    m_dwba_intensity.setAllTo(0.0);
    NamedVector<double> *p_alpha_axis = dynamic_cast<NamedVector<double> *>(m_dwba_intensity.getAxis("alpha_f"));
    double lambda = 2.0*M_PI/m_ki.mag();
    std::map<double, OpticalFresnel::MultiLayerCoeff_t> fresnel_coeff_map;
    for (size_t i=0; i<p_alpha_axis->getSize(); ++i) {
        double angle = (*p_alpha_axis)[i];
        kvector_t kvec = kvector_t::LambdaAlphaPhi(lambda, -angle, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        fresnelCalculator.execute(*mp_multi_layer, kvec, coeffs);
        fresnel_coeff_map[angle] = coeffs;
    }
    // Also add input angle
    OpticalFresnel::MultiLayerCoeff_t coeffs;
    fresnelCalculator.execute(*mp_multi_layer, m_ki, coeffs);
    fresnel_coeff_map[-m_alpha_i] = coeffs;
    // Run through layers for DWBA corrections
    for (std::map<size_t, LayerDWBASimulation*>::const_iterator it=m_layer_dwba_simulation_map.begin();
            it!=m_layer_dwba_simulation_map.end(); ++it) {
        size_t i = (*it).first;
        LayerDWBASimulation *p_layer_dwba_sim = (*it).second;
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
        p_layer_dwba_sim->setKzTAndRFunctions(kz_function, T_function, R_function);
        p_layer_dwba_sim->run();
        // TODO: this must be a += statement when this is implemented in OutputData<double>
        //m_dwba_intensity += (*p_layer_dwba_sim->getDWBAIntensity());
        m_dwba_intensity += p_layer_dwba_sim->getDWBAIntensity();
    }
}
