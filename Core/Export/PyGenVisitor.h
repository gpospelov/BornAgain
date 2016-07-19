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
#include <string>

class GISASSimulation;
class SampleLabelHandler;

class BA_CORE_API_ PyGenVisitor : public ISampleVisitor
{
public:
    PyGenVisitor();
    virtual ~PyGenVisitor();

    using ISampleVisitor::visit;

    std::string writePyScript(
        const GISASSimulation* simulation, const std::string& output_filename);
    virtual void visit(const FormFactorAnisoPyramid*);
    virtual void visit(const FormFactorBox*);
    virtual void visit(const FormFactorCone*);
    virtual void visit(const FormFactorCone6*);
    virtual void visit(const FormFactorCuboctahedron*);
    virtual void visit(const FormFactorCylinder*);
    virtual void visit(const FormFactorDodecahedron*);
    virtual void visit(const FormFactorEllipsoidalCylinder*);
    virtual void visit(const FormFactorFullSphere*);
    virtual void visit(const FormFactorFullSpheroid*);
    virtual void visit(const FormFactorGauss*);
    virtual void visit(const FormFactorHemiEllipsoid*);
    virtual void visit(const FormFactorIcosahedron*);
    virtual void visit(const FormFactorLorentz*);
    virtual void visit(const FormFactorPrism3*);
    virtual void visit(const FormFactorPrism6*);
    virtual void visit(const FormFactorPyramid*);
    virtual void visit(const FormFactorRipple1*);
    virtual void visit(const FormFactorRipple2*);
    virtual void visit(const FormFactorTetrahedron*);
    virtual void visit(const FormFactorTruncatedCube*);
    virtual void visit(const FormFactorTruncatedSphere*);
    virtual void visit(const FormFactorTruncatedSpheroid*);
    virtual void visit(const InterferenceFunctionNone*);
    virtual void visit(const InterferenceFunction1DLattice*);
    virtual void visit(const InterferenceFunctionRadialParaCrystal*);
    virtual void visit(const InterferenceFunction2DLattice*);
    virtual void visit(const InterferenceFunction2DParaCrystal*);
    virtual void visit(const Layer*);
    virtual void visit(const LayerInterface*);
    virtual void visit(const LayerRoughness*);
    virtual void visit(const MultiLayer*);
    virtual void visit(const ParticleComposition*);
    virtual void visit(const MesoCrystal*);
    virtual void visit(const Particle*);
    virtual void visit(const ParticleDistribution*);
    virtual void visit(const ParticleCoreShell*);
    virtual void visit(const ParticleLayout*);

    virtual void visit(const RotationX*);
    virtual void visit(const RotationY*);
    virtual void visit(const RotationZ*);
    virtual void visit(const RotationEuler*);

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

#endif // PYGENVISITOR_H
