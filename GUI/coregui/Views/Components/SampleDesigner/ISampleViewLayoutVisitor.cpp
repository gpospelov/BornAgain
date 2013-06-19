#include "ISampleViewLayoutVisitor.h"
#include "ISampleView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleDecorationView.h"
#include <iostream>

ISampleViewLayoutVisitor::ISampleViewLayoutVisitor()
{

}


void ISampleViewLayoutVisitor::visit(const ISampleView *view)
{
    std::cout << "ViewLayoutVisitor(ISampleView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const ISampleRectView *view)
{
    std::cout << "ViewLayoutVisitor(ISampleRectView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const LayerView *view)
{
    std::cout << "ViewLayoutVisitor(LayerView) " << view->type() << std::endl;

}

void ISampleViewLayoutVisitor::visit(const MultiLayerView *view)
{
    std::cout << "ViewLayoutVisitor(MultiLayerView) " << view->type() << std::endl;

    foreach(QGraphicsItem *item, view->childItems()) {
        std::cout << "xxx " << item->type() << std::endl;
    }
}

void ISampleViewLayoutVisitor::visit(const FormFactorView *view)
{
    std::cout << "ViewLayoutVisitor(FormFactorView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const FormFactorFullSphereView *view)
{
    std::cout << "ViewLayoutVisitor(FormFactorFullSphereView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const FormFactorPyramidView *view)
{
    std::cout << "ViewLayoutVisitor(FormFactorPyramidView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const FormFactorPrism3View *view)
{
    std::cout << "ViewLayoutVisitor(FormFactorPrism3View) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const InterferenceFunctionView *view)
{
    std::cout << "ViewLayoutVisitor(InterferenceFunctionView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const InterferenceFunction1DParaCrystalView *view)
{
    std::cout << "ViewLayoutVisitor(InterferenceFunction1DParaCrystalView) " << view->type() << std::endl;
}

void ISampleViewLayoutVisitor::visit(const ParticleDecorationView *view)
{
    std::cout << "ViewLayoutVisitor(ParticleDecorationView) " << view->type() << std::endl;
}

