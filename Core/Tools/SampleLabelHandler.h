// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SampleLabelHandler.h
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

#include "WinDllMacros.h"
#include "Utils.h"
#include <map>

class IFormFactor;
class IInterferenceFunction;
class Layer;
class MultiLayer;
class LayerRoughness;
class IMaterial;
class Particle;
class IAbstractParticle;
class ParticleCoreShell;
class ParticleDistribution;
class ILayout;
class ParticleComposition;
class IRotation;

//! @class SampleLabelHandler
//! @ingroup tools_internal
//! @brief The hadler which construct labels for sample variables during python script generation

class BA_CORE_API_ SampleLabelHandler
{
public:
    typedef Utils::OrderedMap<const IFormFactor*, std::string> formfactors_t;
    typedef Utils::OrderedMap<const IInterferenceFunction*, std::string> interferences_t;
    typedef Utils::OrderedMap<const Layer*, std::string> layers_t;
    typedef Utils::OrderedMap<const LayerRoughness*, std::string> roughnesses_t;
    typedef Utils::OrderedMap<const IMaterial*, std::string> materials_t;
    typedef Utils::OrderedMap<const MultiLayer*, std::string> multilayers_t;
    typedef Utils::OrderedMap<const Particle*, std::string> particles_t;
    typedef Utils::OrderedMap<const ParticleCoreShell*, std::string> particlescoreshell_t;
    typedef Utils::OrderedMap<const ParticleDistribution*, std::string> particledistributions_t;
    typedef Utils::OrderedMap<const ILayout*, std::string> layouts_t;
    typedef Utils::OrderedMap<const ParticleComposition*, std::string> particlecompositions_t;
    typedef Utils::OrderedMap<const IRotation*, std::string> rotations_t;

    SampleLabelHandler();
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

    std::string getLabel(const IFormFactor *sample);
    std::string getLabel(const IInterferenceFunction *sample);
    std::string getLabel(const IMaterial *sample);
    std::string getLabel(const Layer *sample);
    std::string getLabel(const LayerRoughness *sample);
    std::string getLabel(const MultiLayer *sample);
    std::string getLabel(const IAbstractParticle *sample);
    std::string getLabel(const ParticleCoreShell *sample);
    std::string getLabel(const ParticleDistribution *sample);
    std::string getLabel(const ILayout *sample);
    std::string getLabel(const ParticleComposition *sample);
    std::string getLabel(const IRotation *sample);

    void insertMaterial(const IMaterial *sample);
    void setLabel(const IFormFactor *sample);
    void setLabel(const IInterferenceFunction *sample);
    void setLabel(const ILayout *sample);
    void setLabel(const Layer *sample);
    void setLabel(const LayerRoughness *sample);
    void setLabel(const MultiLayer *sample);
    void setLabel(const Particle *sample);
    void setLabel(const ParticleCoreShell *sample);
    void setLabel(const ParticleDistribution *sample);
    void setLabel(const ParticleComposition *sample);
    void setLabel(const IRotation *sample);


private:
    bool definesSameMaterial(const IMaterial *left, const IMaterial *right) const;
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

#endif // LABELSAMPLE_H
