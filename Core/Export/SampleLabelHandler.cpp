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
#include "IInterferenceFunction.h"
#include "HomogeneousMaterial.h"
#include "LayerRoughness.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include <set>

std::string SampleLabelHandler::labelFormFactor(const IFormFactor* ff)
{
    return m_FormFactorLabel[ff];
}

std::string SampleLabelHandler::labelInterferenceFunction(const IInterferenceFunction* iff)
{
    return m_InterferenceFunctionLabel[iff];
}

std::string SampleLabelHandler::labelMaterial(const HomogeneousMaterial* mat)
{
    return m_MaterialLabel[mat];
}

std::string SampleLabelHandler::labelLayer(const Layer* layer)
{
    return m_LayerLabel[layer];
}

std::string SampleLabelHandler::labelRoughness(const LayerRoughness* roughness)
{
    return m_LayerRoughnessLabel[roughness];
}

std::string SampleLabelHandler::labelMultiLayer(const MultiLayer* ml)
{
    return m_MultiLayerLabel[ml];
}

std::string SampleLabelHandler::labelParticle(const IAbstractParticle* absparticle)
{
    if (const auto core_shell_particle = dynamic_cast<const ParticleCoreShell*>(absparticle))
        return m_ParticleCoreShellLabel[core_shell_particle];
    if (const auto particle = dynamic_cast<const Particle*>(absparticle))
        return m_ParticleLabel[particle];
    if (const auto particle = dynamic_cast<const ParticleDistribution*>(absparticle))
        return m_ParticleDistributionLabel[particle];
    if (const auto lattice_basis = dynamic_cast<const ParticleComposition*>(absparticle))
        return m_ParticleCompositionLabel[lattice_basis];
    throw Exceptions::NotImplementedException(
        "SampleLabelHandler::getLabel: called for unknown IParticle type");
}

std::string SampleLabelHandler::labelParticleCoreShell(const ParticleCoreShell* pcs)
{
    return m_ParticleCoreShellLabel[pcs];
}

std::string SampleLabelHandler::labelParticleDistribution(const ParticleDistribution* pd)
{
    return m_ParticleDistributionLabel[pd];
}

std::string SampleLabelHandler::labelLayout(const ILayout* layout)
{
    return m_ILayoutLabel[layout];
}

std::string SampleLabelHandler::labelParticleComposition(const ParticleComposition* pc)
{
    return m_ParticleCompositionLabel[pc];
}

std::string SampleLabelHandler::labelRotation(const IRotation* rot)
{
    return m_RotationsLabel[rot];
}

void SampleLabelHandler::insertMaterial(const HomogeneousMaterial* mat)
{
    for (auto it=m_MaterialLabel.begin(); it!=m_MaterialLabel.end(); ++it) {
        if( *(it->first) == *mat ) {
            m_MaterialLabel.insert(mat, it->second);
            return;
        }
    }
    // material not found => create new label
    std::set<std::string> unique_labels;
    for (auto it=m_MaterialLabel.begin(); it!=m_MaterialLabel.end(); ++it)
        unique_labels.insert(it->second);

    std::string label = "material_" + std::to_string(unique_labels.size()+1);
    m_MaterialLabel.insert(mat, label);
}

void SampleLabelHandler::insertFormFactor(const IFormFactor* sample)
{
    std::string label = "formFactor_" + std::to_string(m_FormFactorLabel.size()+1);
    m_FormFactorLabel.insert(sample, label);
}

void SampleLabelHandler::insertInterferenceFunction(const IInterferenceFunction* sample)
{
    std::string label = "interference_" + std::to_string(m_InterferenceFunctionLabel.size()+1);
    m_InterferenceFunctionLabel.insert(sample, label);
}

void SampleLabelHandler::insertLayout(const ILayout* sample)
{
    std::string label = "layout_" + std::to_string(m_ILayoutLabel.size()+1);
    m_ILayoutLabel.insert(sample, label);
}

void SampleLabelHandler::insertLayer(const Layer* sample)
{
    std::string label = "layer_" + std::to_string(m_LayerLabel.size()+1);
    m_LayerLabel.insert(sample, label);
}

void SampleLabelHandler::insertRoughness(const LayerRoughness* sample)
{
    if (sample->getSigma() != 0 &&
        sample->getHurstParameter() != 0 &&
        sample->getLatteralCorrLength() != 0) {
        std::string label = "layerRoughness_" + std::to_string(m_LayerRoughnessLabel.size()+1);
        m_LayerRoughnessLabel.insert(sample, label);
    }
}

void SampleLabelHandler::insertMultiLayer(const MultiLayer* sample)
{
    std::string label = "multiLayer_" + std::to_string(m_MultiLayerLabel.size()+1);
    m_MultiLayerLabel.insert(sample, label);
}

void SampleLabelHandler::insertParticle(const Particle* sample)
{
    std::string label = "particle_" + std::to_string(m_ParticleLabel.size()+1);
    m_ParticleLabel.insert(sample, label);
}

void SampleLabelHandler::insertParticleCoreShell(const ParticleCoreShell* sample)
{
    std::string label = "particleCoreShell_" + std::to_string(m_ParticleCoreShellLabel.size()+1);
    m_ParticleCoreShellLabel.insert(sample, label);
}

void SampleLabelHandler::insertParticleDistribution(const ParticleDistribution* sample)
{
    std::string label = "particleDistribution_" +
            std::to_string(m_ParticleDistributionLabel.size()+1);
    m_ParticleDistributionLabel.insert(sample, label);
}

void SampleLabelHandler::insertParticleComposition(const ParticleComposition* sample)
{
    std::string label = "particleComposition_" +
            std::to_string(m_ParticleCompositionLabel.size()+1);
    m_ParticleCompositionLabel.insert(sample, label);
}

void SampleLabelHandler::insertRotation(const IRotation* sample)
{
    std::string label = "rotation_" + std::to_string(m_RotationsLabel.size()+1);
    m_RotationsLabel.insert(sample, label);
}
