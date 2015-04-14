// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/PyGenVisitor.h
//! @brief     Defines PyGenVisitor class.
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
class Simulation;

class BA_CORE_API_ PyGenVisitor : public ISampleVisitor
{
public:
    PyGenVisitor();

    using ISampleVisitor::visit;

    std::string writePyScript(const Simulation *simulation);
    void visit(const FormFactorAnisoPyramid *sample);
    void visit(const FormFactorBox *sample);
    void visit(const FormFactorCone *sample);
    void visit(const FormFactorCone6 *sample);
    void visit(const FormFactorCuboctahedron *sample);
    void visit(const FormFactorCylinder *sample);
    void visit(const FormFactorEllipsoidalCylinder *sample);
    void visit(const FormFactorFullSphere *sample);
    void visit(const FormFactorFullSpheroid *sample);
    void visit(const FormFactorGauss *sample);
    void visit(const FormFactorHemiEllipsoid *sample);
    void visit(const FormFactorInfLongBox *sample);
    void visit(const FormFactorInfLongRipple1 *sample);
    void visit(const FormFactorInfLongRipple2 *sample);
    void visit(const FormFactorLorentz *sample);
    void visit(const FormFactorPrism3 *sample);
    void visit(const FormFactorPrism6 *sample);
    void visit(const FormFactorPyramid *sample);
    void visit(const FormFactorRipple1 *sample);
    void visit(const FormFactorRipple2 *sample);
    void visit(const FormFactorTetrahedron *sample);
    void visit(const FormFactorTruncatedCube *sample);
    void visit(const FormFactorTruncatedSphere *sample);
    void visit(const FormFactorTruncatedSpheroid *sample);
    void visit(const InterferenceFunctionNone *sample);
    void visit(const InterferenceFunction1DLattice *sample);
    void visit(const InterferenceFunctionRadialParaCrystal *sample);
    void visit(const InterferenceFunction2DLattice *sample);
    void visit(const InterferenceFunction2DParaCrystal *sample);
    void visit(const Layer *sample);
    void visit(const LayerInterface *sample){ (void)sample; }
    void visit(const LayerRoughness *sample);
    void visit(const MultiLayer *sample);
    void visit(const ParticleComposition *sample);
    void visit(const MesoCrystal *sample);
    void visit(const Particle *sample);
    void visit(const ParticleCoreShell *sample);
    void visit(const ParticleInfo *sample){ (void)sample; }
    void visit(const ParticleLayout *sample);

    void visit(const RotationX *sample);
    void visit(const RotationY *sample);
    void visit(const RotationZ *sample);
    void visit(const RotationEuler *sample);

    std::string definePreamble() const;
    std::string defineGetSimulation(const Simulation *simulation) const;
    std::string defineGetSample() const;
    std::string defineMaterials() const;

private:
    std::string defineLayers() const;
    std::string defineFormFactors() const;
    std::string defineParticles() const;
    std::string defineCoreShellParticles() const;
    std::string defineParticleCompositions() const;
    std::string defineInterferenceFunctions() const;
    std::string defineParticleLayouts() const;
    std::string defineRoughnesses() const;
    std::string addLayoutsToLayers() const;
    std::string defineMultiLayers() const;
    std::string defineDetector(const Simulation *simulation) const;
    std::string defineBeam(const Simulation *simulation) const;
    std::string definePlotting(const Simulation *simulation) const;
    std::string defineRunSimulation() const;
    SampleLabelHandler *m_label;

    std::string indent() const;
};


#endif
