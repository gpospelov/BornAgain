#ifndef ISAMPLEVIEWVISITOR_H
#define ISAMPLEVIEWVISITOR_H

#include "Exceptions.h"

class ISampleView;
class ISampleRectView;
class LayerView;
class MultiLayerView;
class FormFactorView;
class FormFactorFullSphereView;
class FormFactorPyramidView;
class FormFactorCylinderView;
class FormFactorPrism3View;
class InterferenceFunctionView;
class InterferenceFunction1DParaCrystalView;
class ParticleDecorationView;

//! Interface to visit a sample view tree and perform operations on its nodes

class ISampleViewVisitor
{
public:
    virtual ~ISampleViewVisitor(){}
    virtual void visit(const ISampleView *) { throw NotImplementedException("ISampleViewVisitor::visit(ISampleView *)"); }
    virtual void visit(const ISampleRectView *) { throw NotImplementedException("ISampleViewVisitor::visit(ISampleRectView *)"); }
    virtual void visit(const LayerView *) { throw NotImplementedException("ISampleViewVisitor::visit(LayerView *)"); }
    virtual void visit(const MultiLayerView *) { throw NotImplementedException("ISampleViewVisitor::visit(MultiLayerView *)"); }
    virtual void visit(const FormFactorView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorView *)"); }
    virtual void visit(const FormFactorFullSphereView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorFullSphereView *)"); }
    virtual void visit(const FormFactorPyramidView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorPyramidView *)"); }
    virtual void visit(const FormFactorPrism3View *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorPrism3View *)"); }
    virtual void visit(const InterferenceFunctionView *) { throw NotImplementedException("ISampleViewVisitor::visit(InterferenceFunctionView *)"); }
    virtual void visit(const InterferenceFunction1DParaCrystalView *) { throw NotImplementedException("ISampleViewVisitor::visit(InterferenceFunction1DParaCrystalView *)"); }
    virtual void visit(const ParticleDecorationView *) { throw NotImplementedException("ISampleViewVisitor::visit(ParticleDecorationView *)"); }

};

#endif // ISAMPLEVIEWVISITOR_H
