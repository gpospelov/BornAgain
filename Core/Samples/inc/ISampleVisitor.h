// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISampleVisitor.h
//! @brief     Defines interface class ISampleVisitor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEVISITOR_H
#define ISAMPLEVISITOR_H

#include "Exceptions.h"

class ISample;
// - the order according to the hierarchy as reported by IDE
class ICompositeSample;
// -
class IClusteredParticles;
class Crystal;
// -
class ILayout;
class ParticleLayout;
// -
class Layer;
// -
class LayerInterface;
// -
class MultiLayer;
// -
class Particle;
class LatticeBasis;
class MesoCrystal;
class ParticleCoreShell;
// -
class ParticleInfo;
class DiffuseParticleInfo;
class PositionParticleInfo;
// -
class IFormFactor;
// -
class FormFactorDWBAPol;
class FormFactorDWBAPolConstZ;
// -
class FormFactorWeighted;
// -
class IFormFactorBorn;
// -
class FormFactorBox;
class FormFactorCone;
class FormFactorCone6;
class FormFactorCrystal;
class FormFactorCylinder;
class FormFactorEllipsoidalCylinder;
class FormFactorFullSphere;
class FormFactorFullSpheroid;
class FormFactorGauss;
class FormFactorHemiEllipsoid;
class FormFactorInfLongBox;
class FormFactorLorentz;
//class FormFactorParallelepiped;
class FormFactorPrism3;
class FormFactorPrism6;
class FormFactorPyramid;
class FormFactorRipple1;
class FormFactorRipple2;
class FormFactorSphereGaussianRadius;
class FormFactorTetrahedron;
class FormFactorTruncatedSphere;
class FormFactorTruncatedSpheroid;
class IFormFactorBornSeparable;
// -
class IFormFactorDecorator;
// -
class FormFactorDWBA;
class FormFactorDWBAConstZ;
class FormFactorDecoratorDebyeWaller;
class FormFactorDecoratorFactor;
class FormFactorDecoratorMaterial;
class FormFactorDecoratorMultiPositionFactor;
class FormFactorDecoratorPositionFactor;
class FormFactorDecoratorTransformation;
// -
class IInterferenceFunction;
class InterferenceFunction1DLattice;
class InterferenceFunction1DParaCrystal;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunctionNone;
// -
class IRoughness;
class LayerRoughness;

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

    virtual void visit(const ISample *);

    virtual void visit(const ICompositeSample *);

    virtual void visit(const IClusteredParticles *);
    virtual void visit(const Crystal *);

    virtual void visit(const ILayout *);
    virtual void visit(const ParticleLayout *);

    virtual void visit(const Layer *);

    virtual void visit(const LayerInterface *);

    virtual void visit(const MultiLayer *);

    virtual void visit(const Particle *);
    virtual void visit(const LatticeBasis *);
    virtual void visit(const MesoCrystal *);
    virtual void visit(const ParticleCoreShell *);

    virtual void visit(const ParticleInfo *);
    virtual void visit(const DiffuseParticleInfo *);
    virtual void visit(const PositionParticleInfo *);

    virtual void visit(const IFormFactor *);

    virtual void visit(const FormFactorDWBAPol *);
    virtual void visit(const FormFactorDWBAPolConstZ *);

    virtual void visit(const FormFactorWeighted *);

    virtual void visit(const IFormFactorBorn *);

    virtual void visit(const FormFactorBox *);
    virtual void visit(const FormFactorCone *);
    virtual void visit(const FormFactorCone6 *);
    virtual void visit(const FormFactorCrystal *);
    virtual void visit(const FormFactorCylinder *);
    virtual void visit(const FormFactorEllipsoidalCylinder *);
    virtual void visit(const FormFactorFullSphere *);
    virtual void visit(const FormFactorFullSpheroid *);
    virtual void visit(const FormFactorGauss *);
    virtual void visit(const FormFactorHemiEllipsoid *);
    virtual void visit(const FormFactorInfLongBox *);
    virtual void visit(const FormFactorLorentz *);
    virtual void visit(const FormFactorPrism3 *);
    virtual void visit(const FormFactorPrism6 *);
    virtual void visit(const FormFactorPyramid *);
    virtual void visit(const FormFactorRipple1 *);
    virtual void visit(const FormFactorRipple2 *);
    virtual void visit(const FormFactorSphereGaussianRadius *);
    virtual void visit(const FormFactorTetrahedron *);
    virtual void visit(const FormFactorTruncatedSphere *);
    virtual void visit(const FormFactorTruncatedSpheroid *);
    virtual void visit(const IFormFactorBornSeparable *);

    virtual void visit(const IFormFactorDecorator *);

    virtual void visit(const FormFactorDWBA *);
    virtual void visit(const FormFactorDWBAConstZ *);
    virtual void visit(const FormFactorDecoratorDebyeWaller *);
    virtual void visit(const FormFactorDecoratorFactor *);
    virtual void visit(const FormFactorDecoratorMaterial *);
    virtual void visit(const FormFactorDecoratorMultiPositionFactor *);
    virtual void visit(const FormFactorDecoratorPositionFactor *);
    virtual void visit(const FormFactorDecoratorTransformation *);

    virtual void visit(const IInterferenceFunction *);
    virtual void visit(const InterferenceFunction1DLattice *);
    virtual void visit(const InterferenceFunction1DParaCrystal *);
    virtual void visit(const InterferenceFunction2DLattice *);
    virtual void visit(const InterferenceFunction2DParaCrystal *);
    virtual void visit(const InterferenceFunctionNone *);

    virtual void visit(const IRoughness *);
    virtual void visit(const LayerRoughness *);

    // enter and leave methods
    bool visitEnter(const ICompositeSample *);
    bool visitLeave(const ICompositeSample *);

    //! return current level of the visitor in the composite hierarchy
    int getLevel() const { return m_level; }

    //! set current level of the visitor in the composite hierarchy
    void setLevel(int level) { m_level = level; }

private:
    int m_level;
};

void VisitSampleTree(const ISample &sample, ISampleVisitor &visitor);


#endif // ISAMPLEVISITOR_H
