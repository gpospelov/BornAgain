// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerComputation.cpp
//! @brief     Implements class MultiLayerComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MultiLayerComputation.h"
#include "BornAgainNamespace.h"
#include "DecoratedLayerComputation.h"
#include "Layer.h"
#include "LayerComputation.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "LayerSpecularInfo.h"
#include "Logger.h"
#include "MatrixSpecularInfoMap.h"
#include "MultiLayer.h"
#include "MultiLayerRoughnessComputation.h"
#include "ScalarSpecularInfoMap.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"
#include "SpecularMatrix.h"

#include <iterator>

MultiLayerComputation::MultiLayerComputation(const MultiLayer* p_multi_layer)
    : mp_roughness_dwba_simulation(nullptr)
{
    mp_multi_layer = p_multi_layer->clone();
}

MultiLayerComputation::~MultiLayerComputation()
{
    delete mp_multi_layer;
    delete mp_roughness_dwba_simulation;
}

MultiLayerComputation* MultiLayerComputation::clone() const
{
    throw Exceptions::NotImplementedException(
        "Bug: unexpected call to MultiLayerComputation::clone(); "
        "functionality not yet implemented");
}

void MultiLayerComputation::init(
    const SimulationOptions& options,
    const Simulation& simulation,
    std::vector<SimulationElement>::iterator begin_it,
    std::vector<SimulationElement>::iterator end_it)
{
    msglog(MSG::DEBUG2) << "MultiLayerComputation::init()";
    Computation::init(options, simulation, begin_it, end_it);

    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        for (size_t j=0; j<mp_multi_layer->getLayer(i)->getNumberOfLayouts(); ++j) {
            LayerComputation* p_layer_dwba_sim =
                new DecoratedLayerComputation(mp_multi_layer->getLayer(i), j);
            if (p_layer_dwba_sim) {
                if (m_layer_dwba_simulations_map.find(i) == m_layer_dwba_simulations_map.end())
                    m_layer_dwba_simulations_map[i] = SafePointerVector<LayerComputation>();
                m_layer_dwba_simulations_map[i].push_back(p_layer_dwba_sim);
            }
        }

    }
    // scattering from rough surfaces in DWBA
    for (size_t i=0; i<mp_multi_layer->getNumberOfInterfaces(); ++i) {
        if(mp_multi_layer->getLayerInterface(i)->getRoughness() ) {
            mp_roughness_dwba_simulation = new MultiLayerRoughnessComputation(mp_multi_layer);
            break;
        }
    }
}

void MultiLayerComputation::run()
{
    m_outcome.setRunning();
    try {
        runProtected();
        m_outcome.setCompleted();
    }
    catch(const std::exception &ex) {
        m_outcome.setRunMessage(std::string(ex.what()));
        m_outcome.setFailed();
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// This allows them to be added and normalized together to the beam afterwards
void MultiLayerComputation::runProtected()
{
    msglog(MSG::DEBUG2) << "MultiLayerComputation::runProtected()";
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
            LayerComputation* p_layer_dwba_sim = it->second[i];
            p_layer_dwba_sim->init(
                m_sim_options, *mp_simulation, layer_elements.begin(), layer_elements.end());
            p_layer_dwba_sim->run();
            addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
        }
    }

    if (!mp_multi_layer->requiresMatrixRTCoefficients() && mp_roughness_dwba_simulation) {
        msglog(MSG::DEBUG2) << "MultiLayerComputation::run() -> roughness";
        mp_roughness_dwba_simulation->init(
            m_sim_options, *mp_simulation, layer_elements.begin(), layer_elements.end());
        mp_roughness_dwba_simulation->run();
        addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }
}

void MultiLayerComputation::collectRTCoefficientsScalar()
{
    // run through layers and construct T,R functions
    for(size_t i_layer=0;
        i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG2) << "MultiLayerComputation::run() -> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        ScalarSpecularInfoMap* p_coeff_map = new ScalarSpecularInfoMap(mp_multi_layer, i_layer);
        layer_coeff_map.addRTCoefficients(p_coeff_map);

        // layer DWBA simulation
        auto pos = m_layer_dwba_simulations_map.find(i_layer);
        if (pos != m_layer_dwba_simulations_map.end() ) {
            for (size_t i=0; i<pos->second.size();++i) {
                LayerComputation* p_layer_dwba_sim = pos->second[i];
                p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
            }
        }

        // layer roughness DWBA
        if (mp_roughness_dwba_simulation)
            mp_roughness_dwba_simulation->setSpecularInfo(i_layer, layer_coeff_map);
    } // i_layer
}

void MultiLayerComputation::collectRTCoefficientsMatrix()
{
    // run through layers and add DWBA from each layer
    for(size_t i_layer=0; i_layer<mp_multi_layer->getNumberOfLayers(); ++i_layer) {
        msglog(MSG::DEBUG2) << "MultiLayerComputation::runMagnetic() -> Layer " << i_layer;
        LayerSpecularInfo layer_coeff_map;
        MatrixSpecularInfoMap* p_coeff_map = new MatrixSpecularInfoMap(mp_multi_layer, i_layer);
        layer_coeff_map.addRTCoefficients(p_coeff_map);

        // layer DWBA simulation
        auto pos = m_layer_dwba_simulations_map.find(i_layer);
        if (pos != m_layer_dwba_simulations_map.end() ) {
            for (size_t i=0; i<pos->second.size();++i) {
                LayerComputation* p_layer_dwba_sim = pos->second[i];
                p_layer_dwba_sim->setSpecularInfo(layer_coeff_map);
            }
        }
    } // i_layer
}
