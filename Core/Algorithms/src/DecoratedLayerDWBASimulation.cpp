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

void DecoratedLayerDWBASimulation::init(const GISASSimulation &simulation,
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
    double wavelength = getWaveLength();
    double total_surface_density = mp_layer->getTotalParticleSurfaceDensity(m_layout_index);

    DWBASimulation::iterator it = begin();
    while (it != end()) {
        if (!m_progress.update())
            break;

        Bin1D phi_bin = getDWBAIntensity().getBinOfAxis(BornAgain::PHI_AXIS_NAME, it.getIndex());
        Bin1D alpha_bin
            = getDWBAIntensity().getBinOfAxis(BornAgain::ALPHA_AXIS_NAME, it.getIndex());
        double alpha_f = alpha_bin.getMidPoint();
        size_t n_layers = mp_layer->getNumberOfLayers();
        if (n_layers > 1 && alpha_f < 0) {
            ++it;
            continue;
        }
        Bin1DCVector k_f_bin = getKfBin(wavelength, alpha_bin, phi_bin);
        // each ffdwba: 1 call to getOutCoeffs
        if (checkPolarizationPresent()) {
            // matrix dwba calculation
            *it = p_strategy->evaluate(m_ki, m_beam_polarization, k_f_bin, m_detector_polarization,
                                       alpha_bin, phi_bin) * total_surface_density;
        } else {
            // scalar dwba calculation
            cvector_t k_ij = m_ki;
            k_ij.setZ(-(complex_t)mp_specular_info->getInCoefficients()->getScalarKz());
            *it = p_strategy->evaluate(k_ij, k_f_bin, alpha_bin, phi_bin) * total_surface_density;
        }
        ++it;
    }
    m_progress.finished();
}
