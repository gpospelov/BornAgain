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
#include "ParticleLayoutComputation.h"
#include "Layer.h"
#include "ILayerSpecularInfo.h"
#include "Logger.h"
#include "MatrixSpecularInfoMap.h"
#include "MultiLayer.h"
#include "RoughMultiLayerComputation.h"
#include "SpecularComputation.h"
#include "ScalarSpecularInfoMap.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"
#include "SpecularMagnetic.h"
#include "SpecularMatrix.h"
#include <iterator> // needed for back_inserter

MainComputation::MainComputation(
    const MultiLayer& multi_layer,
    const SimulationOptions& options,
    ProgressHandler& progress,
    const std::vector<SimulationElement>::iterator& begin_it,
    const std::vector<SimulationElement>::iterator& end_it)
    : mP_multi_layer(multi_layer.clone())
    , mP_inverted_multilayer(nullptr)
    , m_sim_options(options)
    , m_progress(&progress)
    , m_begin_it(begin_it)
    , m_end_it(end_it)
    , mp_roughness_computation(nullptr)
{
    msglog(Logging::DEBUG2) << "MainComputation::init()";

    size_t nLayers = mP_multi_layer->getNumberOfLayers();
    m_layer_computation.resize( nLayers );
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mP_multi_layer->getLayer(i);
        for (size_t j=0; j<layer->getNumberOfLayouts(); ++j)
            m_layer_computation[i].push_back(
                        new ParticleLayoutComputation(mP_multi_layer.get(),
                                                      layer->getLayout(j), i));
    }
    // scattering from rough surfaces in DWBA
    if (mP_multi_layer->hasRoughness())
        mp_roughness_computation = new RoughMultiLayerComputation(mP_multi_layer.get());
    mp_specular_computation = new SpecularComputation();
}

MainComputation::~MainComputation()
{
    delete mp_roughness_computation;
    delete mp_specular_computation;
    for (auto& layer_comp: m_layer_computation)
        for (ParticleLayoutComputation* comp: layer_comp)
            delete comp;
}

void MainComputation::run()
{
    m_status.setRunning();
    try {
        runProtected();
        m_status.setCompleted();
    } catch(const std::exception &ex) {
        m_status.setErrorMessage(std::string(ex.what()));
        m_status.setFailed();
    }
}

// The normalization of the calculated scattering intensities is:
// For nanoparticles: rho * (scattering cross-section/scattering particle)
// For roughness: (scattering cross-section of area S)/S
// For specular peak: |R|^2 * sin(alpha_i) / solid_angle
// This allows them to be added and normalized together to the beam afterwards
void MainComputation::runProtected()
{
    msglog(Logging::DEBUG2) << "MainComputation::runProtected()";

    if (mP_multi_layer->requiresMatrixRTCoefficients())
        collectRTCoefficientsMatrix();
    else
        collectRTCoefficientsScalar();

    // run through layers and run layer simulations
    std::vector<SimulationElement> layer_elements;
    std::copy(m_begin_it, m_end_it, std::back_inserter(layer_elements));
    bool polarized = mP_multi_layer->containsMagneticMaterial();
    for (auto& layer_comp: m_layer_computation) {
        for (const ParticleLayoutComputation* comp: layer_comp) {
            if (!m_progress->alive())
                return;
            comp->eval(m_sim_options, m_progress, polarized,
                       layer_elements.begin(), layer_elements.end());
            addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
        }
    }

    if (!mP_multi_layer->requiresMatrixRTCoefficients() && mp_roughness_computation) {
        msglog(Logging::DEBUG2) << "MainComputation::run() -> roughness";
        if (!m_progress->alive())
            return;
        mp_roughness_computation->eval(m_sim_options, m_progress, polarized,
                                       layer_elements.begin(), layer_elements.end());
        addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }

    if (m_sim_options.includeSpecular())
        mp_specular_computation->eval(m_sim_options, m_progress, polarized, m_begin_it, m_end_it);
}

void MainComputation::collectRTCoefficientsScalar()
{
    if (m_fresnel_info.size()!=0) return;
    // run through layers and construct T,R functions
    for(size_t i=0; i<mP_multi_layer->getNumberOfLayers(); ++i) {
        msglog(Logging::DEBUG2) << "MainComputation::run() -> Layer " << i;
        m_fresnel_info.push_back(new ScalarSpecularInfoMap(mP_multi_layer.get(), i));

        // layer DWBA simulation
        for(ParticleLayoutComputation* comp: m_layer_computation[i])
            comp->setSpecularInfo(&m_fresnel_info);

    }
    // specular simulation (R^2 at top layer)
    mp_specular_computation->setSpecularInfo(&m_fresnel_info);
    // layer roughness DWBA
    if (mp_roughness_computation)
        mp_roughness_computation->setSpecularInfo(&m_fresnel_info);
}

void MainComputation::collectRTCoefficientsMatrix()
{
    if (m_fresnel_info.size()!=0) return;
    mP_inverted_multilayer.reset(mP_multi_layer->cloneInvertB());
    // run through layers and construct T,R functions
    for(size_t i=0; i<mP_multi_layer->getNumberOfLayers(); ++i) {
        msglog(Logging::DEBUG2) << "MainComputation::runMagnetic() -> Layer " << i;
        m_fresnel_info.push_back(new MatrixSpecularInfoMap(mP_multi_layer.get(),
                                                           mP_inverted_multilayer.get(), i));

        // layer DWBA simulation
        for(ParticleLayoutComputation* comp: m_layer_computation[i])
            comp->setSpecularInfo(&m_fresnel_info);
    }
}
