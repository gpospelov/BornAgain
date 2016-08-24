// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MainComputation.cpp
//! @brief     Implements class MainComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MainComputation.h"
#include "BornAgainNamespace.h"
#include "DecoratedLayerComputation.h"
#include "Layer.h"
#include "LayerInterface.h"
#include "LayerRoughness.h"
#include "LayerSpecularInfo.h"
#include "Logger.h"
#include "MatrixSpecularInfoMap.h"
#include "MultiLayer.h"
#include "RoughMultiLayerComputation.h"
#include "ScalarSpecularInfoMap.h"
#include "Simulation.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"
#include "SpecularMatrix.h"

#include <algorithm>
#include <iterator>

MainComputation::MainComputation(
    const MultiLayer* p_multi_layer,
    const SimulationOptions& options,
    Simulation& simulation,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
    : m_sim_options(options)
    , mp_roughness_computation(nullptr)
{
    mp_multi_layer = p_multi_layer->clone();

    msglog(MSG::DEBUG2) << "MainComputation::init()";
    m_begin_it = begin_it;
    m_end_it = end_it;

    // initialising call backs
    simulation.initProgressHandlerDWBA(&m_progress);

    for (size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        m_layer_computation.push_back({});
        for (size_t j=0; j<mp_multi_layer->getLayer(i)->getNumberOfLayouts(); ++j)
            m_layer_computation[i].push_back(
                new DecoratedLayerComputation(mp_multi_layer->getLayer(i), j));
    }
    // scattering from rough surfaces in DWBA
    if (mp_multi_layer->hasRoughness())
        mp_roughness_computation = new RoughMultiLayerComputation(mp_multi_layer);
}

MainComputation::~MainComputation()
{
    delete mp_multi_layer;
    delete mp_roughness_computation;
    for (auto& layer_comp: m_layer_computation)
        for (DecoratedLayerComputation* comp: layer_comp)
            delete comp;
}

void MainComputation::run()
{
    m_outcome.setRunning();
    try {
        runProtected();
        m_outcome.setCompleted();
    } catch(const std::exception &ex) {
        m_outcome.setRunMessage(std::string(ex.what()));
        m_outcome.setFailed();
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// This allows them to be added and normalized together to the beam afterwards
void MainComputation::runProtected()
{
    msglog(MSG::DEBUG2) << "MainComputation::runProtected()";

    if (mp_multi_layer->requiresMatrixRTCoefficients())
        collectRTCoefficientsMatrix();
    else
        collectRTCoefficientsScalar();

    // run through layers and run layer simulations
    std::vector<SimulationElement> layer_elements;
    std::copy(m_begin_it, m_end_it, std::back_inserter(layer_elements));
    bool polarized = mp_multi_layer->containsMagneticMaterial();
    for (auto& layer_comp: m_layer_computation) {
        for (DecoratedLayerComputation* comp: layer_comp) {
            comp->eval(m_sim_options, polarized, *mp_multi_layer,
                       layer_elements.begin(), layer_elements.end());
            addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
        }
    }

    if (!mp_multi_layer->requiresMatrixRTCoefficients() && mp_roughness_computation) {
        msglog(MSG::DEBUG2) << "MainComputation::run() -> roughness";
        mp_roughness_computation->eval(layer_elements.begin(), layer_elements.end());
        addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }
}

void MainComputation::collectRTCoefficientsScalar()
{
    // run through layers and construct T,R functions
    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        msglog(MSG::DEBUG2) << "MainComputation::run() -> Layer " << i;
        LayerSpecularInfo layer_coeff_map;
        layer_coeff_map.addRTCoefficients(new ScalarSpecularInfoMap(mp_multi_layer, i));

        // layer DWBA simulation
        for(DecoratedLayerComputation* comp: m_layer_computation[i])
            comp->setSpecularInfo(layer_coeff_map);

        // layer roughness DWBA
        if (mp_roughness_computation)
            mp_roughness_computation->setSpecularInfo(i, layer_coeff_map);
    }
}

void MainComputation::collectRTCoefficientsMatrix()
{
    // run through layers and construct T,R functions
    for(size_t i=0; i<mp_multi_layer->getNumberOfLayers(); ++i) {
        msglog(MSG::DEBUG2) << "MainComputation::runMagnetic() -> Layer " << i;
        LayerSpecularInfo layer_coeff_map;
        layer_coeff_map.addRTCoefficients(new MatrixSpecularInfoMap(mp_multi_layer, i));

        // layer DWBA simulation
        for(DecoratedLayerComputation* comp: m_layer_computation[i])
            comp->setSpecularInfo(layer_coeff_map);
    }
}
