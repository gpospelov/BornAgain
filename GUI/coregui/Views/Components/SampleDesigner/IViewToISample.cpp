#include "IViewToISample.h"

#include "ConnectableView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleLayoutView.h"
#include <iostream>

#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "ParticleInfo.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "Particle.h"

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

    goForward();
    foreach(QGraphicsItem *item, view->childItems()) {
        IView *layerView = dynamic_cast<IView *>(item);
        if(layerView) {
            layerView->accept(this);
            if(m_view_to_sample[layerView]) {
                std::cout << "XZXZXZ " << m_view_to_sample[layerView] << " " <<  m_view_to_sample[layerView]->getName() << std::endl;
                Layer *layer = dynamic_cast<Layer *>(m_view_to_sample[layerView]);
                Q_ASSERT(layer);
                sample->addLayer(*layer);
            } else {
                std::cout << "Panic, no layer created" << std::endl;
            }
//            sample->addLayer(*m_view_to_sample[layerView]->clone());

        }
    }
    goBack();

    m_view_to_sample[view] = sample;
}


void IViewToISample::visit(LayerView *)
{
//    Q_ASSERT(view);
//    std::cout << get_indent() << "ViewVisitor(LayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
//    //m_views.insertMulti(m_level, view);


//    QList<ConnectableView *> connections = view->getConnectedInputItems();

//    // in the absence of connections it is simple Layer
//    if(connections.empty()) {
//        m_view_to_sample[view] = view->getLayer()->clone();

//    // with connections it is LayerDecorator
//    } else {
//        goForward();
//        foreach(ConnectableView *item, connections) {
//            item->accept(this);
//            Q_ASSERT(m_view_to_sample[item]);
//            ParticleLayout *particles = dynamic_cast<ParticleLayout *>(m_view_to_sample[item]);
//            Q_ASSERT(particles);
//            LayerDecorator *decorator = new LayerDecorator(*view->getLayer(), *particles);
//            m_view_to_sample[view] = decorator;
//            delete particles;
//        }
//        goBack();

//    }

}


void IViewToISample::visit(ParticleLayoutView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ParticleLayoutView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;

    ParticleLayout *decoration = new ParticleLayout();

//    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ConnectableView *item, view->getConnectedInputItems()) {
        item->accept(this);
        Q_ASSERT(m_view_to_sample[item]);

        ParticleInfo *info = dynamic_cast<ParticleInfo *>(m_view_to_sample[item]);
        std::cout << "info " << info << std::endl;
        if(info) {
            decoration->addParticleInfo(*info);
        }

        IInterferenceFunction *func = dynamic_cast<IInterferenceFunction *>(m_view_to_sample[item]);
        if(func) {
            decoration->addInterferenceFunction(func);
        }

    }
    goBack();

    m_view_to_sample[view] = decoration;

}


void IViewToISample::visit(FormFactorView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
//    m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(FormFactorFullSphereView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorFullSphereView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
//    m_views.insertMulti(m_level, view);
//    Particle *particle = new Particle(complex_t(0,0), *view->getFormFactor()->clone());
//    ParticleInfo *info = new ParticleInfo(particle, 0.0, view->getWeight());
//    m_view_to_sample[view] = info;
}


void IViewToISample::visit(FormFactorPyramidView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPyramidView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
//    Particle *particle = new Particle(complex_t(0,0), *view->getFormFactor()->clone());
//    ParticleInfo *info = new ParticleInfo(particle, 0.0, view->getWeight());
//    m_view_to_sample[view] = info;
}


void IViewToISample::visit(FormFactorPrism3View *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPrism3View ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
//    Particle *particle = new Particle(complex_t(0,0), *view->getFormFactor()->clone());
//    ParticleInfo *info = new ParticleInfo(particle, 0.0, view->getWeight());
//    m_view_to_sample[view] = info;
}


void IViewToISample::visit(FormFactorCylinderView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorCylinderView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
//    Particle *particle = new Particle(complex_t(0,0), *view->getFormFactor()->clone());
//    ParticleInfo *info = new ParticleInfo(particle, 0.0, view->getWeight());
//    m_view_to_sample[view] = info;
}


void IViewToISample::visit(InterferenceFunctionView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunctionView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    //m_views.insertMulti(m_level, view);
}


void IViewToISample::visit(InterferenceFunction1DParaCrystalView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunction1DParaCrystalView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    //m_views.insertMulti(m_level, view);
    InterferenceFunction1DParaCrystal *func = new InterferenceFunction1DParaCrystal(0,0,0);
    m_view_to_sample[view] = func;
}




