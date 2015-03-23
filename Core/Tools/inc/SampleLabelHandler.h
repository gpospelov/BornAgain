// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/SampleLabelHandler.h
//! @brief     Defines SampleLabelHandler class
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
#include <map>
#include "MultiLayer.h"
#include "Layer.h"
#include "IParticle.h"
#include "ParticleLayout.h"

//static std::map<const Layer *,std::string> m_layerLabel;

class BA_CORE_API_ SampleLabelHandler
{
public:
    SampleLabelHandler();
    std::map<const IFormFactor*, std::string>* getFormFactorMap();
    std::map<const IInterferenceFunction*, std::string>* getInterferenceFunctionMap();
    std::map<const Layer*, std::string>* getLayerMap();
    std::map<const LayerRoughness*, std::string>* getLayerRoughnessMap();
    std::map<const IMaterial*, std::string>* getMaterialMap();
    std::map<const MultiLayer*, std::string>* getMultiLayerMap();
    std::map<const Particle*, std::string>* getParticleMap();
    std::map<const ParticleCoreShell*, std::string>* getParticleCoreShellMap();
    std::map<const ILayout*, std::string>* getParticleLayoutMap();
    std::map<const ParticleComposition*, std::string>* getParticleCompositionMap();
    std::string getLabel(const IFormFactor *sample);
    std::string getLabel(const IInterferenceFunction *sample);
    std::string getLabel(const IMaterial *sample);
    std::string getLabel(const Layer *sample);
    std::string getLabel(const LayerRoughness *sample);
    std::string getLabel(const MultiLayer *sample);
    std::string getLabel(const IParticle *sample);
    std::string getLabel(const ParticleCoreShell *sample);
    std::string getLabel(const ILayout *sample);
    std::string getLabel(const ParticleComposition *sample);
    void insertMaterial(const IMaterial *sample);
    void setLabel(const IFormFactor *sample);
    void setLabel(const IInterferenceFunction *sample);
    void setLabel(const ILayout *sample);
    void setLabel(const Layer *sample);
    void setLabel(const LayerRoughness *sample);
    void setLabel(const MultiLayer *sample);
    void setLabel(const Particle *sample);
    void setLabel(const ParticleCoreShell *sample);
    void setLabel(const ParticleComposition *sample);


private:
    bool definesSameMaterial(const IMaterial *left, const IMaterial *right) const;
    std::map<const IFormFactor*, std::string> m_FormFactorLabel;
    std::map<const IInterferenceFunction*, std::string> m_InterferenceFunctionLabel;
    std::map<const Layer*, std::string> m_LayerLabel;
    std::map<const LayerRoughness*, std::string> m_LayerRoughnessLabel;
    std::map<const IMaterial*, std::string> m_MaterialLabel;
    std::map<const MultiLayer*, std::string> m_MultiLayerLabel;
    std::map<const Particle*, std::string> m_ParticleLabel;
    std::map<const ParticleCoreShell*, std::string> m_ParticleCoreShellLabel;
    std::map<const ILayout*, std::string> m_ILayoutLabel;
    std::map<const ParticleComposition*, std::string> m_ParticleCompositionLabel;
};

#endif // LABELSAMPLE_H
