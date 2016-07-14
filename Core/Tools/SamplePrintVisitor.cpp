// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SamplePrintVisitor.cpp
//! @brief     Implements SamplePrintVisitor class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactors.h"
#include "InterferenceFunctions.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include "SamplePrintVisitor.h"

void SamplePrintVisitor::visit(const ISample *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::visit(const ISample *)"
                                  " -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const ICompositeSample *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const ICompositeSample *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const IClusteredParticles *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const IClusteredParticles *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const Crystal *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const ILayout *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const IDecoration *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const ParticleLayout *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const Layer *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName() << " "
              << (sample->getMaterial() ? sample->getMaterial()->getName() : "0_MATERIAL") << " "
              << sample->getRefractiveIndex() << " " << *sample->getParameterPool() << std::endl;
}

void SamplePrintVisitor::visit(const LayerInterface *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const MultiLayer *sample)
{
    std::cout << "----------------------------------------"
                 "----------------------------------------" << std::endl;
    print_default(sample);
}

void SamplePrintVisitor::visit(const Particle *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName() << " "
              << (sample->getMaterial() ? sample->getMaterial()->getName() : "0_MATERIAL") << " "
              << sample->getRefractiveIndex() << std::endl;
}

void SamplePrintVisitor::visit(const ParticleDistribution *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName() << std::endl;
}

void SamplePrintVisitor::visit(const ParticleComposition *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const MesoCrystal *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const ParticleCoreShell *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const IFormFactor *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const IFormFactor *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDWBAPol *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorDWBAPol *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorWeighted *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorWeighted *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const IFormFactorBorn *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const IFormFactorBorn *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorAnisoPyramid *sample)
{
    print_default(sample);
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
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorCrystal *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorCuboctahedron *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorCylinder *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorDodecahedron *sample)
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

void SamplePrintVisitor::visit(const FormFactorIcosahedron *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorLongBoxGauss *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorLongBoxLorentz *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorLorentz *sample)
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

void SamplePrintVisitor::visit(const FormFactorSphereGaussianRadius *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorSphereLogNormalRadius *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorTetrahedron *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorTrivial *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorTruncatedCube *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorTruncatedSphere *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorTruncatedSpheroid *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const IFormFactorDecorator *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const IFormFactorDecorator *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDWBA *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorDWBA *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDecoratorDebyeWaller *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const FormFactorDecoratorFactor *)
{
    throw Exceptions::NotImplementedException(
        "SamplePrintVisitor::"
        "visit(const FormFactorDecoratorFactor *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDecoratorMaterial *)
{
    throw Exceptions::NotImplementedException(
        "SamplePrintVisitor::"
        "visit(const FormFactorDecoratorMaterial *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDecoratorMultiPositionFactor *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorDecoratorMultiPositionFactor *) -> "
                                  "Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDecoratorPositionFactor *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorDecoratorPositionFactor *) -> "
                                  "Error. Not implemented.");
}

void SamplePrintVisitor::visit(const FormFactorDecoratorRotation *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const FormFactorDecoratorRotation *) -> "
                                  "Error. Not implemented.");
}

void SamplePrintVisitor::visit(const IInterferenceFunction *)
{
    throw Exceptions::NotImplementedException(
        "SamplePrintVisitor::"
        "visit(const IInterferenceFunction *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const InterferenceFunction1DLattice *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const InterferenceFunctionRadialParaCrystal *sample)
{
    print_default(sample);
    const IFTDistribution1D *pdf = sample->getProbabilityDistribution();
    std::cout << get_indent() << ".... pdf: " << (*pdf) << std::endl;
}

void SamplePrintVisitor::visit(const InterferenceFunction2DLattice *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
{
    print_default(sample);
    std::vector<const IFTDistribution2D *> pdfs = sample->getProbabilityDistributions();
    std::cout << get_indent() << ".... pdfs: " << (*pdfs[0]) << " " << (*pdfs[1]) << std::endl;
}

void SamplePrintVisitor::visit(const InterferenceFunctionNone *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const IRoughness *)
{
    throw Exceptions::NotImplementedException("SamplePrintVisitor::"
                                  "visit(const IRoughness *) -> Error. Not implemented.");
}

void SamplePrintVisitor::visit(const LayerRoughness *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const RotationX *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const RotationY *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const RotationZ *sample)
{
    print_default(sample);
}

void SamplePrintVisitor::visit(const RotationEuler *sample)
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
    result.resize((getLevel() - 1) * 4, '.');
    result += " ";
    return result;
}

//! print default sample information
void SamplePrintVisitor::print_default(const ISample *sample)
{
    assert(sample);
    std::cout << get_indent() << sample->getName() << " " << (*sample->getParameterPool())
              << std::endl;
}
