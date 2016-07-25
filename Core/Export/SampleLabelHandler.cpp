// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/SampleLabelHandler.cpp
//! @brief     Implement class SampleLabelHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleLabelHandler.h"
#include "HomogeneousMagneticMaterial.h"
#include "IInterferenceFunction.h"
#include "IMaterial.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"

std::string SampleLabelHandler::getLabelFormFactor(const IFormFactor* sample)
{
    return m_FormFactorLabel[sample];
}

std::string SampleLabelHandler::getLabelInterferenceFunction(const IInterferenceFunction* sample)
{
    return m_InterferenceFunctionLabel[sample];
}

std::string SampleLabelHandler::getLabelMaterial(const IMaterial* sample)
{
    return m_MaterialLabel[sample];
}

std::string SampleLabelHandler::getLabelLayer(const Layer* sample)
{
    return m_LayerLabel[sample];
}

std::string SampleLabelHandler::getLabelRoughness(const LayerRoughness* sample)
{
    return m_LayerRoughnessLabel[sample];
}

std::string SampleLabelHandler::getLabelMultiLayer(const MultiLayer* sample)
{
    return m_MultiLayerLabel[sample];
}

std::string SampleLabelHandler::getLabelParticle(const IAbstractParticle* sample)
{
    if (const ParticleCoreShell* core_shell_particle =
            dynamic_cast<const ParticleCoreShell*>(sample))
        return m_ParticleCoreShellLabel[core_shell_particle];
    if (const Particle* particle = dynamic_cast<const Particle*>(sample))
        return m_ParticleLabel[particle];
    if (const ParticleDistribution* particle = dynamic_cast<const ParticleDistribution*>(sample))
        return m_ParticleDistributionLabel[particle];

    if (const ParticleComposition* lattice_basis = dynamic_cast<const ParticleComposition*>(sample))
        return m_ParticleCompositionLabel[lattice_basis];
    throw Exceptions::NotImplementedException(
        "SampleLabelHandler::getLabel: called for unknown IParticle type");
}

std::string SampleLabelHandler::getLabelParticleCoreShell(const ParticleCoreShell* sample)
{
    return m_ParticleCoreShellLabel[sample];
}

std::string SampleLabelHandler::getLabelParticleDistribution(const ParticleDistribution* sample)
{
    return m_ParticleDistributionLabel[sample];
}

std::string SampleLabelHandler::getLabelLayout(const ILayout* sample)
{
    return m_ILayoutLabel[sample];
}

std::string SampleLabelHandler::getLabelParticleComposition(const ParticleComposition* sample)
{
    return m_ParticleCompositionLabel[sample];
}

std::string SampleLabelHandler::getLabelRotation(const IRotation* sample)
{
    return m_RotationsLabel[sample];
}

void SampleLabelHandler::insertMaterial(const IMaterial* sample)
{
    for (auto it=m_MaterialLabel.begin(); it!=m_MaterialLabel.end(); ++it) {
        if(pEqual(it->first, sample) ) {
            m_MaterialLabel.insert(sample, it->second);
            return;
        }
    }
    // material not found => create new label
    std::ostringstream label_stream;
    label_stream << "material_" << m_MaterialLabel.size()+1;
    m_MaterialLabel.insert(sample, label_stream.str());
}

void SampleLabelHandler::setLabel(const IFormFactor* sample)
{
    std::ostringstream inter;
    inter << "formFactor_" << m_FormFactorLabel.size()+1;
    m_FormFactorLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const IInterferenceFunction* sample)
{
    std::ostringstream inter;
    inter << "interference_" << m_InterferenceFunctionLabel.size()+1;
    m_InterferenceFunctionLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const ILayout* sample)
{
    std::ostringstream inter;
    inter << "layout_" << m_ILayoutLabel.size()+1;
    m_ILayoutLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const Layer* sample)
{
    std::ostringstream inter;
    inter << "layer_" << m_LayerLabel.size()+1;
    m_LayerLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const LayerRoughness* sample)
{
    if(sample->getSigma() != 0 &&
       sample->getHurstParameter() != 0 &&
       sample->getLatteralCorrLength() != 0) {
        std::ostringstream inter;
        inter << "layerRoughness_" << m_LayerRoughnessLabel.size()+1;
        m_LayerRoughnessLabel.insert(sample, inter.str());
    }
}

void SampleLabelHandler::setLabel(const MultiLayer* sample)
{
    std::ostringstream inter;
    inter << "multiLayer_" << m_MultiLayerLabel.size()+1;
    m_MultiLayerLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const Particle* sample)
{
    std::ostringstream inter;
    inter << "particle_" << m_ParticleLabel.size()+1;
    m_ParticleLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const ParticleCoreShell* sample)
{
    std::ostringstream inter;
    inter << "particleCoreShell_" << m_ParticleCoreShellLabel.size()+1;
    m_ParticleCoreShellLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const ParticleDistribution* sample)
{
    std::ostringstream inter;
    inter << "particleDistribution_" << m_ParticleDistributionLabel.size()+1;
    m_ParticleDistributionLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const ParticleComposition* sample)
{
    std::ostringstream inter;
    inter << "particleComposition_" << m_ParticleCompositionLabel.size()+1;
    m_ParticleCompositionLabel.insert(sample, inter.str());
}

void SampleLabelHandler::setLabel(const IRotation* sample)
{
    std::ostringstream inter;
    inter << "rotation_" << m_RotationsLabel.size()+1;
    m_RotationsLabel.insert(sample, inter.str());
}
