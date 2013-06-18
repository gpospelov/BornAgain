#include "SamplePrintVisitor.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "Particle.h"
#include <iostream>

SamplePrintVisitor::SamplePrintVisitor() : m_level(0)
{
}

bool SamplePrintVisitor::goForward()
{
    ++m_level;
    return true;
}


bool SamplePrintVisitor::goBack()
{
    --m_level;
    return true;
}

std::string SamplePrintVisitor::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


void SamplePrintVisitor::visit(const ISample *sample)
{
    std::cout << get_indent() << "Visitor_ISample " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const MultiLayer *sample)
{
    std::cout << get_indent() << "Visitor_MultiLayer " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const Layer *sample)
{
    std::cout << get_indent() << "Visitor_Layer " << sample->getName()
              << " " << sample->getMaterial()->getName()
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const LayerDecorator *sample)
{
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
    goForward();
    sample->getDecoratedLayer()->accept(this);
    sample->getDecoration()->accept(this);
    goBack();


}

void SamplePrintVisitor::visit(const LayerInterface *sample)
{
    std::cout << get_indent() << "Visitor_LayerInterface " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const ParticleDecoration *sample)
{
    std::cout << get_indent() << "Visitor_ParticleDecoration " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const ParticleInfo *sample)
{
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const Particle *sample)
{
    std::cout << get_indent() << "Visitor_Particle " << sample->getName()
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;
}

void SamplePrintVisitor::visit(const IFormFactor *sample)
{
    std::cout << get_indent() << "Visitor_IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const IInterferenceFunction *sample)
{
    std::cout << get_indent() << "Visitor_IInterferenceFunction " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;


}
