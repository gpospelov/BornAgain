// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/SampleMaterialVisitor.cpp
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
#include "IMaterial.h"
#include "Layer.h"
#include "Particle.h"
#include "LatticeBasis.h"


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
        if (!(*it)->isScalarMaterial()) return true;
    }
    return false;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void SampleMaterialVisitor::visit(const ISample *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const ISample *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const ICompositeSample *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const ICompositeSample *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IClusteredParticles *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IClusteredParticles *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const Crystal *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const Crystal *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IDecoration *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IDecoration *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const ParticleDecoration *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const ParticleDecoration *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const Layer *sample)
{
    assert(sample);
    const IMaterial *material = sample->getMaterial();
    addMaterial(material);
}


void SampleMaterialVisitor::visit(const LayerInterface *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const LayerInterface *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const MultiLayer *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const MultiLayer *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const Particle *sample)
{
    assert(sample);
    addMaterial(sample->getMaterial());
    addMaterial(sample->getAmbientMaterial());
}


void SampleMaterialVisitor::visit(const LatticeBasis *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const LatticeBasis *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const MesoCrystal *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const MesoCrystal *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const ParticleCoreShell *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const ParticleCoreShell *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const ParticleInfo *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const ParticleInfo *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const DiffuseParticleInfo *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const DiffuseParticleInfo *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const PositionParticleInfo *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const PositionParticleInfo *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IFormFactor *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IFormFactor *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDWBAPol *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDWBAPol *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDWBAPolConstZ *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDWBAPolConstZ *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorWeighted *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorWeighted *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IFormFactorBorn *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IFormFactorBorn *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorBox *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorBox *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorCone *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorCone *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorCone6 *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorCone6 *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorCrystal *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorCrystal *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorCylinder *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorCylinder *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorEllipsoidalCylinder *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorEllipsoid *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorFullSphere *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorFullSphere *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorFullSpheroid *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorFullSpheroid *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorGauss *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorGauss *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorHemiEllipsoid *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit const FormFactorHemiSpheroid *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorLorentz *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorLorentz *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorParallelepiped *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorParallelepiped *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorPrism3 *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorPrism3 *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorPrism6 *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorPrism6 *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorPyramid *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorPyramid *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorSphere *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorSphere *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorSphereGaussianRadius *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorSphereGaussianRadius *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorTetrahedron *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorTetrahedron *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IFormFactorBornSeparable *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IFormFactorBornSeparable *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IFormFactorDecorator *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IFormFactorDecorator *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDWBA *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDWBA *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDWBAConstZ *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDWBAConstZ *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDecoratorDebyeWaller *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDecoratorDebyeWaller *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDecoratorFactor *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDecoratorFactor *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDecoratorMaterial *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDecoratorMaterial *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDecoratorMultiPositionFactor *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDecoratorMultiPositionFactor *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDecoratorPositionFactor *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDecoratorPositionFactor *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const FormFactorDecoratorTransformation *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const FormFactorDecoratorTransformation *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IInterferenceFunction *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IInterferenceFunction *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const InterferenceFunction1DParaCrystal *){
//    throw NotImplementedException("SampleMaterialVisitor::visit(const InterferenceFunction1DParaCrystal *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const InterferenceFunction2DLattice *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const InterferenceFunction2DLattice *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const InterferenceFunction2DParaCrystal *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const InterferenceFunction2DParaCrystal *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const InterferenceFunctionNone *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const InterferenceFunctionNone *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const IRoughness *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const IRoughness *) -> Error. Not implemented.");
}


void SampleMaterialVisitor::visit(const LayerRoughness *)
{
//    throw NotImplementedException("SampleMaterialVisitor::visit(const LayerRoughness *) -> Error. Not implemented.");
}



