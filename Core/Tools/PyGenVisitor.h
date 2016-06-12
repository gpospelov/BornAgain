// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/PyGenVisitor.h
//! @brief     Declares PyGenVisitor class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef _PYGENVISITOR_H
#define _PYGENVISITOR_H
#include "ISampleVisitor.h"
#include "WinDllMacros.h"

#include <set>

class IMaterial;
class SampleLabelHandler;
class GISASSimulation;

class BA_CORE_API_ PyGenVisitor : public ISampleVisitor
{
public:
    PyGenVisitor();
    virtual ~PyGenVisitor();

    using ISampleVisitor::visit;

    std::string writePyScript(
        const GISASSimulation* simulation, const std::string& output_filename);
    virtual void visit(const FormFactorAnisoPyramid* sample);
    virtual void visit(const FormFactorBox* sample);
    virtual void visit(const FormFactorCone* sample);
    virtual void visit(const FormFactorCone6* sample);
    virtual void visit(const FormFactorCuboctahedron* sample);
    virtual void visit(const FormFactorCylinder* sample);
    virtual void visit(const FormFactorDodecahedron* sample);
    virtual void visit(const FormFactorEllipsoidalCylinder* sample);
    virtual void visit(const FormFactorFullSphere* sample);
    virtual void visit(const FormFactorFullSpheroid* sample);
    virtual void visit(const FormFactorGauss* sample);
    virtual void visit(const FormFactorHemiEllipsoid* sample);
    virtual void visit(const FormFactorIcosahedron* sample);
    virtual void visit(const FormFactorLorentz* sample);
    virtual void visit(const FormFactorPrism3* sample);
    virtual void visit(const FormFactorPrism6* sample);
    virtual void visit(const FormFactorPyramid* sample);
    virtual void visit(const FormFactorRipple1* sample);
    virtual void visit(const FormFactorRipple2* sample);
    virtual void visit(const FormFactorTetrahedron* sample);
    virtual void visit(const FormFactorTruncatedCube* sample);
    virtual void visit(const FormFactorTruncatedSphere* sample);
    virtual void visit(const FormFactorTruncatedSpheroid* sample);
    virtual void visit(const InterferenceFunctionNone* sample);
    virtual void visit(const InterferenceFunction1DLattice* sample);
    virtual void visit(const InterferenceFunctionRadialParaCrystal* sample);
    virtual void visit(const InterferenceFunction2DLattice* sample);
    virtual void visit(const InterferenceFunction2DParaCrystal* sample);
    virtual void visit(const Layer* sample);
    virtual void visit(const LayerInterface* sample){ (void)sample; }
    virtual void visit(const LayerRoughness* sample);
    virtual void visit(const MultiLayer* sample);
    virtual void visit(const ParticleComposition* sample);
    virtual void visit(const MesoCrystal* sample);
    virtual void visit(const Particle* sample);
    virtual void visit(const ParticleDistribution* sample);
    virtual void visit(const ParticleCoreShell* sample);
    virtual void visit(const ParticleLayout* sample);

    virtual void visit(const RotationX* sample);
    virtual void visit(const RotationY* sample);
    virtual void visit(const RotationZ* sample);
    virtual void visit(const RotationEuler* sample);

    std::string definePreamble() const;
    std::string defineGetSimulation(const GISASSimulation* simulation) const;
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
    std::string defineDetector(const GISASSimulation* simulation) const;
    std::string defineDetectorResolutionFunction(const GISASSimulation* simulation) const;
    std::string defineBeam(const GISASSimulation* simulation) const;
    std::string defineParameterDistributions(const GISASSimulation* simulation) const;
    std::string defineMasks(const GISASSimulation* simulation) const;
    std::string defineSimulationOptions(const GISASSimulation* simulation) const;
    std::string definePlotting(const GISASSimulation* simulation) const;
    std::string defineRunSimulation() const;
    SampleLabelHandler* m_label;

    std::string indent() const;
    void setRotationInformation(const IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
    void setPositionInformation(const IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
};

#endif
