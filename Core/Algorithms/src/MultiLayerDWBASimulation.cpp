#include "MultiLayerDWBASimulation.h"
#include "OpticalFresnel.h"
#include "DoubleToComplexInterpolatingFunction.h"
#include "MultiLayerRoughnessDWBASimulation.h"


MultiLayerDWBASimulation::MultiLayerDWBASimulation(
        const MultiLayer* p_multi_layer) : m_roughness_dwba_simulation(0)
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
    delete m_roughness_dwba_simulation;
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
    // scattering from rough surfaces in DWBA
    for (size_t i=0; i<mp_multi_layer->getNumberOfInterfaces(); ++i) {
        if(mp_multi_layer->getLayerInterface(i)->getRoughness() ) {
            m_roughness_dwba_simulation = new MultiLayerRoughnessDWBASimulation(mp_multi_layer);
            m_roughness_dwba_simulation->init(experiment);
            break;
        }
    }
}

void MultiLayerDWBASimulation::run()
{
    OpticalFresnel fresnelCalculator;

    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());

    m_dwba_intensity.setAllTo(0.0);
    const NamedVector<double> *p_alpha_axis = dynamic_cast<const NamedVector<double> *>(m_dwba_intensity.getAxis("alpha_f"));
    double lambda = 2.0*M_PI/m_ki_real.mag();
    std::map<double, OpticalFresnel::MultiLayerCoeff_t> fresnel_coeff_map;
    for (size_t i=0; i<p_alpha_axis->getSize(); ++i) {
        double angle = (*p_alpha_axis)[i];
        kvector_t kvec;
        kvec.setLambdaAlphaPhi(lambda, -angle, 0.0);
        OpticalFresnel::MultiLayerCoeff_t coeffs;
        fresnelCalculator.execute(*mp_multi_layer, kvec, coeffs);
        fresnel_coeff_map[angle] = coeffs;
    }
    // Also add input angle
    OpticalFresnel::MultiLayerCoeff_t coeffs;
    fresnelCalculator.execute(*mp_multi_layer, m_ki_real, coeffs);
    fresnel_coeff_map[-m_alpha_i] = coeffs;

    // run through layers and construct T,R functions
    for(size_t i_layer=0; i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        std::map<double, complex_t> kz_map;
        std::map<double, complex_t> T_map;
        std::map<double, complex_t> R_map;
        for (std::map<double, OpticalFresnel::MultiLayerCoeff_t>::const_iterator it=fresnel_coeff_map.begin();
                it!=fresnel_coeff_map.end(); ++it) {
            double angle = (*it).first;
            complex_t kz = (*it).second[i_layer].kz;
            complex_t T = (*it).second[i_layer].T;
            complex_t R = (*it).second[i_layer].R;
            kz_map[angle] = kz;
            T_map[angle] = T;
            R_map[angle] = R;
        }
        DoubleToComplexInterpolatingFunction kz_function(kz_map);
        DoubleToComplexInterpolatingFunction T_function(T_map);
        DoubleToComplexInterpolatingFunction R_function(R_map);

        // layer DWBA simulation
        std::map<size_t, LayerDWBASimulation*>::const_iterator pos = m_layer_dwba_simulation_map.find(i_layer);
        if(pos != m_layer_dwba_simulation_map.end() ) {
            LayerDWBASimulation *p_layer_dwba_sim = pos->second;
            p_layer_dwba_sim->setKzTAndRFunctions(kz_function, T_function, R_function);
            p_layer_dwba_sim->run();
            m_dwba_intensity += p_layer_dwba_sim->getDWBAIntensity();
        }

        // layer roughness DWBA
        if(m_roughness_dwba_simulation) {
            m_roughness_dwba_simulation->setTAndRFunctions(i_layer, T_function, R_function);
        }

    } // i_layer

    if(m_roughness_dwba_simulation) {
        m_roughness_dwba_simulation->run();
        m_dwba_intensity += m_roughness_dwba_simulation->getDWBAIntensity();
    }

}


