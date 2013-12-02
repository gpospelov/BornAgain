// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ISampleHierarchicalVisitor.h
//! @brief     Defines interface class ISampleHierarchicalVisitor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEHIERARCHICALVISITOR_H
#define ISAMPLEHIERARCHICALVISITOR_H

#include "Exceptions.h"

class ISample;
// - the order according to the hierarchy as reported by IDE
class ICompositeSample;
// -
class IClusteredParticles;
class Crystal;
// -
class IDecoration;
class ParticleDecoration;
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
class FormFactorCrystal;
class FormFactorCylinder;
class FormFactorEllipsoid;
class FormFactorFullSphere;
class FormFactorFullSpheroid;
class FormFactorGauss;
class FormFactorHemiSpheroid;
class FormFactorLorentz;
class FormFactorParallelepiped;
class FormFactorPrism3;
class FormFactorPrism6;
class FormFactorPyramid;
class FormFactorSphere;
class FormFactorSphereGaussianRadius;
class FormFactorTetrahedron;
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
class InterferenceFunction1DParaCrystal;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunctionNone;
// -
class IRoughness;
class LayerRoughness;


class BA_CORE_API_ ISampleHierarchicalVisitor
{
public:
    ISampleHierarchicalVisitor() : m_nlevel(0) {}
    virtual ~ISampleHierarchicalVisitor(){}

    // visiting methods (the order according to the hierarchy as reported by IDE)

    virtual bool visit(const ISample *);

    virtual bool visit(const ICompositeSample *);

    virtual bool visit(const IClusteredParticles *);
    virtual bool visit(const Crystal *);

    virtual bool visit(const IDecoration *);
    virtual bool visit(const ParticleDecoration *);

    virtual bool visit(const Layer *);

    virtual bool visit(const LayerInterface *);

    virtual bool visit(const MultiLayer *);

    virtual bool visit(const Particle *);
    virtual bool visit(const LatticeBasis *);
    virtual bool visit(const MesoCrystal *);
    virtual bool visit(const ParticleCoreShell *);

    virtual bool visit(const ParticleInfo *);
    virtual bool visit(const DiffuseParticleInfo *);
    virtual bool visit(const PositionParticleInfo *);

    virtual bool visit(const IFormFactor *);

    virtual bool visit(const FormFactorDWBAPol *);
    virtual bool visit(const FormFactorDWBAPolConstZ *);

    virtual bool visit(const FormFactorWeighted *);

    virtual bool visit(const IFormFactorBorn *);

    virtual bool visit(const FormFactorBox *);
    virtual bool visit(const FormFactorCone *);
    virtual bool visit(const FormFactorCrystal *);
    virtual bool visit(const FormFactorCylinder *);
    virtual bool visit(const FormFactorEllipsoid *);
    virtual bool visit(const FormFactorFullSphere *);
    virtual bool visit(const FormFactorFullSpheroid *);
    virtual bool visit(const FormFactorGauss *);
    virtual bool visit(const FormFactorHemiSpheroid *);
    virtual bool visit(const FormFactorLorentz *);
    virtual bool visit(const FormFactorParallelepiped *);
    virtual bool visit(const FormFactorPrism3 *);
    virtual bool visit(const FormFactorPrism6 *);
    virtual bool visit(const FormFactorPyramid *);
    virtual bool visit(const FormFactorSphere *);
    virtual bool visit(const FormFactorSphereGaussianRadius *);
    virtual bool visit(const FormFactorTetrahedron *);
    virtual bool visit(const IFormFactorBornSeparable *);

    virtual bool visit(const IFormFactorDecorator *);

    virtual bool visit(const FormFactorDWBA *);
    virtual bool visit(const FormFactorDWBAConstZ *);
    virtual bool visit(const FormFactorDecoratorDebyeWaller *);
    virtual bool visit(const FormFactorDecoratorFactor *);
    virtual bool visit(const FormFactorDecoratorMaterial *);
    virtual bool visit(const FormFactorDecoratorMultiPositionFactor *);
    virtual bool visit(const FormFactorDecoratorPositionFactor *);
    virtual bool visit(const FormFactorDecoratorTransformation *);

    virtual bool visit(const IInterferenceFunction *);
    virtual bool visit(const InterferenceFunction1DParaCrystal *);
    virtual bool visit(const InterferenceFunction2DLattice *);
    virtual bool visit(const InterferenceFunction2DParaCrystal *);
    virtual bool visit(const InterferenceFunctionNone *);

    virtual bool visit(const IRoughness *);
    virtual bool visit(const LayerRoughness *);


    // enter and leave methods
    bool visitEnter(const ICompositeSample *);
    bool visitLeave(const ICompositeSample *);

    //! return current level of the visitor
    int getLevel() const { return m_nlevel; }

protected:
    int m_nlevel;
};



#endif // ISAMPLEHIERARCHICALVISITOR_H

