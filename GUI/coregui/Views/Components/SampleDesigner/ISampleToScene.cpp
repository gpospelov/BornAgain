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

ISampleToScene::ISampleToScene() : m_level(0), m_can_i_go(false)
{
}

bool ISampleToScene::goForward()
{
//    bool result = m_can_i_go;
//    if(result) ++m_level;
////    m_can_i_go = false;
//    return result;
//    ++m_level;
    return false;
}


bool ISampleToScene::goBack()
{
//    --m_level;
    return false;
}

std::string ISampleToScene::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


void ISampleToScene::visit(const ISample *sample)
{
    std::cout << get_indent() << "Visitor_ISample " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void ISampleToScene::visit(const MultiLayer *sample)
{
    std::cout << get_indent() << "Visitor_MultiLayer " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
//    m_can_i_go = true;

//    goForward();

    m_level++;
    for(size_t i_layer=0; i_layer < sample->getNumberOfLayers(); ++i_layer) {
        const Layer *layer = sample->getLayer(i_layer);
        layer->accept(this);
        if(i_layer < sample->getNumberOfInterfaces()) {
            const LayerInterface *interface = sample->getLayerInterface(i_layer);
            interface->accept(this);
        }
    }
    m_level--;

//    goBack();

}

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
    m_scene->getTopMultiLayer()->addBottomLayer(layerView);
    m_object_to_view[sample] = layerView;
}

void ISampleToScene::visit(const LayerDecorator *sample)
{
    Q_ASSERT(m_scene);
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

//    goForward();
    m_level++;
    const Layer *layer = sample->getDecoratedLayer();
    layer->accept(this);

    const IDecoration *decoration = sample->getDecoration();
    decoration->accept(this);

    m_level--;
//    goBack();

//    LayerView *layerView = m_object_to_view[layer];
//    ParticleDecorationView *decorationView = m_object_to_view[decoration];
    Q_ASSERT(m_object_to_view[layer]);
    Q_ASSERT(m_object_to_view[decoration]);

    m_object_to_view[layer]->connectInputPort(m_object_to_view[decoration]);

}

void ISampleToScene::visit(const LayerInterface *sample)
{
    std::cout << get_indent() << "Visitor_LayerInterface " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void ISampleToScene::visit(const ParticleDecoration *sample)
{
    std::cout << get_indent() << "Visitor_ParticleDecoration " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    ParticleDecorationView *decorationView = new ParticleDecorationView();
    m_scene->addItem(decorationView);
    m_object_to_view[sample] = decorationView;

//    goForward();

    m_level++;

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

    m_level--;

//    goBack();

}

void ISampleToScene::visit(const ParticleInfo *sample)
{
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    m_level++;
    sample->getParticle()->accept(this);

    m_level--;

//    ParticleDecorationView *decorationView = new ParticleDecorationView();
//    m_scene->addItem(decorationView);
//    if(m_context) m_context->connectInputPort(decorationView);

    m_object_to_view[sample] = m_object_to_view[sample->getParticle()];
}

void ISampleToScene::visit(const Particle *sample)
{
    std::cout << get_indent() << "Visitor_Particle " << sample->getName()
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;

    m_level++;
    sample->getSimpleFormFactor()->accept(this);

    m_level--;

    // Particle doesn't have own view and will be represented by the form factor view
    m_object_to_view[sample] = m_object_to_view[sample->getSimpleFormFactor()];

    std::cout << "XXX Particle" << sample << " view" << m_object_to_view[sample] << std::endl;

}

void ISampleToScene::visit(const IFormFactor *sample)
{
    std::cout << get_indent() << "Visitor_IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}


void ISampleToScene::visit(const FormFactorFullSphere *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorFullSphere " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorFullSphereView *view = new FormFactorFullSphereView();
    view->setFormFactor(sample->clone());
    m_scene->addItem(view);
    m_object_to_view[sample] = view;
}

void ISampleToScene::visit(const FormFactorCylinder *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorCylinder " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorCylinderView *view = new FormFactorCylinderView();
    view->setFormFactor(sample->clone());
    m_scene->addItem(view);
    m_object_to_view[sample] = view;
    std::cout << "XXX Cylinder " << view << std::endl;

}

void ISampleToScene::visit(const FormFactorPyramid *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorPyramid " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorPyramidView *view = new FormFactorPyramidView();
    view->setFormFactor(sample->clone());
    m_scene->addItem(view);
    m_object_to_view[sample] = view;

}


void ISampleToScene::visit(const FormFactorPrism3 *sample)
{
    std::cout << get_indent() << "Visitor_FormFactorPrism3 " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorPrism3View *view = new FormFactorPrism3View();
    view->setFormFactor(sample->clone());
    m_scene->addItem(view);
    m_object_to_view[sample] = view;

}


void ISampleToScene::visit(const IInterferenceFunction *sample)
{
    std::cout << get_indent() << "Visitor_IInterferenceFunction " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void ISampleToScene::visit(const InterferenceFunction1DParaCrystal *sample)
{
    std::cout << get_indent() << "Visitor_InterferenceFunction1DParaCrystal" << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    InterferenceFunction1DParaCrystalView *view = new InterferenceFunction1DParaCrystalView();
    m_scene->addItem(view);
    m_object_to_view[sample] = view;
}


void ISampleToScene::visit(const InterferenceFunction2DParaCrystal *sample)
{
    std::cout << get_indent() << "Visitor_InterferenceFunction2DParaCrystal" << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}
