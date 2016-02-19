// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/SampleMaterialVisitor.cpp
//! @brief     Implements class SampleMaterialVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleMaterialVisitor.h"
#include "IMaterial.h"
#include "Layer.h"
#include "Particle.h"
#include "ParticleComposition.h"


void SampleMaterialVisitor::clear()
{
    m_materials.clear();
}


void SampleMaterialVisitor::addMaterial(const IMaterial* p_material)
{
    if (p_material && std::find(m_materials.begin(), m_materials.end(),
            p_material) == m_materials.end() ) {
        m_materials.push_back(p_material);
    }
}


bool SampleMaterialVisitor::containsMagneticMaterial() const {
    for (std::vector<const IMaterial *>::const_iterator it = m_materials.begin();
            it != m_materials.end(); ++it) {
        if(!(*it)) throw DomainErrorException("SampleMaterialVisitor::"
                             "containsMagneticMaterial() -> Error.");
        if (!(*it)->isScalarMaterial()) return true;
    }
    return false;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void SampleMaterialVisitor::visit(const ISample *)
{
}

void SampleMaterialVisitor::visit(const ICompositeSample *)
{
}

void SampleMaterialVisitor::visit(const IClusteredParticles *)
{
}

void SampleMaterialVisitor::visit(const Crystal *)
{
}

void SampleMaterialVisitor::visit(const ILayout *)
{
}

void SampleMaterialVisitor::visit(const ParticleLayout *)
{
}

void SampleMaterialVisitor::visit(const Layer *sample)
{
    assert(sample);
    const IMaterial *material = sample->getMaterial();
    addMaterial(material);
}

void SampleMaterialVisitor::visit(const LayerInterface *)
{
}

void SampleMaterialVisitor::visit(const MultiLayer *)
{
}

void SampleMaterialVisitor::visit(const Particle *sample)
{
    assert(sample);
    addMaterial(sample->getMaterial());
    addMaterial(sample->getAmbientMaterial());
}

void SampleMaterialVisitor::visit(const ParticleDistribution *)
{
}

void SampleMaterialVisitor::visit(const ParticleComposition *)
{
}

void SampleMaterialVisitor::visit(const MesoCrystal *)
{
}

void SampleMaterialVisitor::visit(const ParticleCoreShell *)
{
}

void SampleMaterialVisitor::visit(const IFormFactor *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDWBAPol *)
{
}

void SampleMaterialVisitor::visit(const FormFactorWeighted *)
{
}

void SampleMaterialVisitor::visit(const IFormFactorBorn *)
{
}

void SampleMaterialVisitor::visit(const FormFactorAnisoPyramid *)
{
}

void SampleMaterialVisitor::visit(const FormFactorBox *)
{
}

void SampleMaterialVisitor::visit(const FormFactorCone *)
{
}

void SampleMaterialVisitor::visit(const FormFactorCone6 *)
{
}

void SampleMaterialVisitor::visit(const FormFactorCrystal *)
{
}

void SampleMaterialVisitor::visit(const FormFactorCuboctahedron *)
{
}

void SampleMaterialVisitor::visit(const FormFactorCylinder *)
{
}

void SampleMaterialVisitor::visit(const FormFactorEllipsoidalCylinder *)
{
}

void SampleMaterialVisitor::visit(const FormFactorFullSphere *)
{
}

void SampleMaterialVisitor::visit(const FormFactorFullSpheroid *)
{
}

void SampleMaterialVisitor::visit(const FormFactorGauss *)
{
}

void SampleMaterialVisitor::visit(const FormFactorHemiEllipsoid *)
{
}

void SampleMaterialVisitor::visit(const FormFactorLongBoxGauss *)
{
}

void SampleMaterialVisitor::visit(const FormFactorLongBoxLorentz *)
{
}

void SampleMaterialVisitor::visit(const FormFactorLorentz *)
{
}

void SampleMaterialVisitor::visit(const FormFactorPrism3 *)
{
}

void SampleMaterialVisitor::visit(const FormFactorPrism6 *)
{
}

void SampleMaterialVisitor::visit(const FormFactorPyramid *)
{
}

void SampleMaterialVisitor::visit(const FormFactorRipple1 *)
{
}

void SampleMaterialVisitor::visit(const FormFactorRipple2 *)
{
}

void SampleMaterialVisitor::visit(const FormFactorSphereGaussianRadius *)
{
}

void SampleMaterialVisitor::visit(const FormFactorSphereLogNormalRadius *)
{
}

void SampleMaterialVisitor::visit(const FormFactorTetrahedron *)
{
}

void SampleMaterialVisitor::visit(const FormFactorTrivial *)
{
}

void SampleMaterialVisitor::visit(const FormFactorTruncatedCube *)
{
}

void SampleMaterialVisitor::visit(const FormFactorTruncatedSphere *)
{
}

void SampleMaterialVisitor::visit(const FormFactorTruncatedSpheroid *)
{
}

void SampleMaterialVisitor::visit(const IFormFactorDecorator *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDWBA *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDecoratorDebyeWaller *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDecoratorFactor *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDecoratorMaterial *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDecoratorMultiPositionFactor *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDecoratorPositionFactor *)
{
}

void SampleMaterialVisitor::visit(const FormFactorDecoratorRotation *)
{
}

void SampleMaterialVisitor::visit(const IInterferenceFunction *)
{
}

void SampleMaterialVisitor::visit(const InterferenceFunction1DLattice *)
{
}

void SampleMaterialVisitor::visit(const InterferenceFunctionRadialParaCrystal *)
{
}

void SampleMaterialVisitor::visit(const InterferenceFunction2DLattice *)
{
}

void SampleMaterialVisitor::visit(const InterferenceFunction2DParaCrystal *)
{
}

void SampleMaterialVisitor::visit(const InterferenceFunctionNone *)
{
}

void SampleMaterialVisitor::visit(const IRoughness *)
{
}

void SampleMaterialVisitor::visit(const LayerRoughness *)
{
}

void SampleMaterialVisitor::visit(const RotationX *)
{
}

void SampleMaterialVisitor::visit(const RotationY *)
{
}

void SampleMaterialVisitor::visit(const RotationZ *)
{
}

void SampleMaterialVisitor::visit(const RotationEuler *)
{
}
