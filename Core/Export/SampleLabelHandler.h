// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.h
//! @brief     Defines classes LabelMap and SampleLabelHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLELABELHANDLER_H
#define SAMPLELABELHANDLER_H

#include "Exceptions.h"
#include "OrderedMap.h"
#include <map>

class IAbstractParticle;
class IFormFactor;
class IInterferenceFunction;
class ILayout;
class HomogeneousMaterial;
class IRotation;
class Layer;
class LayerRoughness;
class MultiLayer;
class Particle;
class ParticleComposition;
class ParticleCoreShell;
class ParticleDistribution;

template<class Key>
class LabelMap : public OrderedMap<Key, std::string>
{
};


//! The handler which construct labels for sample variables during python script generation.
//! @ingroup tools_internal

class BA_CORE_API_ SampleLabelHandler
{
public:
    typedef LabelMap<const IFormFactor*> formfactors_t;
    typedef LabelMap<const IInterferenceFunction*> interferences_t;
    typedef LabelMap<const ILayout*> layouts_t;
    typedef LabelMap<const HomogeneousMaterial*> materials_t;
    typedef LabelMap<const IRotation*> rotations_t;
    typedef LabelMap<const Layer*> layers_t;
    typedef LabelMap<const LayerRoughness*> roughnesses_t;
    typedef LabelMap<const MultiLayer*> multilayers_t;
    typedef LabelMap<const Particle*> particles_t;
    typedef LabelMap<const ParticleComposition*> particlecompositions_t;
    typedef LabelMap<const ParticleCoreShell*> particlescoreshell_t;
    typedef LabelMap<const ParticleDistribution*> particledistributions_t;

    SampleLabelHandler() {}
    formfactors_t* getFormFactorMap() { return &m_FormFactorLabel; }
    interferences_t* getInterferenceFunctionMap() { return &m_InterferenceFunctionLabel; }
    layers_t* getLayerMap() { return &m_LayerLabel; }
    layouts_t* getParticleLayoutMap() { return &m_ILayoutLabel; }
    materials_t* getMaterialMap() { return &m_MaterialLabel; }
    multilayers_t* getMultiLayerMap() { return &m_MultiLayerLabel; }
    particlecompositions_t* getParticleCompositionMap() { return &m_ParticleCompositionLabel; }
    particledistributions_t* getParticleDistributionsMap() { return &m_ParticleDistributionLabel; }
    particles_t* getParticleMap() { return &m_ParticleLabel; }
    particlescoreshell_t* getParticleCoreShellMap() { return &m_ParticleCoreShellLabel; }
    rotations_t* getRotationsMap() { return &m_RotationsLabel; }
    roughnesses_t* getLayerRoughnessMap() { return &m_LayerRoughnessLabel; }

    std::string getLabelParticle(const IAbstractParticle* sample);
    std::string getLabelFormFactor(const IFormFactor* sample);
    std::string getLabelInterferenceFunction(const IInterferenceFunction* sample);
    std::string getLabelLayout(const ILayout* sample);
    std::string getLabelMaterial(const HomogeneousMaterial* sample);
    std::string getLabelRotation(const IRotation* sample);
    std::string getLabelLayer(const Layer* sample);
    std::string getLabelRoughness(const LayerRoughness* sample);
    std::string getLabelMultiLayer(const MultiLayer* sample);
    std::string getLabelParticleComposition(const ParticleComposition* sample);
    std::string getLabelParticleCoreShell(const ParticleCoreShell* sample);
    std::string getLabelParticleDistribution(const ParticleDistribution* sample);

    void insertMaterial(const HomogeneousMaterial* sample);
    void insertFormFactor(const IFormFactor* sample);
    void insertInterferenceFunction(const IInterferenceFunction* sample);
    void insertLayout(const ILayout* sample);
    void insertRotation(const IRotation* sample);
    void insertLayer(const Layer* sample);
    void insertRoughness(const LayerRoughness* sample);
    void insertMultiLayer(const MultiLayer* sample);
    void insertParticle(const Particle* sample);
    void insertParticleComposition(const ParticleComposition* sample);
    void insertParticleCoreShell(const ParticleCoreShell* sample);
    void insertParticleDistribution(const ParticleDistribution* sample);

private:
    formfactors_t m_FormFactorLabel;
    interferences_t m_InterferenceFunctionLabel;
    layers_t m_LayerLabel;
    layouts_t m_ILayoutLabel;
    materials_t m_MaterialLabel;
    multilayers_t m_MultiLayerLabel;
    particlecompositions_t m_ParticleCompositionLabel;
    particledistributions_t m_ParticleDistributionLabel;
    particles_t m_ParticleLabel;
    particlescoreshell_t m_ParticleCoreShellLabel;
    rotations_t m_RotationsLabel;
    roughnesses_t m_LayerRoughnessLabel;
};

#endif // SAMPLELABELHANDLER_H
