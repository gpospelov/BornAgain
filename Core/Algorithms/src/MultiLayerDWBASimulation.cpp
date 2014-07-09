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

#include "SpecularMatrix.h"
#include "SpecularMagnetic.h"
#include "MultiLayer.h"
#include "MultiLayerRoughnessDWBASimulation.h"
#include "MessageService.h"
#include "ScalarSpecularInfoMap.h"
#include "MatrixSpecularInfoMap.h"
#include "BornAgainNamespace.h"

#include <boost/scoped_ptr.hpp>


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
    m_dwba_intensity.setAllTo(0.0);
    if (mp_polarization_output) {
        mp_polarization_output->setAllTo(Eigen::Matrix2d::Zero());
    }

    if (requiresMatrixRTCoefficients()) {
        collectRTCoefficientsMatrix();
    }
    else {
        collectRTCoefficientsScalar();
    }

    // run through layers and run layer simulations
    for (std::map<size_t, LayerDWBASimulation*>::const_iterator it =
            m_layer_dwba_simulation_map.begin();
            it != m_layer_dwba_simulation_map.end(); ++it)
    {
        LayerDWBASimulation *p_layer_dwba_sim = it->second;
        p_layer_dwba_sim->run();
        if (mp_polarization_output) {
            addPolarizedDWBAIntensity(
                p_layer_dwba_sim->getPolarizedDWBAIntensity() );
        }
        else {
            addDWBAIntensity( p_layer_dwba_sim->getDWBAIntensity() );
        }
    }

    if (!mp_polarization_output && mp_roughness_dwba_simulation) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run() -> roughness";
        mp_roughness_dwba_simulation->run();
        addDWBAIntensity( mp_roughness_dwba_simulation->getDWBAIntensity() );
    }
}

void MultiLayerDWBASimulation::collectRTCoefficientsScalar()
{
    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    double lambda = 2*M_PI/m_ki_real.mag();

    // the coefficients for the incoming wavevector are calculated on the
    // original sample
    SpecularMatrix specularCalculator;
    SpecularMatrix::MultiLayerCoeff_t coeffs;
    specularCalculator.execute(*mp_multi_layer, m_ki_real, coeffs);

    // run through layers and construct T,R functions
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::run()"
                "-> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        ScalarSpecularInfoMap *p_coeff_map = new ScalarSpecularInfoMap(
                    mp_multi_layer, i_layer, lambda);
        layer_coeff_map.addOutCoefficients(p_coeff_map);

        // add reflection/transmission coeffs from incoming beam
        layer_coeff_map.addInCoefficients(new ScalarRTCoefficients(
                coeffs[i_layer]));

        // layer DWBA simulation
        std::map<size_t, LayerDWBASimulation*>::const_iterator pos =
            m_layer_dwba_simulation_map.find(i_layer);
        if(pos != m_layer_dwba_simulation_map.end() ) {
            LayerDWBASimulation *p_layer_dwba_sim = pos->second;
            p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
        }

        // layer roughness DWBA
        if(mp_roughness_dwba_simulation) {
            mp_roughness_dwba_simulation->setSpecularInfo(i_layer,
                    layer_coeff_map);
        }

    } // i_layer
}

void MultiLayerDWBASimulation::collectRTCoefficientsMatrix()
{
    kvector_t m_ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    double lambda = 2*M_PI/m_ki_real.mag();

    // the coefficients for the incoming wavevector are calculated on the
    // original sample
    SpecularMagnetic specularCalculator;
    SpecularMagnetic::MultiLayerCoeff_t coeffs;
    specularCalculator.execute(*mp_multi_layer, m_ki_real, coeffs);

    // run through layers and add DWBA from each layer
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG) << "MultiLayerDWBASimulation::runMagnetic()"
                "-> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        MatrixSpecularInfoMap *p_coeff_map = new MatrixSpecularInfoMap(
                    mp_multi_layer, i_layer, lambda);
        layer_coeff_map.addOutCoefficients(p_coeff_map);

        // add reflection/transmission coeffs from incoming beam
        layer_coeff_map.addInCoefficients(new MatrixRTCoefficients(
                coeffs[i_layer]));

        // layer DWBA simulation
        std::map<size_t, LayerDWBASimulation*>::const_iterator pos =
            m_layer_dwba_simulation_map.find(i_layer);
        if(pos != m_layer_dwba_simulation_map.end() ) {
            LayerDWBASimulation *p_layer_dwba_sim = pos->second;
            p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
        }
    } // i_layer
}

bool MultiLayerDWBASimulation::requiresMatrixRTCoefficients() const
{
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        const Layer *p_layer = mp_multi_layer->getLayer(i);
        const IMaterial *p_material = p_layer->getMaterial();
        if (!p_material->isScalarMaterial()) return true;
    }
    return false;
}

