// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/ISampleVisitor.h
//! @brief     Declares interface class ISampleVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEVISITOR_H
#define ISAMPLEVISITOR_H

//! @class ISampleVisitor
//! @ingroup samples_internal
//! @brief Visitor interface to visit ISample objects
//!
//! From visitor pattern to achieve double dispatch

class BA_CORE_API_ ISampleVisitor
{
public:
    ISampleVisitor() : m_level(0) {}
    virtual ~ISampleVisitor(){}

    // visiting methods (the order according to the hierarchy as reported by IDE)

    virtual void visit(const class ISample*);

    virtual void visit(const class ICompositeSample*);

    virtual void visit(const class IClusteredParticles*);
    virtual void visit(const class Crystal*);

    virtual void visit(const class ILayout*);
    virtual void visit(const class ParticleLayout*);

    virtual void visit(const class Layer*);

    virtual void visit(const class LayerInterface*);

    virtual void visit(const class MultiLayer*);

    virtual void visit(const class IAbstractParticle*);
    virtual void visit(const class IParticle*);
    virtual void visit(const class Particle*);
    virtual void visit(const class ParticleDistribution*);
    virtual void visit(const class ParticleComposition*);
    virtual void visit(const class MesoCrystal*);
    virtual void visit(const class ParticleCoreShell*);

    virtual void visit(const class IFormFactor*);
    virtual void visit(const class IFormFactorBorn*);
    virtual void visit(const class IFormFactorDecorator*);

    virtual void visit(const class FormFactorAnisoPyramid*);
    virtual void visit(const class FormFactorBox*);
    virtual void visit(const class FormFactorCone*);
    virtual void visit(const class FormFactorCone6*);
    virtual void visit(const class FormFactorCuboctahedron*);
    virtual void visit(const class FormFactorCrystal*);
    virtual void visit(const class FormFactorCylinder*);
    virtual void visit(const class FormFactorDodecahedron*);
    virtual void visit(const class FormFactorEllipsoidalCylinder*);
    virtual void visit(const class FormFactorFullSphere*);
    virtual void visit(const class FormFactorFullSpheroid*);
    virtual void visit(const class FormFactorGauss*);
    virtual void visit(const class FormFactorHemiEllipsoid*);
    virtual void visit(const class FormFactorIcosahedron*);
    virtual void visit(const class FormFactorLongBoxGauss*);
    virtual void visit(const class FormFactorLongBoxLorentz*);
    virtual void visit(const class FormFactorLorentz*);
    virtual void visit(const class FormFactorPrism3*);
    virtual void visit(const class FormFactorPrism6*);
    virtual void visit(const class FormFactorPyramid*);
    virtual void visit(const class FormFactorRipple1*);
    virtual void visit(const class FormFactorRipple2*);
    virtual void visit(const class FormFactorSphereGaussianRadius*);
    virtual void visit(const class FormFactorSphereLogNormalRadius*);
    virtual void visit(const class FormFactorTetrahedron*);
    virtual void visit(const class FormFactorTrivial*);
    virtual void visit(const class FormFactorTruncatedCube*);
    virtual void visit(const class FormFactorTruncatedSphere*);
    virtual void visit(const class FormFactorTruncatedSpheroid*);

    virtual void visit(const class FormFactorDWBA*);
    virtual void visit(const class FormFactorDWBAPol*);
    virtual void visit(const class FormFactorWeighted*);
    virtual void visit(const class FormFactorDecoratorDebyeWaller*);
    virtual void visit(const class FormFactorDecoratorFactor*);
    virtual void visit(const class FormFactorDecoratorMaterial*);
    virtual void visit(const class FormFactorDecoratorMultiPositionFactor*);
    virtual void visit(const class FormFactorDecoratorPositionFactor*);
    virtual void visit(const class FormFactorDecoratorRotation*);

    virtual void visit(const class IInterferenceFunction*);
    virtual void visit(const class InterferenceFunction1DLattice*);
    virtual void visit(const class InterferenceFunctionRadialParaCrystal*);
    virtual void visit(const class InterferenceFunction2DLattice*);
    virtual void visit(const class InterferenceFunction2DParaCrystal*);
    virtual void visit(const class InterferenceFunctionNone*);

    virtual void visit(const class IRoughness*);
    virtual void visit(const class LayerRoughness*);

    virtual void visit(const class IRotation*);
    virtual void visit(const class RotationX*);
    virtual void visit(const class RotationY*);
    virtual void visit(const class RotationZ*);
    virtual void visit(const class RotationEuler*);

    // enter and leave methods
    bool visitEnter(const class ICompositeSample*);
    bool visitLeave(const class ICompositeSample*);

    //! return current level of the visitor in the composite hierarchy
    int getLevel() const { return m_level; }

    //! set current level of the visitor in the composite hierarchy
    void setLevel(int level) { m_level = level; }

private:
    int m_level;
};

BA_CORE_API_ void VisitSampleTreePreorder(const class ISample& sample, ISampleVisitor& visitor);
BA_CORE_API_ void VisitSampleTreePostorder(const class ISample& sample, ISampleVisitor& visitor);

#endif // ISAMPLEVISITOR_H
