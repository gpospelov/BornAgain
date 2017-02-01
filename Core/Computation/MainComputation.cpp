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
{
    size_t nLayers = mP_multi_layer->getNumberOfLayers();
    for (size_t i=0; i<nLayers; ++i) {
        const Layer* layer = mP_multi_layer->getLayer(i);
        for (size_t j=0; j<layer->getNumberOfLayouts(); ++j)
            m_computation_terms.push_back(
                        new ParticleLayoutComputation(mP_multi_layer.get(),
                                                      layer->getLayout(j), i));
    }
    // scattering from rough surfaces in DWBA
    if (mP_multi_layer->hasRoughness())
        m_computation_terms.push_back(new RoughMultiLayerComputation(mP_multi_layer.get()));
    if (m_sim_options.includeSpecular())
        m_computation_terms.push_back(new SpecularComputation(mP_multi_layer.get()));
}

MainComputation::~MainComputation()
{
    for (IComputationTerm* comp: m_computation_terms)
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
    if (mP_multi_layer->requiresMatrixRTCoefficients())
        collectFresnelMatrix();
    else
        collectFresnelScalar();

    std::vector<SimulationElement> layer_elements;
    std::copy(m_begin_it, m_end_it, std::back_inserter(layer_elements));
    bool polarized = mP_multi_layer->containsMagneticMaterial();
    // add all IComputationTerms:
    for (const IComputationTerm* comp: m_computation_terms) {
        if (!m_progress->alive())
            return;
        if (comp->eval(m_sim_options, m_progress, polarized,
                       layer_elements.begin(), layer_elements.end()) )
            addElementsWithWeight(layer_elements.begin(), layer_elements.end(), m_begin_it, 1.0);
    }
}

void MainComputation::collectFresnelScalar()
{
    if (m_full_fresnel_map.size()!=0) return;

    // run through layers and construct T,R maps
    for(size_t i=0; i<mP_multi_layer->getNumberOfLayers(); ++i) {
        m_full_fresnel_map.push_back(new ScalarSpecularInfoMap(mP_multi_layer.get(), i));
    }
    passFresnelInfo();
}

void MainComputation::collectFresnelMatrix()
{
    if (m_full_fresnel_map.size()!=0) return;
    mP_inverted_multilayer.reset(mP_multi_layer->cloneInvertB());

    // run through layers and construct T,R maps
    for(size_t i=0; i<mP_multi_layer->getNumberOfLayers(); ++i) {
        m_full_fresnel_map.push_back(new MatrixSpecularInfoMap(mP_multi_layer.get(),
                                                           mP_inverted_multilayer.get(), i));
    }
    passFresnelInfo();
}

void MainComputation::passFresnelInfo()
{
    for (IComputationTerm* comp: m_computation_terms) {
        comp->setSpecularInfo(&m_full_fresnel_map);
    }
}
