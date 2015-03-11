// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/TransformToDomain.h
//! @brief     Defines class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TRANSFORMTODOMAIN_H
#define TRANSFORMTODOMAIN_H

#include "Samples.h"
#include "InterferenceFunctions.h"
#include "ParameterizedItem.h"
#include "Instrument.h"

namespace TransformToDomain
{
BA_CORE_API_ IMaterial *createDomainMaterial(const ParameterizedItem &item);
BA_CORE_API_ MultiLayer *createMultiLayer(const ParameterizedItem &item);
BA_CORE_API_ Layer *createLayer(const ParameterizedItem &item);
BA_CORE_API_ ParticleLayout *createParticleLayout(const ParameterizedItem &item);
BA_CORE_API_ Particle *createParticle(const ParameterizedItem &item,
                                  double &depth, double &abundance);
BA_CORE_API_ ParticleCoreShell *createParticleCoreShell(const ParameterizedItem &item,
        const Particle &core, const Particle &shell, double &depth, double &abundance);
BA_CORE_API_ ParticleComposition *createParticleCollection(const ParameterizedItem &item,
                                                    double &depth, double &abundance);
BA_CORE_API_ IFormFactor *createFormFactor(const ParameterizedItem &item);
BA_CORE_API_ IDistribution1D * createDistribution(
        const ParameterizedItem &item);
BA_CORE_API_ IInterferenceFunction *createInterferenceFunction(
        const ParameterizedItem &item);
BA_CORE_API_ Instrument *createInstrument(const ParameterizedItem &item);
BA_CORE_API_ Beam *createBeam(const ParameterizedItem &item);
BA_CORE_API_ LayerRoughness *createLayerRoughness(const ParameterizedItem &item);
BA_CORE_API_ void initInstrumentFromDetectorItem(const ParameterizedItem &item,
                                                 Instrument *instrument);
BA_CORE_API_ void addDistributionParametersToSimulation(const ParameterizedItem &beam_item, Simulation *simulation);
}

#endif // TRANSFORMTODOMAIN_H
