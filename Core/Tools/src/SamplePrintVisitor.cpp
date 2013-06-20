#include "SamplePrintVisitor.h"
#include "ISample.h"
#include "FormFactors.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "Particle.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include <iostream>


void SamplePrintVisitor::visit(const ISample *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_ISample " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const MultiLayer *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_MultiLayer " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();
    for(size_t i_layer=0; i_layer < sample->getNumberOfLayers(); ++i_layer) {
        const Layer *layer = sample->getLayer(i_layer);
        layer->accept(this);
        if(i_layer < sample->getNumberOfInterfaces()) {
            const LayerInterface *interface = sample->getLayerInterface(i_layer);
            interface->accept(this);
        }
    }
    goBack();
}


void SamplePrintVisitor::visit(const Layer *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_Layer " << sample->getName()
              << " " << sample->getMaterial()->getName()
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const LayerDecorator *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_LayerDecorator " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    const Layer *layer = sample->getDecoratedLayer();
    layer->accept(this);

    const IDecoration *decoration = sample->getDecoration();
    decoration->accept(this);

    goBack();
}


void SamplePrintVisitor::visit(const LayerInterface *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_LayerInterface " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const ParticleDecoration *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_ParticleDecoration " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();
    for(size_t i_info=0; i_info < sample->getNumberOfParticles(); ++i_info) {
        const ParticleInfo *info = sample->getParticleInfo(i_info);
        info->accept(this);
    }

    for(size_t i_func=0; i_func < sample->getNumberOfInterferenceFunctions(); ++i_func) {
        const IInterferenceFunction *func = sample->getInterferenceFunction(i_func);
        func->accept(this);
    }
    goBack();
}


void SamplePrintVisitor::visit(const ParticleInfo *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    sample->getParticle()->accept(this);

    goBack();
}


void SamplePrintVisitor::visit(const Particle *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_Particle " << sample->getName()
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;

    goForward();

    sample->getSimpleFormFactor()->accept(this);

    goBack();
}


void SamplePrintVisitor::visit(const IFormFactor *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}


void SamplePrintVisitor::visit(const FormFactorFullSphere *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_FormFactorFullSphere " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const FormFactorCylinder *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_FormFactorCylinder " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const FormFactorPyramid *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_FormFactorPyramid " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const FormFactorPrism3 *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_FormFactorPrism3 " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const IInterferenceFunction *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_IInterferenceFunction " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const InterferenceFunction1DParaCrystal *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_InterferenceFunction1DParaCrystal" << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
{
    assert(sample);
    std::cout << get_indent() << "Visitor_InterferenceFunction2DParaCrystal" << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}



