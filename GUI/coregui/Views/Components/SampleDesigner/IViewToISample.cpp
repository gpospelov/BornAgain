#include "IViewToISample.h"

#include "ConnectableView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleDecorationView.h"
#include <iostream>

#include "MultiLayer.h"

ISample *IViewToISample::makeISample(IView *view)
{
    view->accept(this);
    return m_view_to_sample[view];
}


void IViewToISample::visit(IView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ISampleView ) " << m_level << " " << view->type() << " " << std::endl;
}


void IViewToISample::visit(ConnectableView *view)
{
    std::cout << get_indent() << "ViewVisitor(ISampleRectView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
}


void IViewToISample::visit(MultiLayerView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(MultiLayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    //m_views.insertMulti(m_level, view);

    MultiLayer *sample = new MultiLayer();

//    goForward();
//    foreach(QGraphicsItem *item, view->childItems()) {
//        ISampleView *layerView = dynamic_cast<ISampleView *>(item);
//        if(layerView) {
//            layerView->accept(this);
//            std::cout << "XZXZXZ " << m_view_to_sample[layerView] << " " <<  m_view_to_sample[layerView]->getName() << std::endl;
//            //sample->addLayer(*(Layer *)m_view_to_sample[layerView]);

//        }
//    }
//    goBack();

    Layer layer;
    sample->addLayer(layer);
    sample->addLayer(layer);
    sample->addLayer(layer);

    m_view_to_sample[view] = sample;
}


void IViewToISample::visit(LayerView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(LayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    //m_views.insertMulti(m_level, view);

    Layer *layer = new Layer();
    m_view_to_sample[view] = layer;

//    goForward();
//    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
//        item->accept(this);
//    }
//    goBack();
}


void IViewToISample::visit(FormFactorView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(FormFactorFullSphereView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorFullSphereView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(FormFactorPyramidView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPyramidView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(FormFactorPrism3View *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPrism3View ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(FormFactorCylinderView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorCylinderView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(InterferenceFunctionView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunctionView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(InterferenceFunction1DParaCrystalView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunction1DParaCrystalView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(ParticleDecorationView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ParticleDecorationView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;

    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ConnectableView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();
}


