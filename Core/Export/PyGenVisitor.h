// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PyGenVisitor.h
//! @brief     Declares PyGenVisitor class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYGENVISITOR_H
#define PYGENVISITOR_H

#include "ISampleVisitor.h"

class SampleLabelHandler;

class BA_CORE_API_ PyGenVisitor : public ISampleVisitor
{
public:
    PyGenVisitor();
    virtual ~PyGenVisitor();

    std::string writePyScript(
        const class GISASSimulation* simulation, const std::string& output_filename);
    virtual void visit(const class FormFactorAnisoPyramid* sample);
    virtual void visit(const class FormFactorBox* sample);
    virtual void visit(const class FormFactorCone* sample);
    virtual void visit(const class FormFactorCone6* sample);
    virtual void visit(const class FormFactorCuboctahedron* sample);
    virtual void visit(const class FormFactorCylinder* sample);
    virtual void visit(const class FormFactorDodecahedron* sample);
    virtual void visit(const class FormFactorEllipsoidalCylinder* sample);
    virtual void visit(const class FormFactorFullSphere* sample);
    virtual void visit(const class FormFactorFullSpheroid* sample);
    virtual void visit(const class FormFactorGauss* sample);
    virtual void visit(const class FormFactorHemiEllipsoid* sample);
    virtual void visit(const class FormFactorIcosahedron* sample);
    virtual void visit(const class FormFactorLorentz* sample);
    virtual void visit(const class FormFactorPrism3* sample);
    virtual void visit(const class FormFactorPrism6* sample);
    virtual void visit(const class FormFactorPyramid* sample);
    virtual void visit(const class FormFactorRipple1* sample);
    virtual void visit(const class FormFactorRipple2* sample);
    virtual void visit(const class FormFactorTetrahedron* sample);
    virtual void visit(const class FormFactorTruncatedCube* sample);
    virtual void visit(const class FormFactorTruncatedSphere* sample);
    virtual void visit(const class FormFactorTruncatedSpheroid* sample);
    virtual void visit(const class InterferenceFunctionNone* sample);
    virtual void visit(const class InterferenceFunction1DLattice* sample);
    virtual void visit(const class InterferenceFunctionRadialParaCrystal* sample);
    virtual void visit(const class InterferenceFunction2DLattice* sample);
    virtual void visit(const class InterferenceFunction2DParaCrystal* sample);
    virtual void visit(const class Layer* sample);
    virtual void visit(const class LayerInterface* sample){ (void)sample; }
    virtual void visit(const class LayerRoughness* sample);
    virtual void visit(const class MultiLayer* sample);
    virtual void visit(const class ParticleComposition* sample);
    virtual void visit(const class MesoCrystal* sample);
    virtual void visit(const class Particle* sample);
    virtual void visit(const class ParticleDistribution* sample);
    virtual void visit(const class ParticleCoreShell* sample);
    virtual void visit(const class ParticleLayout* sample);

    virtual void visit(const class RotationX* sample);
    virtual void visit(const class RotationY* sample);
    virtual void visit(const class RotationZ* sample);
    virtual void visit(const class RotationEuler* sample);

    std::string definePreamble() const;
    std::string defineGetSimulation(const class GISASSimulation* simulation) const;
    std::string defineGetSample() const;
    std::string defineMaterials() const;

private:
    std::string defineLayers() const;
    std::string defineFormFactors() const;
    std::string defineParticles() const;
    std::string defineCoreShellParticles() const;
    std::string defineParticleDistributions() const;
    std::string defineParticleCompositions() const;
    std::string defineInterferenceFunctions() const;
    std::string defineParticleLayouts() const;
    std::string defineRoughnesses() const;
    std::string addLayoutsToLayers() const;
    std::string defineMultiLayers() const;
    std::string defineDetector(const class GISASSimulation* simulation) const;
    std::string defineDetectorResolutionFunction(const class GISASSimulation* simulation) const;
    std::string defineBeam(const class GISASSimulation* simulation) const;
    std::string defineParameterDistributions(const class GISASSimulation* simulation) const;
    std::string defineMasks(const class GISASSimulation* simulation) const;
    std::string defineSimulationOptions(const class GISASSimulation* simulation) const;
    std::string definePlotting(const class GISASSimulation* simulation) const;
    std::string defineRunSimulation() const;
    SampleLabelHandler* m_label;

    std::string indent() const;
    void setRotationInformation(const class IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
    void setPositionInformation(const class IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
};

#endif // PYGENVISITOR_H
