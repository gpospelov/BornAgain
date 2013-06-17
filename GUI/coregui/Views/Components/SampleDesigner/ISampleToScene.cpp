#include "ISampleToScene.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "Particle.h"
#include <iostream>

ISampleToScene::ISampleToScene() : m_level(0)
{
}

void ISampleToScene::enter()
{
    ++m_level;
}


void ISampleToScene::leave()
{
    --m_level;
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
}

void ISampleToScene::visit(const Layer *sample)
{
    std::cout << get_indent() << "Visitor_Layer " << sample->getName()
              << " " << sample->getMaterial()->getName()
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void ISampleToScene::visit(const LayerDecorator *sample)
{
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    enter();
    sample->getDecoratedLayer()->accept(this);
    sample->getDecoration()->accept(this);
    leave();

//    visitor->visit(this);
//    visitor->enter();
//    mp_decorated_layer->accept(visitor);
//    mp_decoration->accept(visitor);
//    visitor->leave();

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

}

void ISampleToScene::visit(const ParticleInfo *sample)
{
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
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
