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

void SamplePrintVisitor::enter()
{
    ++m_level;
}


void SamplePrintVisitor::leave()
{
    --m_level;
}

std::string SamplePrintVisitor::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


void SamplePrintVisitor::visit(ISample *sample)
{
    std::cout << get_indent() << "Visitor_ISample " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(MultiLayer *sample)
{
    std::cout << get_indent() << "Visitor_MultiLayer " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(Layer *sample)
{
    std::cout << get_indent() << "Visitor_Layer " << sample->getName()
              << " " << sample->getMaterial()->getName()
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(LayerDecorator *sample)
{
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}

void SamplePrintVisitor::visit(LayerInterface *sample)
{
    std::cout << get_indent() << "Visitor_LayerInterface " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(ParticleDecoration *sample)
{
    std::cout << get_indent() << "Visitor_ParticleDecoration " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}

void SamplePrintVisitor::visit(ParticleInfo *sample)
{
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(Particle *sample)
{
    std::cout << get_indent() << "Visitor_Particle " << sample->getName()
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;
}

void SamplePrintVisitor::visit(IFormFactor *sample)
{
    std::cout << get_indent() << "Visitor_IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

