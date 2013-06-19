#ifndef ISAMPLEVIEWLAYOUTVISITOR_H
#define ISAMPLEVIEWLAYOUTVISITOR_H

#include "ISampleViewVisitor.h"

//! The ISampleViewLayoutVisitor class places views of ISample nicely on the scene
class ISampleViewLayoutVisitor : public ISampleViewVisitor
{
public:
    ISampleViewLayoutVisitor();

    void visit(const ISampleView *view);
    void visit(const ISampleRectView *view);
    void visit(const LayerView *view);
    void visit(const MultiLayerView *view);
    void visit(const FormFactorView *view);
    void visit(const FormFactorFullSphereView *view);
    void visit(const FormFactorPyramidView *view);
    void visit(const FormFactorPrism3View *view);
    void visit(const InterferenceFunctionView *view);
    void visit(const InterferenceFunction1DParaCrystalView *view);
    void visit(const ParticleDecorationView *view);

};

#endif // ISAMPLEVIEWLAYOUTVISITOR_H
