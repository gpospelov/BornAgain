#include <iostream>
#include "LabelSample.h"

LabelSample::LabelSample()
{

}

std::string LabelSample::getLabel(const IFormFactor *sample)
{
    return m_formFactorLabel[sample];
}

std::string LabelSample::getLabel(const IInterferenceFunction *sample)
{
    return m_interferenceFunctionLabel[sample];
}

std::string LabelSample::getLabel(const IMaterial *sample)
{
    return m_materialLabel[sample];
}

std::string LabelSample::getLabel(const Layer *sample)
{
    return m_layerLabel[sample];
}

std::string LabelSample::getLabel(const LayerRoughness *sample)
{
    return m_layerRoughnessLabel[sample];
}

std::string LabelSample::getLabel(const MultiLayer *sample)
{
    return m_multiLayerLabel[sample];
}

std::string LabelSample::getLabel(const Particle *sample)
{
    return m_particleLabel[sample];
}

std::string LabelSample::getLabel(const ParticleInfo *sample)
{
    return m_particleInfoLabel[sample];
}

std::string LabelSample::getLabel(const ILayout *sample)
{
    return m_particleLayoutLabel[sample];
}

std::map<const IFormFactor *,std::string>* LabelSample::getFormFactorMap()
{
    return &m_formFactorLabel;
}

std::map<const IInterferenceFunction *,std::string>* LabelSample::getInterferenceFunctionMap()
{
    return &m_interferenceFunctionLabel;
}

std::map<const Layer *,std::string>* LabelSample::getLayerMap()
{
    return &m_layerLabel;
}

std::map<const LayerRoughness *,std::string>* LabelSample::getLayerRoughnessMap()
{
    return &m_layerRoughnessLabel;
}

std::map<const IMaterial*, std::string>* LabelSample::getMaterialMap()
{
    return &m_materialLabel;
}

std::map<const MultiLayer *,std::string>* LabelSample::getMultiLayerMap()
{
    return &m_multiLayerLabel;
}

std::map<const Particle *,std::string>* LabelSample::getParticleMap()
{
    return &m_particleLabel;
}

std::map<const ParticleInfo *,std::string>* LabelSample::getParticleInfoMap()
{
    return &m_particleInfoLabel;
}

std::map<const ILayout *,std::string>* LabelSample::getParticleLayoutMap()
{
    return &m_particleLayoutLabel;
}

std::set<const Particle *>* LabelSample::getStochasticallyGeneratedParticle()
{
    return &StochasticallyGeneratedParticle;
}

void LabelSample::insertMaterial(const IMaterial *sample)
{
    std::map<const IMaterial *,std::string>::iterator it = m_materialLabel.begin();
    std::map<const IMaterial *,std::string>::const_iterator iEnd = m_materialLabel.end();
    while (it != iEnd)
    {
        if(it->first->getName() == sample->getName() &&
                it->first->getRefractiveIndex() == sample->getRefractiveIndex() )
        {
            m_materialLabel[sample] = it->second;
            break;
        }
        it++;
    }
    if(it == iEnd)
    {
        std::ostringstream inter;
        inter << "Material_" << m_materialLabel.size()+1;
        m_materialLabel[sample] = inter.str();
    }
}

void LabelSample::insertStochasticallyGeneratedParticle(const Particle *sample)
{
    StochasticallyGeneratedParticle.insert(sample);
}

void LabelSample::setLabel(const IFormFactor *sample)
{
//    if (StochasticallyGeneratedParticle.getSimpleFormFactor()->find(sample) ==  StochasticallyGeneratedParticle.getSimpleFormFactor()->end())
    {
        std::ostringstream inter;
        inter << "FormFactor_" << m_formFactorLabel.size()+1;
        m_formFactorLabel[sample] = inter.str();
    }
}

void LabelSample::setLabel(const IInterferenceFunction *sample)
{
    std::ostringstream inter;
    inter << "InterferenceFunction_" << m_interferenceFunctionLabel.size()+1;
    m_interferenceFunctionLabel[sample] = inter.str();
}

void LabelSample::setLabel(const Layer *sample)
{
    std::ostringstream inter;
    inter << "Layer_" << m_layerLabel.size()+1;
    m_layerLabel[sample] = inter.str();
}

void LabelSample::setLabel(const LayerRoughness *sample)
{
    if(sample->getSigma() != 0 && sample->getHurstParameter() != 0 && sample->getLatteralCorrLength() != 0)
    {
        std::ostringstream inter;
        inter << "LayerRoughness_" << m_layerRoughnessLabel.size()+1;
        m_layerRoughnessLabel[sample] = inter.str();
    }
}

void LabelSample::setLabel(const MultiLayer *sample)
{
    std::ostringstream inter;
    inter << "MultiLayer_" << m_multiLayerLabel.size()+1;
    m_multiLayerLabel[sample] = inter.str();;
}

void LabelSample::setLabel(const Particle *sample)
{
    std::ostringstream inter;
    inter << "Particle_" << m_particleLabel.size()+1;
    m_particleLabel[sample] = inter.str();;
}

void LabelSample::setLabel(const ParticleInfo *sample)
{
    std::ostringstream inter;
    inter << "ParticleInfo_" << m_particleInfoLabel.size()+1;
    m_particleInfoLabel[sample] = inter.str();;
}

void LabelSample::setLabel(const ILayout *sample)
{
    std::ostringstream inter;
    inter << "ParticleLayout_" << m_particleLayoutLabel.size()+1;
    m_particleLayoutLabel[sample] = inter.str();;
}
