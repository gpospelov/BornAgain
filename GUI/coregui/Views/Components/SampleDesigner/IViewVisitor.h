#ifndef ISAMPLEVIEWVISITOR_H
#define ISAMPLEVIEWVISITOR_H

#include "Exceptions.h"

class IView;
class ConnectableView;
class LayerView;
class MultiLayerView;
class FormFactorView;
class FormFactorFullSphereView;
class FormFactorPyramidView;
class FormFactorCylinderView;
class FormFactorPrism3View;
class InterferenceFunctionView;
class InterferenceFunction1DParaCrystalView;
class ParticleLayoutView;

//! Interface to visit a sample view tree and perform operations on its nodes

class IViewVisitor
{
public:
    virtual ~IViewVisitor(){}
    virtual void visit(IView *) { throw NotImplementedException("ISampleViewVisitor::visit(ISampleView *)"); }
    virtual void visit(ConnectableView *) { throw NotImplementedException("ISampleViewVisitor::visit(ISampleRectView *)"); }
    virtual void visit(MultiLayerView *) { throw NotImplementedException("ISampleViewVisitor::visit(MultiLayerView *)"); }
    virtual void visit(LayerView *) { throw NotImplementedException("ISampleViewVisitor::visit(LayerView *)"); }
    virtual void visit(ParticleLayoutView *) { throw NotImplementedException("ISampleViewVisitor::visit(ParticleLayoutView *)"); }
    virtual void visit(FormFactorView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorView *)"); }
    virtual void visit(FormFactorFullSphereView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorFullSphereView *)"); }
    virtual void visit(FormFactorPyramidView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorPyramidView *)"); }
    virtual void visit(FormFactorPrism3View *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorPrism3View *)"); }
    virtual void visit(FormFactorCylinderView *) { throw NotImplementedException("ISampleViewVisitor::visit(FormFactorCylinderView *)"); }
    virtual void visit(InterferenceFunctionView *) { throw NotImplementedException("ISampleViewVisitor::visit(InterferenceFunctionView *)"); }
    virtual void visit(InterferenceFunction1DParaCrystalView *) { throw NotImplementedException("ISampleViewVisitor::visit(InterferenceFunction1DParaCrystalView *)"); }

    virtual bool goForward(){ return true; }
    virtual bool goBack(){ return true; }

};

#endif // ISAMPLEVIEWVISITOR_H
