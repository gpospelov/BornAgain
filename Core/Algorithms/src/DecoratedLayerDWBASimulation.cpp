// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DecoratedLayerDWBASimulation.cpp
//! @brief     Implements class DecoratedLayerDWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecoratedLayerDWBASimulation.h"
#include "Layer.h"
#include "FormFactors.h"
#include "MessageService.h"
#include "BornAgainNamespace.h"

#include <boost/scoped_ptr.hpp>

DecoratedLayerDWBASimulation::DecoratedLayerDWBASimulation(const Layer *p_layer,
                                                           size_t layout_index)
    : LayerDWBASimulation(p_layer), m_layout_index(layout_index)
{
}

DecoratedLayerDWBASimulation::~DecoratedLayerDWBASimulation()
{
}

void DecoratedLayerDWBASimulation::init(const Simulation &simulation,
                                        std::vector<SimulationElement>::iterator begin_it,
                                        std::vector<SimulationElement>::iterator end_it)
{
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::init()";
    DWBASimulation::init(simulation, begin_it, end_it);
}

void DecoratedLayerDWBASimulation::run()
{
    setStatus(RUNNING);
    try {
        runProtected();
        setStatus(COMPLETED);
    } catch (const std::exception &ex) {
        setRunMessage(std::string(ex.what()));
        setStatus(FAILED);
        std::string message("DecoratedLayerDWBASimulation::run() -> Exception was caught \n\n"
                            + getRunMessage());
        throw Exceptions::RuntimeErrorException(message);
    }
}

void DecoratedLayerDWBASimulation::runProtected()
{
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::runProtected()";
    boost::scoped_ptr<const IInterferenceFunctionStrategy> P_strategy(createAndInitStrategy());

    calculateCoherentIntensity(P_strategy.get());
}

IInterferenceFunctionStrategy *DecoratedLayerDWBASimulation::createAndInitStrategy() const
{
    LayerStrategyBuilder builder(*mp_layer, *mp_simulation, m_sim_params, m_layout_index);
    assert(mp_specular_info);
    builder.setRTInfo(*mp_specular_info);
    IInterferenceFunctionStrategy *p_strategy = builder.createStrategy();
    return p_strategy;
}

void DecoratedLayerDWBASimulation::calculateCoherentIntensity(
    const IInterferenceFunctionStrategy *p_strategy)
{
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::calculateCoh...()";
    double lambda = m_begin_it->getWavelength();
    double alpha_i = m_begin_it->getAlphaI();
    double phi_i = m_begin_it->getPhiI();
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, phi_i);
    double total_surface_density = mp_layer->getTotalParticleSurfaceDensity(m_layout_index);

    std::vector<SimulationElement>::iterator it = m_begin_it;
    while (it != m_end_it) {
        if (!m_progress.update())
            break;
        Bin1D alpha_bin(it->getAlphaMin(), it->getAlphaMax());
        Bin1D phi_bin(it->getPhiMin(), it->getPhiMax());
        double alpha_f = alpha_bin.getMidPoint();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0) {
            ++it;
            continue;
        }
        Bin1DCVector k_f_bin = getKfBin(lambda, alpha_bin, phi_bin);
        // each ffdwba: 1 call to getOutCoeffs
        if (checkPolarizationPresent()) {
            // matrix dwba calculation
            it->setIntensity(p_strategy->evaluate(k_i, it->getPolarization(), k_f_bin,
                                                  it->getAnalyzerOperator(), alpha_bin, phi_bin)
                             * total_surface_density);
        } else {
            // scalar dwba calculation
            k_i.setZ(-(complex_t)mp_specular_info->getInCoefficients()->getScalarKz());
            it->setIntensity(p_strategy->evaluate(k_i, k_f_bin, alpha_bin, phi_bin)
                             * total_surface_density);
        }
        ++it;
    }
    m_progress.finished();
}
