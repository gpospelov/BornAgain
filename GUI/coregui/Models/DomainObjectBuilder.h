// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/DomainObjectBuilder.h
//! @brief     Defines class DomainObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H

#include "WinDllMacros.h"
class ISample;
class Instrument;
class MultiLayer;
class Layer;
class ParticleLayout;
class Particle;
class IInterferenceFunction;
class Beam;
class ParticleCoreShell;
class ParticleDistribution;
class ParameterizedItem;
class LayerRoughness;

class BA_CORE_API_ DomainObjectBuilder
{
public:
    explicit DomainObjectBuilder(){}
    ~DomainObjectBuilder(){}

    MultiLayer *buildMultiLayer(const ParameterizedItem &multilayer_item) const;
    Instrument *buildInstrument(const ParameterizedItem &instrument_item) const;

private:
    Layer *buildLayer(const ParameterizedItem &item) const;
    ParticleLayout *buildParticleLayout(const ParameterizedItem &item) const;
    Particle *buildParticle(const ParameterizedItem &item, double &depth,
                            double &abundance) const;
    ParticleDistribution *buildParticleDistribution(
            const ParameterizedItem &item, double &depth,
            double &abundance) const;
    IInterferenceFunction *buildInterferenceFunction(
            const ParameterizedItem &item) const;
    Beam *buildBeam(const ParameterizedItem &item) const;
    ParticleCoreShell *buildParticleCoreShell(const ParameterizedItem &item,
                                     double &depth, double &abundance) const;
    void addParticleToLayout(ParticleLayout *result,
        ParameterizedItem *particle_item, double depth, double abundance,
        const Particle& particle) const;
};

#endif // DOMAINOBJECTBUILDER_H
