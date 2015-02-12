// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/LabelSample.cpp
//! @brief     Implement class LabelSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include "LabelSample.h"
#include "ParticleCoreShell.h"

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

std::string LabelSample::getLabel(const IParticle *sample)
{
    if (const ParticleCoreShell *pcs = dynamic_cast<const ParticleCoreShell*>(sample))
        return m_particleCoreShellLabel[pcs];
    if (const Particle *p = dynamic_cast<const Particle*>(sample))
        return m_particleLabel[p];
    throw Exceptions::NotImplementedException("LabelSample::getLabel: called"
                                              " for unknown IParticle type");
}

std::string LabelSample::getLabel(const ParticleCoreShell *sample)
{
    return m_particleCoreShellLabel[sample];
}

std::string LabelSample::getLabel(const ParticleInfo *sample)
{
    return m_particleInfoLabel[sample];
}

std::string LabelSample::getLabel(const ILayout *sample)
{
    return m_ILayoutLabel[sample];
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

std::map<const ParticleCoreShell *,std::string>* LabelSample::getParticleCoreShellMap()
{
    return &m_particleCoreShellLabel;
}

std::map<const ParticleInfo *,std::string>* LabelSample::getParticleInfoMap()
{
    return &m_particleInfoLabel;
}

std::map<const ILayout *,std::string>* LabelSample::getParticleLayoutMap()
{
    return &m_ILayoutLabel;
}

void LabelSample::insertMaterial(const IMaterial *sample)
{
    std::map<const IMaterial *,std::string>::iterator it = m_materialLabel.begin();
    std::map<const IMaterial *,std::string>::const_iterator iEnd = m_materialLabel.end();
    while (it != iEnd)
    {
        if(definesSameMaterial(it->first, sample) )
        {
            m_materialLabel[sample] = it->second;
            break;
        }
        it++;
    }
    if(it == iEnd)
    {
        std::ostringstream label_stream;
        label_stream << "Material_" << m_materialLabel.size()+1;
        m_materialLabel[sample] = label_stream.str();
    }
}

void LabelSample::setLabel(const IFormFactor *sample)
{
        std::ostringstream inter;
        inter << "FormFactor_" << m_formFactorLabel.size()+1;
        m_formFactorLabel[sample] = inter.str();
}

void LabelSample::setLabel(const IInterferenceFunction *sample)
{
    std::ostringstream inter;
    inter << "InterferenceFunction_" << m_interferenceFunctionLabel.size()+1;
    m_interferenceFunctionLabel[sample] = inter.str();
}

void LabelSample::setLabel(const ILayout *sample)
{
    std::ostringstream inter;
    inter << "Layout_" << m_ILayoutLabel.size()+1;
    m_ILayoutLabel[sample] = inter.str();;
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

void LabelSample::setLabel(const ParticleCoreShell *sample)
{
    std::ostringstream inter;
    inter << "ParticleCoreShell_" << m_particleCoreShellLabel.size()+1;
    m_particleCoreShellLabel[sample] = inter.str();;
}


void LabelSample::setLabel(const ParticleInfo *sample)
{
    std::ostringstream inter;
    inter << "ParticleInfo_" << m_particleInfoLabel.size()+1;
    m_particleInfoLabel[sample] = inter.str();;
}

bool LabelSample::definesSameMaterial(const IMaterial *left, const IMaterial *right) const
{
    // Non-magnetic materials
    if (left->isScalarMaterial() && right->isScalarMaterial()) {
        if (left->getName() == right->getName() &&
            left->getRefractiveIndex() == right->getRefractiveIndex() ) {
            return true;
        }
        return false;
    }
    // Magnetic materials TODO
    else if (!left->isScalarMaterial() && !right->isScalarMaterial()) {
        const HomogeneousMagneticMaterial *p_left =
                dynamic_cast<const HomogeneousMagneticMaterial *>(left);
        const HomogeneousMagneticMaterial *p_right =
                dynamic_cast<const HomogeneousMagneticMaterial *>(right);
        if (!p_left || !p_right) {
            throw Exceptions::RuntimeErrorException("LabelSample::definesSameMaterial: "
                                                    "non-scalar materials should be of type "
                                                    "HomogeneousMagneticMaterial");
        }
        if (p_left->getName() == p_right->getName() &&
            p_left->getRefractiveIndex() == p_right->getRefractiveIndex() &&
            p_left->getMagneticField() == p_right->getMagneticField() ) {
            return true;
        }
        return false;
    }
    // Return false if one material is magnetic and the other one not
    else return false;
}
