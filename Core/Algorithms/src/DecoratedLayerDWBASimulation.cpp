// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/LayerDecoratorDWBASimulation.cpp
//! @brief     Implements class LayerDecoratorDWBASimulation.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DecoratedLayerDWBASimulation.h"
#include "Layer.h"
#include "FormFactors.h"
#include "MessageService.h"

DecoratedLayerDWBASimulation::DecoratedLayerDWBASimulation(
    const Layer *p_layer)
{
    mp_layer = p_layer->clone();
    mp_diffuseDWBA = mp_layer->createDiffuseDWBASimulation();
}

DecoratedLayerDWBASimulation::~DecoratedLayerDWBASimulation()
{
    delete mp_layer;
    delete mp_diffuseDWBA;
}

void DecoratedLayerDWBASimulation::init(const Simulation& simulation)
{
    msglog(MSG::DEBUG) << "LayerDecoratorDWBASimulation::init()";
    DWBASimulation::init(simulation);
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->init(simulation);
    }
}

void DecoratedLayerDWBASimulation::run()
{
    msglog(MSG::DEBUG) << "LayerDecoratorDWBASimulation::run()";
    IInterferenceFunctionStrategy *p_strategy = createAndInitStrategy();

    calculateCoherentIntensity(p_strategy);
    calculateInCoherentIntensity();

    delete p_strategy;
}

IInterferenceFunctionStrategy
    *DecoratedLayerDWBASimulation::createAndInitStrategy() const
{
    LayerStrategyBuilder builder(
        *mp_layer, *mp_simulation, m_sim_params);
    if (checkPolarizationPresent()) {
        assert(mp_coeff_map);
        builder.setRTInfo(*mp_coeff_map);
    }
    else {
        assert(mp_RT_function);
        builder.setRTInfo(*mp_RT_function);
    }
    IInterferenceFunctionStrategy *p_strategy = builder.createStrategy();
    return p_strategy;
}

void DecoratedLayerDWBASimulation::calculateCoherentIntensity(
    const IInterferenceFunctionStrategy *p_strategy)
{
    msglog(MSG::DEBUG) << "LayerDecoratorDWBASimulation::calculateCoh...()";
    double wavelength = getWaveLength();
    double total_surface_density =
        mp_layer->getTotalParticleSurfaceDensity();

    cvector_t k_ij = m_ki;
    k_ij.setZ(-mp_kz_function->evaluate(-m_alpha_i));

    DWBASimulation::iterator it_intensity = begin();
    while ( it_intensity != end() )
    {
        Bin1D phi_bin = getDWBAIntensity().getBinOfAxis(
            "phi_f", it_intensity.getIndex());
        Bin1D alpha_bin = getDWBAIntensity().getBinOfAxis(
            "alpha_f", it_intensity.getIndex());
        double alpha_f = alpha_bin.getMidPoint();
        if (std::abs(mp_RT_function->evaluate(alpha_f).first)!=0.0 &&
            alpha_f<0) {
            ++it_intensity;
            continue;
        }
        Bin1DCVector k_f_bin = getKfBin(wavelength, alpha_bin, phi_bin);
        *it_intensity =
            p_strategy->evaluate(k_ij, k_f_bin,
                                 -m_alpha_i, alpha_f)*total_surface_density;
        ++it_intensity;
    }
}

void DecoratedLayerDWBASimulation::calculateInCoherentIntensity()
{
    msglog(MSG::DEBUG) << "Calculating incoherent scattering...";
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->setReflectionTransmissionFunction( *mp_RT_function);
        mp_diffuseDWBA->setKzFunction( *mp_kz_function);
        mp_diffuseDWBA->setThreadInfo(m_thread_info);
        mp_diffuseDWBA->run();
        addDWBAIntensity( mp_diffuseDWBA->getDWBAIntensity() );
    }
}


