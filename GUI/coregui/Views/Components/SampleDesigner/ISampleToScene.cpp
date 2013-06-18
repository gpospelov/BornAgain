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
#include <iostream>

ISampleToScene::ISampleToScene() : m_level(0), m_can_i_go(true), m_context(0)
{
}

bool ISampleToScene::goForward()
{
    bool result = m_can_i_go;
    if(result) ++m_level;
//    m_can_i_go = false;
    return result;
}


bool ISampleToScene::goBack()
{
    --m_level;
    return m_can_i_go;
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
    m_context =  m_scene->getTopMultiLayer();
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

    m_context = layerView;
}

void ISampleToScene::visit(const LayerDecorator *sample)
{
    Q_ASSERT(m_scene);
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

//    goForward();
//    const Layer *layer = sample->getDecoratedLayer();
//    //layer->accept(this);

//    LayerView *layerView = new LayerView();
//    layerView->setThickness(layer->getThickness());

//    m_scene->getTopMultiLayer()->addBottomLayer(layerView);

//    ParticleDecorationView *decorationView = new ParticleDecorationView();
//    m_scene->addItem(decorationView);

//    layerView->connectInputPort(decorationView);

//    sample->getDecoration()->accept(this);
//    goBack();


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
    if(m_context) m_context->connectInputPort(decorationView);
    m_context = decorationView;

//    ParticleDecorationView *view = new ParticleDecorationView();
//    m_scene->addItem(view);


    //    visitor->enter();
    //    for(size_t i=0; i<m_particles.size(); ++i) {
    //        m_particles[i]->accept(visitor);
    //    }
    //    for(size_t i=0; i<m_interference_functions.size(); ++i) {
    //        m_interference_functions[i]->accept(visitor);
    //    }
    //    visitor->leave();


//    goForward();

}

void ISampleToScene::visit(const ParticleInfo *sample)
{
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

//    ParticleDecorationView *decorationView = new ParticleDecorationView();
//    m_scene->addItem(decorationView);
//    if(m_context) m_context->connectInputPort(decorationView);

    FormFactorView *ff(0);


}

void ISampleToScene::visit(const Particle *sample)
{
    std::cout << get_indent() << "Visitor_Particle " << sample->getName()
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;
}

void ISampleToScene::visit(const IFormFactor *sample)
{
    std::cout << get_indent() << "Visitor_IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}


void ISampleToScene::visit(const IInterferenceFunction *sample)
{
    std::cout << get_indent() << "Visitor_IInterferenceFunction " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}
