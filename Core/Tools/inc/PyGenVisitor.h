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
class LabelSample;
class Simulation;

class BA_CORE_API_ PyGenVisitor : public ISampleVisitor
{
public:
    PyGenVisitor();

    using ISampleVisitor::visit;

    std::string writePyScript(const Simulation *simulation);
    virtual void visit(const FormFactorAnisoPyramid *sample);
    virtual void visit(const FormFactorBox *sample);
    virtual void visit(const FormFactorCone *sample);
    virtual void visit(const FormFactorCone6 *sample);
    virtual void visit(const FormFactorCuboctahedron *sample);
    virtual void visit(const FormFactorCylinder *sample);
    virtual void visit(const FormFactorEllipsoidalCylinder *sample);
    virtual void visit(const FormFactorFullSphere *sample);
    virtual void visit(const FormFactorFullSpheroid *sample);
    virtual void visit(const FormFactorGauss *sample);
    virtual void visit(const FormFactorHemiEllipsoid *sample);
    virtual void visit(const FormFactorInfLongBox *sample);
    virtual void visit(const FormFactorInfLongRipple1 *sample);
    virtual void visit(const FormFactorInfLongRipple2 *sample);
    virtual void visit(const FormFactorLorentz *sample);
    virtual void visit(const FormFactorPrism3 *sample);
    virtual void visit(const FormFactorPrism6 *sample);
    virtual void visit(const FormFactorPyramid *sample);
    virtual void visit(const FormFactorRipple1 *sample);
    virtual void visit(const FormFactorRipple2 *sample);
    virtual void visit(const FormFactorTetrahedron *sample);
    virtual void visit(const FormFactorTruncatedSphere *sample);
    virtual void visit(const FormFactorTruncatedSpheroid *sample);
    virtual void visit(const InterferenceFunctionNone *sample);
    virtual void visit(const InterferenceFunction1DLattice *sample);
    virtual void visit(const InterferenceFunctionRadialParaCrystal *sample);
    virtual void visit(const InterferenceFunction2DLattice *sample);
    virtual void visit(const InterferenceFunction2DParaCrystal *sample);
    virtual void visit(const Layer *sample);
    virtual void visit(const LayerInterface *sample){ (void)sample; }
    virtual void visit(const LayerRoughness *sample);
    virtual void visit(const MultiLayer *sample);
    virtual void visit(const LatticeBasis *sample);
    virtual void visit(const MesoCrystal *sample);
    virtual void visit(const Particle *sample);
    virtual void visit(const ParticleCoreShell *sample);
    virtual void visit(const ParticleInfo *sample){ (void)sample; }
    virtual void visit(const ParticleLayout *sample);


private:
    LabelSample *m_label;
    std::set<std::string> visitedMaterials;
};


#endif
