// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Visitors/SampleMaterialVisitor.h
//! @brief     Declares class SampleMaterialVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEMATERIALVISITOR_H
#define SAMPLEMATERIALVISITOR_H

#include "ISampleVisitor.h" // inheriting from
#include "IMaterial.h"
#include <vector>

//! @class SampleMaterialVisitor
//! @ingroup samples_internal
//! @brief SampleMaterialVisitor retrieves a list of the used materials in a sample

class BA_CORE_API_ SampleMaterialVisitor : public ISampleVisitor
{
public:
    SampleMaterialVisitor() {}
    virtual ~SampleMaterialVisitor() {}

    // visiting methods (the order according to the hierarchy as reported by IDE)

    using ISampleVisitor::visit;

    void visit(const ISample*);

    void visit(const ICompositeSample*);

    void visit(const IClusteredParticles*);
    void visit(const Crystal*);

    void visit(const ILayout*);
    void visit(const ParticleLayout*);

    void visit(const Layer*);

    void visit(const LayerInterface*);

    void visit(const MultiLayer*);

    void visit(const Particle*);
    void visit(const ParticleDistribution*);
    void visit(const ParticleComposition*);
    void visit(const MesoCrystal*);
    void visit(const ParticleCoreShell*);

    void visit(const IFormFactor*);

    void visit(const FormFactorDWBAPol*);

    void visit(const FormFactorWeighted*);

    void visit(const IFormFactorBorn*);

    void visit(const FormFactorAnisoPyramid*);
    void visit(const FormFactorBox*);
    void visit(const FormFactorCone*);
    void visit(const FormFactorCone6*);
    void visit(const FormFactorCrystal*);
    void visit(const FormFactorCuboctahedron*);
    void visit(const FormFactorCylinder*);
    void visit(const FormFactorDodecahedron*);
    void visit(const FormFactorEllipsoidalCylinder*);
    void visit(const FormFactorFullSphere*);
    void visit(const FormFactorFullSpheroid*);
    void visit(const FormFactorGauss*);
    void visit(const FormFactorHemiEllipsoid*);
    void visit(const FormFactorIcosahedron*);
    void visit(const FormFactorLongBoxGauss*);
    void visit(const FormFactorLongBoxLorentz*);
    void visit(const FormFactorLorentz*);
    void visit(const FormFactorPrism3*);
    void visit(const FormFactorPrism6*);
    void visit(const FormFactorPyramid*);
    void visit(const FormFactorRipple1*);
    void visit(const FormFactorRipple2*);
    void visit(const FormFactorSphereGaussianRadius*);
    void visit(const FormFactorSphereLogNormalRadius*);
    void visit(const FormFactorTetrahedron*);
    void visit(const FormFactorTrivial*);
    void visit(const FormFactorTruncatedCube*);
    void visit(const FormFactorTruncatedSphere*);
    void visit(const FormFactorTruncatedSpheroid*);

    void visit(const IFormFactorDecorator*);

    void visit(const FormFactorDWBA*);
    void visit(const FormFactorDecoratorDebyeWaller*);
    void visit(const FormFactorDecoratorFactor*);
    void visit(const FormFactorDecoratorMaterial*);
    void visit(const FormFactorDecoratorMultiPositionFactor*);
    void visit(const FormFactorDecoratorPositionFactor*);
    void visit(const FormFactorDecoratorRotation*);

    void visit(const IInterferenceFunction*);
    void visit(const InterferenceFunction1DLattice*);
    void visit(const InterferenceFunctionRadialParaCrystal*);
    void visit(const InterferenceFunction2DLattice*);
    void visit(const InterferenceFunction2DParaCrystal*);
    void visit(const InterferenceFunctionNone*);

    void visit(const IRoughness*);
    void visit(const LayerRoughness*);

    void visit(const RotationX*);
    void visit(const RotationY*);
    void visit(const RotationZ*);
    void visit(const RotationEuler*);

    //! return vector of material presented in the sample
    std::vector<const IMaterial*> getMaterials() const { return m_materials; }

    //! return true if contains magnetic materials
    bool containsMagneticMaterial() const;

    //! clear state of the visitor
    void clear();

protected:
    void addMaterial(const IMaterial* p_material);
    std::vector<const IMaterial*> m_materials;
};

#endif // SAMPLEMATERIALVISITOR_H
