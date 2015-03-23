// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/SampleLabelHandler.cpp
//! @brief     Implement class SampleLabelHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include "SampleLabelHandler.h"
#include "ParticleCoreShell.h"
#include "ParticleComposition.h"

SampleLabelHandler::SampleLabelHandler()
{
}

std::string SampleLabelHandler::getLabel(const IFormFactor *sample)
{
    return m_FormFactorLabel[sample];
}

std::string SampleLabelHandler::getLabel(const IInterferenceFunction *sample)
{
    return m_InterferenceFunctionLabel[sample];
}

std::string SampleLabelHandler::getLabel(const IMaterial *sample)
{
    return m_MaterialLabel[sample];
}

std::string SampleLabelHandler::getLabel(const Layer *sample)
{
    return m_LayerLabel[sample];
}

std::string SampleLabelHandler::getLabel(const LayerRoughness *sample)
{
    return m_LayerRoughnessLabel[sample];
}

std::string SampleLabelHandler::getLabel(const MultiLayer *sample)
{
    return m_MultiLayerLabel[sample];
}

std::string SampleLabelHandler::getLabel(const IParticle *sample)
{
    if (const ParticleCoreShell *core_shell_particle =
            dynamic_cast<const ParticleCoreShell*>(sample))
        return m_ParticleCoreShellLabel[core_shell_particle];
    if (const Particle *particle = dynamic_cast<const Particle*>(sample))
        return m_ParticleLabel[particle];
    if (const ParticleComposition *lattice_basis = dynamic_cast<const ParticleComposition*>(sample))
        return m_ParticleCompositionLabel[lattice_basis];
    throw Exceptions::NotImplementedException("LabelSample::getLabel: called"
                                              " for unknown IParticle type");
}

std::string SampleLabelHandler::getLabel(const ParticleCoreShell *sample)
{
    return m_ParticleCoreShellLabel[sample];
}

std::string SampleLabelHandler::getLabel(const ILayout *sample)
{
    return m_ILayoutLabel[sample];
}

std::string SampleLabelHandler::getLabel(const ParticleComposition *sample)
{
    return m_ParticleCompositionLabel[sample];
}

std::map<const IFormFactor *,std::string>* SampleLabelHandler::getFormFactorMap()
{
    return &m_FormFactorLabel;
}

std::map<const IInterferenceFunction *,std::string>* SampleLabelHandler::getInterferenceFunctionMap()
{
    return &m_InterferenceFunctionLabel;
}

std::map<const Layer *,std::string>* SampleLabelHandler::getLayerMap()
{
    return &m_LayerLabel;
}

std::map<const LayerRoughness *,std::string>* SampleLabelHandler::getLayerRoughnessMap()
{
    return &m_LayerRoughnessLabel;
}

std::map<const IMaterial*, std::string>* SampleLabelHandler::getMaterialMap()
{
    return &m_MaterialLabel;
}

std::map<const MultiLayer *,std::string>* SampleLabelHandler::getMultiLayerMap()
{
    return &m_MultiLayerLabel;
}

std::map<const Particle *,std::string>* SampleLabelHandler::getParticleMap()
{
    return &m_ParticleLabel;
}

std::map<const ParticleCoreShell *,std::string>* SampleLabelHandler::getParticleCoreShellMap()
{
    return &m_ParticleCoreShellLabel;
}

std::map<const ILayout *,std::string>* SampleLabelHandler::getParticleLayoutMap()
{
    return &m_ILayoutLabel;
}

std::map<const ParticleComposition *, std::string> *SampleLabelHandler::getParticleCompositionMap()
{
    return &m_ParticleCompositionLabel;
}

void SampleLabelHandler::insertMaterial(const IMaterial *sample)
{
    std::map<const IMaterial *,std::string>::iterator it = m_MaterialLabel.begin();
    std::map<const IMaterial *,std::string>::const_iterator iEnd = m_MaterialLabel.end();
    while (it != iEnd)
    {
        if(definesSameMaterial(it->first, sample) )
        {
            m_MaterialLabel[sample] = it->second;
            break;
        }
        it++;
    }
    if(it == iEnd)
    {
        std::ostringstream label_stream;
        label_stream << "material_" << m_MaterialLabel.size()+1;
        m_MaterialLabel[sample] = label_stream.str();
    }
}

void SampleLabelHandler::setLabel(const IFormFactor *sample)
{
        std::ostringstream inter;
        inter << "formFactor_" << m_FormFactorLabel.size()+1;
        m_FormFactorLabel[sample] = inter.str();
}

void SampleLabelHandler::setLabel(const IInterferenceFunction *sample)
{
    std::ostringstream inter;
    inter << "interference_" << m_InterferenceFunctionLabel.size()+1;
    m_InterferenceFunctionLabel[sample] = inter.str();
}

void SampleLabelHandler::setLabel(const ILayout *sample)
{
    std::ostringstream inter;
    inter << "layout_" << m_ILayoutLabel.size()+1;
    m_ILayoutLabel[sample] = inter.str();;
}

void SampleLabelHandler::setLabel(const Layer *sample)
{
    std::ostringstream inter;
    inter << "layer_" << m_LayerLabel.size()+1;
    m_LayerLabel[sample] = inter.str();
}

void SampleLabelHandler::setLabel(const LayerRoughness *sample)
{
    if(sample->getSigma() != 0 && sample->getHurstParameter() != 0 && sample->getLatteralCorrLength() != 0)
    {
        std::ostringstream inter;
        inter << "layerRoughness_" << m_LayerRoughnessLabel.size()+1;
        m_LayerRoughnessLabel[sample] = inter.str();
    }
}

void SampleLabelHandler::setLabel(const MultiLayer *sample)
{
    std::ostringstream inter;
    inter << "multiLayer_" << m_MultiLayerLabel.size()+1;
    m_MultiLayerLabel[sample] = inter.str();
}

void SampleLabelHandler::setLabel(const Particle *sample)
{
    std::ostringstream inter;
    inter << "particle_" << m_ParticleLabel.size()+1;
    m_ParticleLabel[sample] = inter.str();
}

void SampleLabelHandler::setLabel(const ParticleCoreShell *sample)
{
    std::ostringstream inter;
    inter << "particleCoreShell_" << m_ParticleCoreShellLabel.size()+1;
    m_ParticleCoreShellLabel[sample] = inter.str();
}

void SampleLabelHandler::setLabel(const ParticleComposition *sample)
{
    std::ostringstream inter;
    inter << "particleComposition_" << m_ParticleCompositionLabel.size()+1;
    m_ParticleCompositionLabel[sample] = inter.str();
}


bool SampleLabelHandler::definesSameMaterial(const IMaterial *left, const IMaterial *right) const
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
