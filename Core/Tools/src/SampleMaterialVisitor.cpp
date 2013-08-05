// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      SampleMaterialVisitor.cpp
//! @brief     Implements class SampleMaterialVisitor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleMaterialVisitor.h"

#include <algorithm>

SampleMaterialVisitor::SampleMaterialVisitor()
{
    m_materials.clear();
}

SampleMaterialVisitor::~SampleMaterialVisitor()
{
    m_materials.clear();
}

void SampleMaterialVisitor::visit(const ISample* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::visit(ISample *)");
}

void SampleMaterialVisitor::visit(const MultiLayer* sample)
{
    assert(sample);

    for(size_t i_layer=0; i_layer < sample->getNumberOfLayers(); ++i_layer) {
        const Layer *layer = sample->getLayer(i_layer);
        layer->accept(this);
    }
}

void SampleMaterialVisitor::visit(const Layer* sample)
{
    assert(sample);

    IMaterial *p_material = sample->getMaterial();
    addMaterial(p_material);
    const IDecoration *p_decoration = sample->getDecoration();
    if (p_decoration) {
        p_decoration->accept(this);
    }
}

void SampleMaterialVisitor::visit(const LayerInterface* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::visit(LayerInterface *)");
}

void SampleMaterialVisitor::visit(const ParticleDecoration* sample)
{
    assert(sample);

    for (size_t i=0; i<sample->getNumberOfParticles(); ++i) {
        const ParticleInfo *p_particle_info = sample->getParticleInfo(i);
        p_particle_info->accept(this);
    }
}

void SampleMaterialVisitor::visit(const ParticleInfo* sample)
{
    assert(sample);

    const Particle *p_particle = sample->getParticle();
    if (p_particle) {
        p_particle->accept(this);
    }
}

void SampleMaterialVisitor::visit(const Particle* sample)
{
    assert(sample);

    const IMaterial *p_material = sample->getMaterial();
    addMaterial(p_material);
}

void SampleMaterialVisitor::visit(const IFormFactor* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(IFormFactor *)");
}

void SampleMaterialVisitor::visit(const FormFactorFullSphere* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(FormFactorFullSphere *)");
}

void SampleMaterialVisitor::visit(const FormFactorPyramid* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(FormFactorPyramid *)");
}

void SampleMaterialVisitor::visit(const FormFactorCylinder* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(FormFactorCylinder *)");
}

void SampleMaterialVisitor::visit(const FormFactorPrism3* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(FormFactorPrism3 *)");
}

void SampleMaterialVisitor::visit(const IInterferenceFunction* sample)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(IInterferenceFunction *)");
}

void SampleMaterialVisitor::visit(const InterferenceFunction1DParaCrystal*)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(IInterferenceFunction *)");
}

void SampleMaterialVisitor::visit(const InterferenceFunction2DParaCrystal*)
{
    throw NotImplementedException("SampleMaterialVisitor::"
            "visit(InterferenceFunction2DParaCrystal *)");
}

void SampleMaterialVisitor::addMaterial(const IMaterial* p_material)
{
    if (std::find(m_materials.begin(), m_materials.end(), p_material) !=
            m_materials.end() ) {
        m_materials.push_back(p_material);
    }
}
