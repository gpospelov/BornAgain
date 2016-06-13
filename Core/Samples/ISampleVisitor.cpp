// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/ISampleVisitor.cpp
//! @brief     Implements class ISampleVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISampleVisitor.h"
#include "ISample.h"
#include "ICompositeSample.h"
#include "SampleTreeIterator.h"
#include "ISampleIteratorStrategy.h"

void VisitSampleTreePreorder(const ISample& sample, ISampleVisitor& visitor)
{
    SampleTreeIterator<SampleIteratorPreorderStrategy> it(&sample);
    it.first();
    while (!it.isDone()) {
        visitor.setLevel(it.getLevel());
        const ISample *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void VisitSampleTreePostorder(const ISample& sample, ISampleVisitor& visitor)
{
    SampleTreeIterator<SampleIteratorPostorderStrategy> it(&sample);
    it.first();
    while (!it.isDone()) {
        visitor.setLevel(it.getLevel());
        const ISample *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void ISampleVisitor::visit(const ISample*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const ISample*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ICompositeSample*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const ICompositeSample*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IClusteredParticles*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IClusteredParticles*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const Crystal*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const Crystal*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ILayout*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IDecoration*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleLayout*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const ParticleLayout*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const Layer*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const Layer*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const LayerInterface*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const LayerInterface*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const MultiLayer*)
{
    throw NotImplementedException(
                "ISampleVisitor::visit(const MultiLayer*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IAbstractParticle*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IAbstractParticle*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IParticle*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IParticle*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const Particle*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const Particle*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleDistribution*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const ParticleDistribution*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleComposition*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const ParticleComposition*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const MesoCrystal*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const MesoCrystal*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const ParticleCoreShell*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const ParticleCoreShell*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IFormFactor*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IFormFactor*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDWBAPol*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDWBAPol*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorWeighted*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorWeighted*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IFormFactorBorn*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IFormFactorBorn*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorAnisoPyramid*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorAnisoPyramid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorBox*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorBox*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCone*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCone*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCone6*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCone6*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCuboctahedron*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCuboctahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCrystal*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCrystal*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorCylinder*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorCylinder*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDodecahedron*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDodecahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorEllipsoidalCylinder*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorEllipsoid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorFullSphere*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorFullSphere*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorFullSpheroid*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorFullSpheroid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorGauss*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorGauss*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorHemiEllipsoid*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit const FormFactorHemiEllipsoid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorIcosahedron*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorIcosahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorLongBoxGauss*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorLongBoxGauss*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorLongBoxLorentz*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorLongBoxLorentz*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorLorentz*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorLorentz*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorPrism3*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorPrism3*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorPrism6*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorPrism6*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorPyramid*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorPyramid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorRipple1*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorRipple1*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorRipple2*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorRipple2*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorSphereGaussianRadius*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorSphereGaussianRadius*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorSphereLogNormalRadius*)
{
    throw NotImplementedException("ISampleVisitor::visit(const FormFactorSphereLogNormalRadius*) "
                                  "-> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTetrahedron*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTetrahedron*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTrivial*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTrivial*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTruncatedCube*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTruncatedCube*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTruncatedSphere*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTruncatedSphere*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorTruncatedSpheroid*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorTruncatedSpheroid*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IFormFactorDecorator*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IFormFactorDecorator*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDWBA*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDWBA*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorDebyeWaller*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorDebyeWaller*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorFactor*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorFactor*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorMaterial*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const FormFactorDecoratorMaterial*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorMultiPositionFactor*)
{
    throw NotImplementedException("ISampleVisitor::visit(const "
                                  "FormFactorDecoratorMultiPositionFactor*) -> Error. Not "
                                  "implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorPositionFactor*)
{
    throw NotImplementedException("ISampleVisitor::visit(const FormFactorDecoratorPositionFactor "
                                  "*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const FormFactorDecoratorRotation*)
{
    throw NotImplementedException("ISampleVisitor::visit(const FormFactorDecoratorRotation "
                                  "*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IInterferenceFunction*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IInterferenceFunction*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunction1DLattice*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunction1DLattice*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunctionRadialParaCrystal*)
{
    throw NotImplementedException("ISampleVisitor::visit(const "
                                  "InterferenceFunctionRadialParaCrystal*) -> Error. Not "
                                  "implemented.");
}

void ISampleVisitor::visit(const InterferenceFunction2DLattice*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunction2DLattice*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunction2DParaCrystal*)
{
    throw NotImplementedException("ISampleVisitor::visit(const InterferenceFunction2DParaCrystal "
                                  "*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const InterferenceFunctionNone*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const InterferenceFunctionNone*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IRoughness*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IRoughness*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const LayerRoughness*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const LayerRoughness*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const IRotation*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const IRotation*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationX*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const RotationX*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationY*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const RotationY*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationZ*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const RotationZ*) -> Error. Not implemented.");
}

void ISampleVisitor::visit(const RotationEuler*)
{
    throw NotImplementedException(
        "ISampleVisitor::visit(const RotationEuler*) -> Error. Not implemented.");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool ISampleVisitor::visitEnter(const ICompositeSample*)
{
    m_level++;
    return false;
}

bool ISampleVisitor::visitLeave(const ICompositeSample*)
{
    m_level--;
    return false;
}
