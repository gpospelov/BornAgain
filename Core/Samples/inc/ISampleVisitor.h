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
class MultiLayer;
class Layer;
class LayerInterface;
class ParticleDecoration;
class ParticleInfo;
class Particle;
class ParticleCoreShell;
class IFormFactor;
class IInterferenceFunction;
class FormFactorFullSphere;
class FormFactorPyramid;
class FormFactorCylinder;
class FormFactorPrism3;
class InterferenceFunction1DParaCrystal;
class InterferenceFunction2DParaCrystal;

//! Interface to visit a sample tree and perform operations on its nodes

class ISampleVisitor
{
public:
    //! Destructor
    virtual ~ISampleVisitor() {}

    //! Performs specific action on the given sample
    //! Needs to be overloaded for different ISample types

    virtual void visit(const ISample *) { throw NotImplementedException(
            "ISampleVisitor::visit(ISample *)"); }
    virtual void visit(const MultiLayer *) { throw NotImplementedException(
            "ISampleVisitor::visit(MultiLayer *)"); }
    virtual void visit(const Layer *) { throw NotImplementedException(
            "ISampleVisitor::visit(Layer *)"); }
    virtual void visit(const LayerInterface *) { throw NotImplementedException(
            "ISampleVisitor::visit(LayerInterface *)"); }
    virtual void visit(const ParticleDecoration *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(ParticleDecoration *)");
    }
    virtual void visit(const ParticleInfo *) { throw NotImplementedException(
            "ISampleVisitor::visit(ParticleInfo *)"); }
    virtual void visit(const Particle *) { throw NotImplementedException(
            "ISampleVisitor::visit(Particle *)"); }
    virtual void visit(const ParticleCoreShell *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(ParticleCoreShell *)");
    }
    virtual void visit(const IFormFactor *) { throw NotImplementedException(
            "ISampleVisitor::visit(IFormFactor *)"); }
    virtual void visit(const FormFactorFullSphere *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(FormFactorFullSphere *)");
    }
    virtual void visit(const FormFactorPyramid *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(FormFactorPyramid *)");
    }
    virtual void visit(const FormFactorCylinder *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(FormFactorCylinder *)");
    }
    virtual void visit(const FormFactorPrism3 *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(FormFactorPrism3 *)");
    }
    virtual void visit(const IInterferenceFunction *) {
        throw NotImplementedException(
            "ISampleVisitor::visit(IInterferenceFunction *)");
    }
    virtual void visit(const InterferenceFunction1DParaCrystal  *) {
        throw NotImplementedException(
                "ISampleVisitor::visit(InterferenceFunction1DParaCrystal  *)");
    }
    virtual void visit(const InterferenceFunction2DParaCrystal  *) {
        throw NotImplementedException(
                "ISampleVisitor::visit(InterferenceFunction2DParaCrystal  *)");
    }

    virtual bool goForward(){ return true; }
    virtual bool goBack(){ return true; }
};


#endif // ISAMPLEVISITOR_H
