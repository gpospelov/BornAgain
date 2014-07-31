// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/DomainObjectBuilder.h
//! @brief     Defines class DomainObjectBuilder.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H

class ISample;
class Instrument;
class MultiLayer;
class Layer;
class ParticleLayout;
class Particle;
class IInterferenceFunction;
class Beam;
class ParticleCoreShell;
class ParameterizedItem;
class LayerRoughness;

class DomainObjectBuilder
{
public:
    explicit DomainObjectBuilder();
    ~DomainObjectBuilder();

    void buildItem(const ParameterizedItem &item);

    ISample *getSample() { return mp_sample; }
    Instrument *getInstrument() { return m_instrument; }

    MultiLayer *buildMultiLayer(const ParameterizedItem &item) const;
    Instrument *buildInstrument(const ParameterizedItem &item) const;

private:
    Layer *buildLayer(const ParameterizedItem &item) const;
    ParticleLayout *buildParticleLayout(const ParameterizedItem &item) const;
    Particle *buildParticle(const ParameterizedItem &item, double &depth, double &abundance) const;
    IInterferenceFunction *buildInterferenceFunction(const ParameterizedItem &item) const;
    Beam *buildBeam(const ParameterizedItem &item) const;
    ParticleCoreShell *buildParticleCoreShell(const ParameterizedItem &item, double &depth, double &abundance) const;

    ISample *mp_sample;
    Instrument *m_instrument;
};

#endif // DOMAINOBJECTBUILDER_H
