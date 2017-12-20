// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/TransformToDomain.h
//! @brief     Defines class TransformToDomain
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TRANSFORMTODOMAIN_H
#define TRANSFORMTODOMAIN_H

#include "Beam.h"
#include "Distributions.h" // for IDistribution1D
#include "IInterferenceFunction.h"
#include "IParticle.h"
#include "Instrument.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include <memory>

class GISASSimulation;
class SessionItem;
class DetectorItem;
class Material;

namespace TransformToDomain
{
BA_CORE_API_ std::unique_ptr<Material> createDomainMaterial(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<IParticle> createIParticle(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<Layer> createLayer(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<LayerRoughness> createLayerRoughness(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<MultiLayer> createMultiLayer(const SessionItem& item);
BA_CORE_API_ std::unique_ptr<ParticleDistribution> createParticleDistribution(
    const SessionItem& item);
BA_CORE_API_ std::unique_ptr<ParticleLayout> createParticleLayout(const SessionItem& item);

BA_CORE_API_ void addDistributionParametersToSimulation(
    const SessionItem& beam_item, GISASSimulation* simulation);
BA_CORE_API_ void setSimulationOptions(GISASSimulation* simulation, const SessionItem& item);
BA_CORE_API_ void setTransformationInfo(IParticle* result, const SessionItem& item);
BA_CORE_API_ void setPositionInfo(IParticle* result, const SessionItem& item);
BA_CORE_API_ void setRotationInfo(IParticle* result, const SessionItem& item);
}

#endif // TRANSFORMTODOMAIN_H
