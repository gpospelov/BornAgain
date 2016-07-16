// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.h
//! @brief     Declares SampleLabelHandler class
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

#include "Utils.h"

//! @class SampleLabelHandler
//! @ingroup tools_internal
//! @brief The hadler which construct labels for sample variables during python script generation

class BA_CORE_API_ SampleLabelHandler
{
public:
    typedef Utils::OrderedMap<const class IFormFactor*, std::string> formfactors_t;
    typedef Utils::OrderedMap<const class IInterferenceFunction*, std::string> interferences_t;
    typedef Utils::OrderedMap<const class Layer*, std::string> layers_t;
    typedef Utils::OrderedMap<const class LayerRoughness*, std::string> roughnesses_t;
    typedef Utils::OrderedMap<const class IMaterial*, std::string> materials_t;
    typedef Utils::OrderedMap<const class MultiLayer*, std::string> multilayers_t;
    typedef Utils::OrderedMap<const class Particle*, std::string> particles_t;
    typedef Utils::OrderedMap<const class ParticleCoreShell*, std::string> particlescoreshell_t;
    typedef Utils::OrderedMap<const class ParticleDistribution*, std::string>
        particledistributions_t;
    typedef Utils::OrderedMap<const class ILayout*, std::string> layouts_t;
    typedef Utils::OrderedMap<const class ParticleComposition*, std::string> particlecompositions_t;
    typedef Utils::OrderedMap<const class IRotation*, std::string> rotations_t;

    SampleLabelHandler() {}
    formfactors_t* getFormFactorMap();
    interferences_t* getInterferenceFunctionMap();
    layers_t* getLayerMap();
    roughnesses_t* getLayerRoughnessMap();
    materials_t* getMaterialMap();
    multilayers_t* getMultiLayerMap();
    particles_t* getParticleMap();
    particlescoreshell_t* getParticleCoreShellMap();
    particledistributions_t* getParticleDistributionsMap();
    layouts_t* getParticleLayoutMap();
    particlecompositions_t* getParticleCompositionMap();
    rotations_t* getRotationsMap();

    std::string getLabel(const class IFormFactor* sample);
    std::string getLabel(const class IInterferenceFunction* sample);
    std::string getLabel(const class IMaterial* sample);
    std::string getLabel(const class Layer* sample);
    std::string getLabel(const class LayerRoughness* sample);
    std::string getLabel(const class MultiLayer* sample);
    std::string getLabel(const class IAbstractParticle* sample);
    std::string getLabel(const class ParticleCoreShell* sample);
    std::string getLabel(const class ParticleDistribution* sample);
    std::string getLabel(const class ILayout* sample);
    std::string getLabel(const class ParticleComposition* sample);
    std::string getLabel(const class IRotation* sample);

    void insertMaterial(const class IMaterial* sample);
    void setLabel(const class IFormFactor* sample);
    void setLabel(const class IInterferenceFunction* sample);
    void setLabel(const class ILayout* sample);
    void setLabel(const class Layer* sample);
    void setLabel(const class LayerRoughness* sample);
    void setLabel(const class MultiLayer* sample);
    void setLabel(const class Particle* sample);
    void setLabel(const class ParticleCoreShell* sample);
    void setLabel(const class ParticleDistribution* sample);
    void setLabel(const class ParticleComposition* sample);
    void setLabel(const class IRotation* sample);


private:
    bool definesSameMaterial(const class IMaterial* left, const class IMaterial* right) const;
    formfactors_t m_FormFactorLabel;
    interferences_t m_InterferenceFunctionLabel;
    layers_t m_LayerLabel;
    roughnesses_t m_LayerRoughnessLabel;
    materials_t m_MaterialLabel;
    multilayers_t m_MultiLayerLabel;
    particles_t m_ParticleLabel;
    particlescoreshell_t m_ParticleCoreShellLabel;
    particledistributions_t m_ParticleDistributionLabel;
    layouts_t m_ILayoutLabel;
    particlecompositions_t m_ParticleCompositionLabel;
    rotations_t m_RotationsLabel;
};

#endif // SAMPLELABELHANDLER_H
