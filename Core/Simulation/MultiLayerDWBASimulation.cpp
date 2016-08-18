// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/MultiLayerDWBASimulation.cpp
//! @brief     Implements class MultiLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerDWBASimulation.h"
#include "BornAgainNamespace.h"
#include "DecoratedLayerDWBASimulation.h"
#include "Layer.h"
#include "LayerDWBASimulation.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "Logger.h"
#include "MatrixSpecularInfoMap.h"
#include "MultiLayer.h"
#include "MultiLayerRoughnessDWBASimulation.h"
#include "ScalarSpecularInfoMap.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"
#include "SpecularMatrix.h"

#include <iterator>

MultiLayerDWBASimulation::MultiLayerDWBASimulation(const MultiLayer* p_multi_layer)
  : mp_roughness_dwba_simulation(0)
{
    mp_multi_layer = p_multi_layer->clone();
}

MultiLayerDWBASimulation::~MultiLayerDWBASimulation()
{
    delete mp_multi_layer;
    delete mp_roughness_dwba_simulation;
}

void MultiLayerDWBASimulation::init(const Simulation& simulation,
                                    std::vector<SimulationElement>::iterator begin_it,
                                    std::vector<SimulationElement>::iterator end_it)
{
    msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::init()";
    DWBASimulation::init(simulation, begin_it, end_it);
    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        for (size_t j=0; j<mp_multi_layer->getLayer(i)->getNumberOfLayouts(); ++j) {
            LayerDWBASimulation* p_layer_dwba_sim =
                new DecoratedLayerDWBASimulation(mp_multi_layer->getLayer(i), j);
            if (p_layer_dwba_sim) {
                if (m_layer_dwba_simulations_map.find(i) == m_layer_dwba_simulations_map.end())
                    m_layer_dwba_simulations_map[i] = SafePointerVector<LayerDWBASimulation>();
                m_layer_dwba_simulations_map[i].push_back(p_layer_dwba_sim);
            }
        }

    }
    // scattering from rough surfaces in DWBA
    for (size_t i=0; i<mp_multi_layer->getNumberOfInterfaces(); ++i) {
        if(mp_multi_layer->getLayerInterface(i)->getRoughness() ) {
            mp_roughness_dwba_simulation = new MultiLayerRoughnessDWBASimulation(mp_multi_layer);
            break;
        }
    }
}

void MultiLayerDWBASimulation::run()
{
    setStatus(RUNNING);
    try {
        runProtected();
        setStatus(COMPLETED);
    }
    catch(const std::exception &ex) {
        setRunMessage(std::string(ex.what()));
        setStatus(FAILED);
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// This allows them to be added and normalized together to the beam afterwards
void MultiLayerDWBASimulation::runProtected()
{
    msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::runProtected()";
    m_dwba_intensity.setAllTo(0.0);

    if (mp_multi_layer->requiresMatrixRTCoefficients())
        collectRTCoefficientsMatrix();
    else
        collectRTCoefficientsScalar();

    // run through layers and run layer simulations
    std::vector<SimulationElement> layer_elements;
    std::copy(m_begin_it, m_end_it, std::back_inserter(layer_elements));
    for (auto it=m_layer_dwba_simulations_map.begin(); it!=m_layer_dwba_simulations_map.end(); ++it)
    {
        for (size_t i=0; i<it->second.size(); ++i) {
            LayerDWBASimulation* p_layer_dwba_sim = it->second[i];
            p_layer_dwba_sim->init(*mp_simulation, layer_elements.begin(), layer_elements.end());
            p_layer_dwba_sim->run();
            addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
        }
    }

    if (!mp_multi_layer->requiresMatrixRTCoefficients() && mp_roughness_dwba_simulation) {
        msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::run() -> roughness";
        mp_roughness_dwba_simulation->init(*mp_simulation, layer_elements.begin(),
                                           layer_elements.end());
        mp_roughness_dwba_simulation->run();
        addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }
}

void MultiLayerDWBASimulation::collectRTCoefficientsScalar()
{
    // run through layers and construct T,R functions
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::run()"
                "-> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        ScalarSpecularInfoMap* p_coeff_map = new ScalarSpecularInfoMap(mp_multi_layer, i_layer);
        layer_coeff_map.addRTCoefficients(p_coeff_map);

        // layer DWBA simulation
        auto pos = m_layer_dwba_simulations_map.find(i_layer);
        if(pos != m_layer_dwba_simulations_map.end() ) {
            for (size_t i=0; i<pos->second.size();++i) {
                LayerDWBASimulation* p_layer_dwba_sim = pos->second[i];
                p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
            }
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
    // run through layers and add DWBA from each layer
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG2) << "MultiLayerDWBASimulation::runMagnetic()"
                "-> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        MatrixSpecularInfoMap* p_coeff_map = new MatrixSpecularInfoMap(mp_multi_layer, i_layer);
        layer_coeff_map.addRTCoefficients(p_coeff_map);

        // layer DWBA simulation
        auto pos = m_layer_dwba_simulations_map.find(i_layer);
        if(pos != m_layer_dwba_simulations_map.end() ) {
            for (size_t i=0; i<pos->second.size();++i) {
                LayerDWBASimulation* p_layer_dwba_sim = pos->second[i];
                p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
            }
        }
    } // i_layer
}
