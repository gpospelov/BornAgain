// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/MultiLayerDWBASimulation.cpp
//! @brief     Implements class MultiLayerDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerDWBASimulation.h"
//#include "OpticalFresnel.h"
#include "SpecularMatrix.h"
#include "MultiLayer.h"
#include "DoubleToComplexInterpolatingFunction.h"
#include "MultiLayerRoughnessDWBASimulation.h"
#include "DoubleToComplexMap.h"
#include "MessageService.h"

MultiLayerDWBASimulation::MultiLayerDWBASimulation(
        const MultiLayer* p_multi_layer)
  : mp_roughness_dwba_simulation(0)
{
    mp_multi_layer = p_multi_layer->clone();
}

MultiLayerDWBASimulation::~MultiLayerDWBASimulation()
{
    delete mp_multi_layer;
    for(std::map<size_t, LayerDWBASimulation*>::iterator it =
            m_layer_dwba_simulation_map.begin();
        it!=m_layer_dwba_simulation_map.end(); ++it)
    {
        delete (*it).second;
    }
    delete mp_roughness_dwba_simulation;
}

void MultiLayerDWBASimulation::init(const Simulation& simulation)
{
    msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::init()";
    DWBASimulation::init(simulation);
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        LayerDWBASimulation *p_layer_dwba_sim =
            mp_multi_layer->getLayer(i)->createDWBASimulation();
        if (p_layer_dwba_sim) {
            m_layer_dwba_simulation_map[i] = p_layer_dwba_sim;
            p_layer_dwba_sim->init(simulation);
        }
    }
    // scattering from rough surfaces in DWBA
    for (size_t i=0; i<mp_multi_layer->getNumberOfInterfaces(); ++i) {
        if(mp_multi_layer->getLayerInterface(i)->getRoughness() ) {
            mp_roughness_dwba_simulation =
                new MultiLayerRoughnessDWBASimulation(mp_multi_layer);
            mp_roughness_dwba_simulation->init(simulation);
            break;
        }
    }
}

void MultiLayerDWBASimulation::setThreadInfo(const ThreadInfo& thread_info)
{
    DWBASimulation::setThreadInfo(thread_info);
    for (std::map<size_t, LayerDWBASimulation*>::iterator it =
             m_layer_dwba_simulation_map.begin();
         it != m_layer_dwba_simulation_map.end(); ++it) {
        it->second->setThreadInfo(thread_info);
    }
    if (mp_roughness_dwba_simulation) {
        mp_roughness_dwba_simulation->setThreadInfo(thread_info);
    }
}

void MultiLayerDWBASimulation::run()
{
    msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> Running thread "
                       << m_thread_info.current_thread;
    SpecularMatrix specularCalculator;

    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());

    m_dwba_intensity.setAllTo(0.0);
    double lambda = 2*M_PI/m_ki_real.mag();

    // collect all alpha angles and calculate Fresnel coefficients
    typedef std::pair<double, SpecularMatrix::MultiLayerCoeff_t>
        doubleFresnelPair_t;
    std::vector<doubleFresnelPair_t> doubleFresnel_buffer;
    std::set<double> alpha_set = getAlphaList();
    doubleFresnel_buffer.reserve(alpha_set.size());

    double angle;
    kvector_t kvec;
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    for (std::set<double>::const_iterator it =
             alpha_set.begin(); it != alpha_set.end(); ++it) {
        angle = *it;
        kvec.setLambdaAlphaPhi(lambda, -angle, 0.0);
        specularCalculator.execute(*mp_multi_layer, kvec, coeffs);
        doubleFresnel_buffer.push_back( doubleFresnelPair_t(angle,coeffs) );
    }

    // run through layers and construct T,R functions
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> Layer " << i_layer;
        DoubleToPairOfComplexMap RT_map;
        DoubleToComplexMap Kz_map;

        for(std::vector<doubleFresnelPair_t >::const_iterator it=
                doubleFresnel_buffer.begin();
            it!=doubleFresnel_buffer.end(); ++it) {
            double angle = (*it).first;
            const SpecularMatrix::LayerMatrixCoeff& coeff = (*it).second[i_layer];
            RT_map[angle] = complexpair_t(coeff.R(), coeff.T());
            Kz_map[angle] = coeff.kz;
        }

        // layer DWBA simulation
        std::map<size_t, LayerDWBASimulation*>::const_iterator pos =
            m_layer_dwba_simulation_map.find(i_layer);
        if(pos != m_layer_dwba_simulation_map.end() ) {
            LayerDWBASimulation *p_layer_dwba_sim = pos->second;
            p_layer_dwba_sim->setKzAndRTFunctions(Kz_map, RT_map);
            p_layer_dwba_sim->run();
            addDWBAIntensity( p_layer_dwba_sim->getDWBAIntensity() );
        }

        // layer roughness DWBA
        if(mp_roughness_dwba_simulation) {
            mp_roughness_dwba_simulation->setReflectionTransmissionFunction
                (i_layer, RT_map);
        }

    } // i_layer

    if(mp_roughness_dwba_simulation) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> roughness";
        mp_roughness_dwba_simulation->run();
        addDWBAIntensity( mp_roughness_dwba_simulation->getDWBAIntensity() );
    }
}

std::set<double> MultiLayerDWBASimulation::getAlphaList() const
{
    std::set<double> result;
    const IAxis *p_alpha_axis = getDWBAIntensity().getAxis("alpha_f");
    for (size_t i=0; i<p_alpha_axis->getSize(); ++i) {
        Bin1D alpha_bin = p_alpha_axis->getBin(i);
        result.insert(alpha_bin.m_lower);
        result.insert(alpha_bin.getMidPoint());
        result.insert(alpha_bin.m_upper);
    }
    // Also add input angle
    result.insert(-m_alpha_i);
    return result;
}


