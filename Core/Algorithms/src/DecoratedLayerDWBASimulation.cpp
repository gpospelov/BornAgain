// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/DecoratedLayerDWBASimulation.cpp
//! @brief     Implements class DecoratedLayerDWBASimulation.
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
#include "BornAgainNamespace.h"

#include <boost/scoped_ptr.hpp>

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
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::init()";
    DWBASimulation::init(simulation);
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->init(simulation);
    }
}

void DecoratedLayerDWBASimulation::run()
{
    msglog(MSG::DEBUG2) << "LayerDecoratorDWBASimulation::run()";
    boost::scoped_ptr<const IInterferenceFunctionStrategy> P_strategy(
            createAndInitStrategy());

    calculateCoherentIntensity(P_strategy.get());
    calculateInCoherentIntensity();
}

IInterferenceFunctionStrategy
    *DecoratedLayerDWBASimulation::createAndInitStrategy() const
{
    LayerStrategyBuilder builder(
        *mp_layer, *mp_simulation, m_sim_params);
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
    double total_surface_density =
        mp_layer->getTotalParticleSurfaceDensity();

    if (checkPolarizationPresent()) {
        // matrix dwba calculation
        OutputData<Eigen::Matrix2d>::iterator it =
                mp_polarization_output->begin(m_thread_info);
        while ( it != mp_polarization_output->end(m_thread_info) )
        {
            if( !m_progress.update()) break;

            Bin1D phi_bin = mp_polarization_output->getBinOfAxis(
                BornAgain::PHI_AXIS_NAME, it.getIndex());
            Bin1D alpha_bin = mp_polarization_output->getBinOfAxis(
                BornAgain::ALPHA_AXIS_NAME, it.getIndex());
            double alpha_f = alpha_bin.getMidPoint();
            if (m_sim_params.me_framework==SimulationParameters::DWBA &&
                    alpha_f<0) {
                ++it;
                continue;
            }
            Bin1DCVector k_f_bin = getKfBin1_matrix(wavelength, alpha_bin,
                    phi_bin);
            *it = p_strategy->evaluatePol(m_ki, k_f_bin, alpha_bin, phi_bin)
                    * total_surface_density;
            ++it;
        }
    }
    else {
        // scalar dwba calculation
        cvector_t k_ij = m_ki;
        k_ij.setZ(-(complex_t)mp_specular_info->getInCoefficients()
                ->getScalarKz());

        DWBASimulation::iterator it_intensity = begin();
        while ( it_intensity != end() )
        {
            if( !m_progress.update()) break;

            Bin1D phi_bin = getDWBAIntensity().getBinOfAxis(
                BornAgain::PHI_AXIS_NAME, it_intensity.getIndex());
            Bin1D alpha_bin = getDWBAIntensity().getBinOfAxis(
                BornAgain::ALPHA_AXIS_NAME, it_intensity.getIndex());
            double alpha_f = alpha_bin.getMidPoint();
            // First call to getOutCoeffs
            size_t n_layers = mp_layer->getNumberOfLayers();
            if (n_layers>1 && alpha_f<0) {
                ++it_intensity;
                continue;
            }
            // Two calls of getOutCoeffs in getKfBin
            Bin1DCVector k_f_bin = getKfBin(wavelength, alpha_bin, phi_bin);
            // each ffdwba: 1 call to getOutCoeffs
            // for ffdwbaconstz: 1 extra call to getOutCoeffs
            *it_intensity = p_strategy->evaluate(
                k_ij, k_f_bin, alpha_bin, phi_bin) * total_surface_density;
            ++it_intensity;
        }
    }
    m_progress.finished();
}


void DecoratedLayerDWBASimulation::calculateInCoherentIntensity()
{
    msglog(MSG::DEBUG2) << "Calculating incoherent scattering...";
    if (mp_diffuseDWBA) {
        mp_diffuseDWBA->setSpecularInfo(*mp_specular_info);
        mp_diffuseDWBA->setThreadInfo(m_thread_info);
        mp_diffuseDWBA->run();
        if (checkPolarizationPresent()) {
            addPolarizedDWBAIntensity(
                    mp_diffuseDWBA->getPolarizedDWBAIntensity() );
        }
        else {
            addDWBAIntensity( mp_diffuseDWBA->getDWBAIntensity() );
        }
    }
}
