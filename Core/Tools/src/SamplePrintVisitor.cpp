#include "SamplePrintVisitor.h"
#include "ISample.h"
#include "FormFactors.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "ParticleInfo.h"
#include <iostream>
#include "MesoCrystal.h"


void SamplePrintVisitor::visit(const ISample *sample)
{
    assert(sample);
    std::cout << get_indent() << "PrintVisitor_ISample " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const MultiLayer *sample)
{
    assert(sample);
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << get_indent() << "MultiLayer " << sample->getName()
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
    std::cout << "----------------------------------------------" << std::endl;
}


void SamplePrintVisitor::visit(const Layer *sample)
{
    assert(sample);
    std::cout << get_indent() << "Layer " << sample->getName()
              << " " << (sample->getMaterial() ? sample->getMaterial()->getName() : "0_MATERIAL")
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;

    const IDecoration *decoration = sample->getDecoration();
    if(decoration) decoration->accept(this);
}


void SamplePrintVisitor::visit(const LayerInterface *sample)
{
    assert(sample);
    std::cout << get_indent() << "LayerInterface " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
    const IRoughness *roughness = sample->getRoughness();
    if(roughness) roughness->accept(this);

}


void SamplePrintVisitor::visit(const ParticleDecoration *sample)
{
    assert(sample);
    std::cout << get_indent() << "ParticleDecoration " << sample->getName()
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
    std::cout << get_indent() << "ParticleInfo " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    sample->getParticle()->accept(this);

    goBack();
}


void SamplePrintVisitor::visit(const Particle *sample)
{
    assert(sample);
    std::cout << get_indent() << "Particle " << sample->getName()
              << " " << (sample->getMaterial() ? sample->getMaterial()->getName() : "0_MATERIAL")
              << " " << sample->getRefractiveIndex()
              << std::endl;

    goForward();

    sample->getSimpleFormFactor()->accept(this);

    goBack();
}


void SamplePrintVisitor::visit(const ParticleCoreShell* sample)
{
    assert(sample);
    std::cout << get_indent() << "ParticleCoreShell " <<
            sample->getName() << std::endl;

    goForward();

    const Particle *p_core = sample->getCoreParticle();
    if (p_core) {
        p_core->accept(this);
    }
    const Particle *p_shell = sample->getShellParticle();
    if (p_shell) {
        p_shell->accept(this);
    }

    goBack();
}

void SamplePrintVisitor::visit(const MesoCrystal* sample)
{
    assert(sample);
    std::cout << get_indent() << "MesoCrystal " <<
            sample->getName() << std::endl;

    goForward();

    const IClusteredParticles *p_clustered_particles =
            sample->getClusteredParticles();
    p_clustered_particles->accept(this);

    const IFormFactor *p_meso_ff = sample->getSimpleFormFactor();
    p_meso_ff->accept(this);

    goBack();
}

void SamplePrintVisitor::visit(const Crystal* sample)
{
    assert(sample);
    std::cout << get_indent() << "Crystal " <<
            sample->getName() << std::endl;

    goForward();

    const LatticeBasis *p_lattice_basis = sample->getLatticeBasis();
    p_lattice_basis->accept(this);

    goBack();
}

void SamplePrintVisitor::visit(const LatticeBasis* sample)
{
    assert(sample);
    std::cout << get_indent() << "LatticeBasis " <<
            sample->getName() << std::endl;

    goForward();

    size_t nbr_particles = sample->getNbrParticles();
    for (size_t i=0; i<nbr_particles; ++i)
    {
        const Particle *p_particle = sample->getParticle(i);
        p_particle->accept(this);
    }

    goBack();
}

void SamplePrintVisitor::visit(const IFormFactor *sample)
{
    assert(sample);
    std::cout << get_indent() << "IFormFactor " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;

}


void SamplePrintVisitor::visit(const FormFactorFullSphere *sample)
{
    assert(sample);
    std::cout << get_indent() << "FormFactorFullSphere " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const FormFactorCylinder *sample)
{
    assert(sample);
    std::cout << get_indent() << "FormFactorCylinder " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const FormFactorPyramid *sample)
{
    assert(sample);
    std::cout << get_indent() << "FormFactorPyramid " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const FormFactorPrism3 *sample)
{
    assert(sample);
    std::cout << get_indent() << "FormFactorPrism3 " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const IInterferenceFunction *sample)
{
    assert(sample);
    std::cout << get_indent() << "IInterferenceFunction " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const InterferenceFunction1DParaCrystal *sample)
{
    assert(sample);
    std::cout << get_indent() << "InterferenceFunction1DParaCrystal " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}

void SamplePrintVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
{
    assert(sample);
    std::cout << get_indent() << "InterferenceFunction2DParaCrystal " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const InterferenceFunction2DLattice *sample)
{
    assert(sample);
    std::cout << get_indent() << "InterferenceFunction2DLattice " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const LayerRoughness *sample)
{
    assert(sample);
    std::cout << get_indent() << "LayerRoughness " << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


