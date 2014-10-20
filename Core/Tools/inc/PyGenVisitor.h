#ifndef _PYGENVISITOR_H
#define _PYGENVISITOR_H
#include "ISampleVisitor.h"
#include "WinDllMacros.h"

#include <set>

class IMaterial;
class LabelSample;
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
    void visit(const FormFactorTruncatedSphere *sample);
    void visit(const FormFactorTruncatedSpheroid *sample);
    void visit(const InterferenceFunctionNone *);
    void visit(const InterferenceFunction1DLattice *);
    void visit(const InterferenceFunction1DParaCrystal *);
    void visit(const InterferenceFunction2DLattice *);
    void visit(const InterferenceFunction2DParaCrystal *);
    void visit(const Layer *sample);
    void visit(const LayerInterface *){}
    void visit(const LayerRoughness *sample);
    void visit(const MultiLayer *sample);
    void visit(const Particle *sample);
    void visit(const ParticleCoreShell *sample);
    void visit(const ParticleInfo *){}
    void visit(const ParticleLayout *sample);
    void visit(const PositionParticleInfo *){}


private:
    LabelSample *m_label;
    std::set<std::string> visitedMaterials;
};


#endif
