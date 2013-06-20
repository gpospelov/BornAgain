#include "LayerView.h"
#include "MultiLayerView.h"
#include "ISampleToScene.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "ParticleDecorationView.h"
#include "FormFactorView.h"
#include "Particle.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionView.h"
#include <iostream>


//! return created views to the scene
QList<ISampleRectView *> ISampleToScene::getItems()
{
    QList<ISampleRectView *> result;



    return result;
}



//! creates ISampleView
void ISampleToScene::visit(const ISample *sample)
{
    std::cout << get_indent() << "Visitor_ISample " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


//! creates view of MultiLayer, goes deeper to access LayerViews and then adds
//! it to MultiLayerView
void ISampleToScene::visit(const MultiLayer *sample)
{
    std::cout << get_indent() << "Visitor_MultiLayer " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    MultiLayerView *multiLayerView = MultiLayerView::createTopMultiLayer();

    goForward();
    for(size_t i_layer=0; i_layer < sample->getNumberOfLayers(); ++i_layer) {
        const Layer *layer = sample->getLayer(i_layer);
        layer->accept(this);
        Q_ASSERT(m_object_to_view[layer]);
        multiLayerView->addBottomLayer((LayerView *)m_object_to_view[layer]);
        if(i_layer < sample->getNumberOfInterfaces()) {
            const LayerInterface *interface = sample->getLayerInterface(i_layer);
            interface->accept(this);
        }
    }
    goBack();

    m_object_to_view[sample] = multiLayerView;

}


//! creates view of Layer
void ISampleToScene::visit(const Layer *sample)
{
    std::cout << get_indent() << "Visitor_Layer " << sample->getName()
              << " " << sample->getMaterial()->getName()
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;

    LayerView *layerView = new LayerView();
    layerView->setThickness(sample->getThickness());
    layerView->setName(sample->getName().c_str());
    m_object_to_view[sample] = layerView;
}


//! should create view of LayerDecorator, but since LayerDecorator doesn't have
//! own graphical representation, the method goes deeper in ISample hierarchy, and
//! on the way back connects layer and it's decoration
void ISampleToScene::visit(const LayerDecorator *sample)
{
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    const Layer *layer = sample->getDecoratedLayer();
    layer->accept(this);

    const IDecoration *decoration = sample->getDecoration();
    decoration->accept(this);

    goBack();

    Q_ASSERT(m_object_to_view[layer]);
    Q_ASSERT(m_object_to_view[decoration]);
    m_object_to_view[layer]->connectInputPort(m_object_to_view[decoration]);
}


//! creates view of LayerInterface
void ISampleToScene::visit(const LayerInterface *sample)
{
    std::cout << get_indent() << "Visitor_LayerInterface " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


//! creates view of ParticleDecoration and connect it with form factors and
//! interference functions views
void ISampleToScene::visit(const ParticleDecoration *sample)
{
    std::cout << get_indent() << "Visitor_ParticleDecoration " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    ParticleDecorationView *decorationView = new ParticleDecorationView();
//    m_scene->addItem(decorationView);
    m_object_to_view[sample] = decorationView;

    goForward();
    for(size_t i_info=0; i_info < sample->getNumberOfParticles(); ++i_info) {
        const ParticleInfo *info = sample->getParticleInfo(i_info);
        info->accept(this);
        Q_ASSERT(m_object_to_view[info]);
        decorationView->connectInputPort(m_object_to_view[info]);
    }

    for(size_t i_func=0; i_func < sample->getNumberOfInterferenceFunctions(); ++i_func) {
        const IInterferenceFunction *func = sample->getInterferenceFunction(i_func);
        func->accept(this);
        Q_ASSERT(m_object_to_view[func]);
        decorationView->connectInputPort(m_object_to_view[func]);
    }
    goBack();
}


//! Should create ParticleInfo view, but since ParticleInfo doesn't have own graphical
//! representation, method just goes deeper in ISample hierarchy
void ISampleToScene::visit(const ParticleInfo *sample)
{
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    sample->getParticle()->accept(this);

    goBack();

    // ParticleInfo doesn't have own view and will be represented by the Particle view
    m_object_to_view[sample] = m_object_to_view[sample->getParticle()];
}


//! Should create Particle view, but since Particle doesn't have own graphical
//! representation, method just goes deeper in ISample hierarchy
void ISampleToScene::visit(const Particle *sample)
{
    std::cout << get_indent() << "Visitor_Particle " << sample->getName()
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;

    goForward();

    sample->getSimpleFormFactor()->accept(this);

    goBack();

    // Particle doesn't have own view and will be represented by the form factor view
    m_object_to_view[sample] = m_object_to_view[sample->getSimpleFormFactor()];
}


void ISampleToScene::visit(const IFormFactor *sample)
{
    std::cout << get_indent() << "Visitor_IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}


//! creates view of FormFactorFullSphere
void ISampleToScene::visit(const FormFactorFullSphere *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorFullSphere " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorFullSphereView *view = new FormFactorFullSphereView();
    view->setFormFactor(sample->clone());
    //m_scene->addItem(view);
    m_object_to_view[sample] = view;
}


//! creates view of FormFactorCylinder
void ISampleToScene::visit(const FormFactorCylinder *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorCylinder " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorCylinderView *view = new FormFactorCylinderView();
    view->setFormFactor(sample->clone());
    //m_scene->addItem(view);
    m_object_to_view[sample] = view;
    std::cout << "XXX Cylinder " << view << std::endl;

}


//! creates view of FormFactorPyramid
void ISampleToScene::visit(const FormFactorPyramid *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorPyramid " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorPyramidView *view = new FormFactorPyramidView();
    view->setFormFactor(sample->clone());
    //m_scene->addItem(view);
    m_object_to_view[sample] = view;

}


//! creates view of FormFactorPrism3
void ISampleToScene::visit(const FormFactorPrism3 *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorPrism3 " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorPrism3View *view = new FormFactorPrism3View();
    view->setFormFactor(sample->clone());
    //m_scene->addItem(view);
    m_object_to_view[sample] = view;

}


//! creates view of IInterferenceFunction
void ISampleToScene::visit(const IInterferenceFunction *sample)
{
    std::cout << get_indent() << "Visitor_IInterferenceFunction " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


//! creates view of InterferenceFunction1DParaCrystal
void ISampleToScene::visit(const InterferenceFunction1DParaCrystal *sample)
{
    std::cout << get_indent() << "Visitor_InterferenceFunction1DParaCrystal" << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    InterferenceFunction1DParaCrystalView *view = new InterferenceFunction1DParaCrystalView();
    //m_scene->addItem(view);
    m_object_to_view[sample] = view;
}


//! creates view of InterferenceFunction2DParaCrystal
void ISampleToScene::visit(const InterferenceFunction2DParaCrystal *sample)
{
    std::cout << get_indent() << "Visitor_InterferenceFunction2DParaCrystal" << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

