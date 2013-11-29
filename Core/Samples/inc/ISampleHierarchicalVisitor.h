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

// --- the order is according to the doxygen class diagram for convenience
class ISample;
// -
class IFormFactor;
// -
class FormFactorDWBAPolConstZ;
class FormFactorDWBAPol;
// -
class FormFactorWeighted;
class IFormFactorBorn;
class IFormFactorDecorator;
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
class IInterferenceFunction;
class InterferenceFunction1DParaCrystal;
class InterferenceFunction2DLattice;
class InterferenceFunction2DParaCrystal;
class InterferenceFunctionNone;
// -
class IRoughness;
class LayerRoughness;
// -
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


class BA_CORE_API_ ISampleHierarchicalVisitor
{
public:
    ISampleHierarchicalVisitor() : m_nlevel(0) {}
    virtual ~ISampleHierarchicalVisitor(){}

    // visiting methods (the order according doxygen class diagram for convenience)

    virtual void visit(const ISample *);

    virtual void visit(const IFormFactor *);

    virtual void visit(const FormFactorDWBAPolConstZ *);
    virtual void visit(const FormFactorDWBAPol *);

    virtual void visit(const FormFactorWeighted *);
    virtual void visit(const IFormFactorBorn *);
    virtual void visit(const IFormFactorDecorator *);
    virtual void visit(const FormFactorBox *);
    virtual void visit(const FormFactorCone *);
    virtual void visit(const FormFactorCrystal *);
    virtual void visit(const FormFactorCylinder *);
    virtual void visit(const FormFactorEllipsoid *);
    virtual void visit(const FormFactorFullSphere *);
    virtual void visit(const FormFactorFullSpheroid *);
    virtual void visit(const FormFactorGauss *);
    virtual void visit(const FormFactorHemiSpheroid *);
    virtual void visit(const FormFactorLorentz *);
    virtual void visit(const FormFactorParallelepiped *);
    virtual void visit(const FormFactorPrism3 *);
    virtual void visit(const FormFactorPrism6 *);
    virtual void visit(const FormFactorPyramid *);
    virtual void visit(const FormFactorSphere *);
    virtual void visit(const FormFactorSphereGaussianRadius *);
    virtual void visit(const FormFactorTetrahedron *);
    virtual void visit(const IFormFactorBornSeparable *);

    virtual void visit(const IInterferenceFunction *);
    virtual void visit(const InterferenceFunction1DParaCrystal *);
    virtual void visit(const InterferenceFunction2DLattice *);
    virtual void visit(const InterferenceFunction2DParaCrystal *);
    virtual void visit(const InterferenceFunctionNone *);

    virtual void visit(const IRoughness *);
    virtual void visit(const LayerRoughness *);

    virtual void visit(const ICompositeSample *);

    virtual void visit(const IClusteredParticles *);
    virtual void visit(const Crystal *);

    virtual void visit(const IDecoration *);
    virtual void visit(const ParticleDecoration *);

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

    // enter and leave methods
    bool visitEnter(const ICompositeSample *);
    bool visitLeave(const ICompositeSample *);

    //! return current level of the visitor
    int getLevel() const { return m_nlevel; }

protected:
    int m_nlevel;
};



#endif // ISAMPLEHIERARCHICALVISITOR_H

