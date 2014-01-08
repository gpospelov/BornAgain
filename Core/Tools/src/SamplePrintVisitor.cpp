// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/SamplePrintVisitor.cpp
//! @brief     Implements SamplePrintVisitor class.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SamplePrintVisitor.h"
#include "ISample.h"
#include "FormFactors.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "InterferenceFunctions.h"
#include "ParticleInfo.h"
#include "LayerInterface.h"
#include "PositionParticleInfo.h"
#include <iostream>
#include "MesoCrystal.h"


void SamplePrintVisitor::visit(const ISample *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const ISample *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const ICompositeSample *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const ICompositeSample *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const IClusteredParticles *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IClusteredParticles *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const Crystal *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const IDecoration *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IDecoration *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const ParticleDecoration *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const Layer *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName()
              << " " << (sample->getMaterial() ? sample->getMaterial()->getName() : "0_MATERIAL")
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;
}


void SamplePrintVisitor::visit(const LayerInterface *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const MultiLayer *sample)
{
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    print_default(sample);
}


void SamplePrintVisitor::visit(const Particle *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName()
              << " " << (sample->getMaterial() ? sample->getMaterial()->getName() : "0_MATERIAL")
              << " " << sample->getRefractiveIndex()
              << std::endl;
}


void SamplePrintVisitor::visit(const LatticeBasis *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const MesoCrystal *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const ParticleCoreShell *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const ParticleCoreShell *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const ParticleInfo *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const DiffuseParticleInfo *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const DiffuseParticleInfo *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const PositionParticleInfo *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const IFormFactor *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IFormFactor *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDWBAPol *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDWBAPol *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDWBAPolConstZ *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDWBAPolConstZ *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorWeighted *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorWeighted *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const IFormFactorBorn *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IFormFactorBorn *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorBox *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorCone *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorCone6 *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorCrystal *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorCrystal *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorCylinder *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorEllipsoidalCylinder *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorFullSphere *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorFullSpheroid *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorGauss *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorHemiEllipsoid *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorLorentz *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorLorentz *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorParallelepiped *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorPrism3 *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorPrism6 *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorPyramid *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorRipple1 *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorRipple2 *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorSphere *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorSphereGaussianRadius *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorTetrahedron *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const IFormFactorBornSeparable *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IFormFactorBornSeparable *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const IFormFactorDecorator *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IFormFactorDecorator *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDWBA *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDWBA *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDWBAConstZ *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDWBAConstZ *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDecoratorDebyeWaller *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const FormFactorDecoratorFactor *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDecoratorFactor *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDecoratorMaterial *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDecoratorMaterial *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDecoratorMultiPositionFactor *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDecoratorMultiPositionFactor *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDecoratorPositionFactor *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDecoratorPositionFactor *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const FormFactorDecoratorTransformation *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const FormFactorDecoratorTransformation *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const IInterferenceFunction *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IInterferenceFunction *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const InterferenceFunction1DParaCrystal *sample){
    print_default(sample);
}


void SamplePrintVisitor::visit(const InterferenceFunction2DLattice *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const InterferenceFunctionNone *sample)
{
    print_default(sample);
}


void SamplePrintVisitor::visit(const IRoughness *)
{
    throw NotImplementedException("SamplePrintVisitor::visit(const IRoughness *) -> Error. Not implemented.");
}


void SamplePrintVisitor::visit(const LayerRoughness *sample)
{
    print_default(sample);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

//! return string representing indentation
std::string SamplePrintVisitor::get_indent()
{
    std::string result;
    result.resize(getLevel()*4, '.');
    result += " ";
    return result;
}

//! print default sample information
void SamplePrintVisitor::print_default(const ISample *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName()
              << " " << (*sample->getParameterPool())
              << std::endl;
}



/*



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


*/



