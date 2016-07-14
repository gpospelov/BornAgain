// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Tools/SampleMaterialVisitor.h
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

#include "IMaterial.h"

//! @class SampleMaterialVisitor
//! @ingroup samples_internal
//! @brief SampleMaterialVisitor retrieves a list of the used materials in a sample

class BA_CORE_API_ SampleMaterialVisitor : public ISampleVisitor
{
public:
    SampleMaterialVisitor() {}
    virtual ~SampleMaterialVisitor() {}

    // visiting methods (the order according to the hierarchy as reported by IDE)


    void visit(const ISample *sample);

    void visit(const ICompositeSample *sample);

    void visit(const IClusteredParticles *sample);
    void visit(const Crystal *sample);

    void visit(const ILayout *sample);
    void visit(const ParticleLayout *sample);

    void visit(const Layer *sample);

    void visit(const LayerInterface *sample);

    void visit(const MultiLayer *sample);

    void visit(const Particle *sample);
    void visit(const ParticleDistribution *sample);
    void visit(const ParticleComposition *sample);
    void visit(const MesoCrystal *sample);
    void visit(const ParticleCoreShell *sample);

    void visit(const IFormFactor *sample);

    void visit(const FormFactorDWBAPol *sample);

    void visit(const FormFactorWeighted *sample);

    void visit(const IFormFactorBorn *sample);

    void visit(const FormFactorAnisoPyramid *sample);
    void visit(const FormFactorBox *sample);
    void visit(const FormFactorCone *sample);
    void visit(const FormFactorCone6 *sample);
    void visit(const FormFactorCrystal *sample);
    void visit(const FormFactorCuboctahedron *sample);
    void visit(const FormFactorCylinder *sample);
    void visit(const FormFactorDodecahedron *sample);
    void visit(const FormFactorEllipsoidalCylinder *sample);
    void visit(const FormFactorFullSphere *sample);
    void visit(const FormFactorFullSpheroid *sample);
    void visit(const FormFactorGauss *sample);
    void visit(const FormFactorHemiEllipsoid *sample);
    void visit(const FormFactorIcosahedron *sample);
    void visit(const FormFactorLongBoxGauss *sample);
    void visit(const FormFactorLongBoxLorentz *sample);
    void visit(const FormFactorLorentz *sample);
    void visit(const FormFactorPrism3 *sample);
    void visit(const FormFactorPrism6 *sample);
    void visit(const FormFactorPyramid *sample);
    void visit(const FormFactorRipple1 *sample);
    void visit(const FormFactorRipple2 *sample);
    void visit(const FormFactorSphereGaussianRadius *sample);
    void visit(const FormFactorSphereLogNormalRadius *sample);
    void visit(const FormFactorTetrahedron *sample);
    void visit(const FormFactorTrivial *sample);
    void visit(const FormFactorTruncatedCube *sample);
    void visit(const FormFactorTruncatedSphere *sample);
    void visit(const FormFactorTruncatedSpheroid *sample);

    void visit(const IFormFactorDecorator *sample);

    void visit(const FormFactorDWBA *sample);
    void visit(const FormFactorDecoratorDebyeWaller *sample);
    void visit(const FormFactorDecoratorFactor *sample);
    void visit(const FormFactorDecoratorMaterial *sample);
    void visit(const FormFactorDecoratorMultiPositionFactor *sample);
    void visit(const FormFactorDecoratorPositionFactor *sample);
    void visit(const FormFactorDecoratorRotation *sample);

    void visit(const IInterferenceFunction *sample);
    void visit(const InterferenceFunction1DLattice *sample);
    void visit(const InterferenceFunctionRadialParaCrystal *sample);
    void visit(const InterferenceFunction2DLattice *sample);
    void visit(const InterferenceFunction2DParaCrystal *sample);
    void visit(const InterferenceFunctionNone *sample);

    void visit(const IRoughness *sample);
    void visit(const LayerRoughness *sample);

    void visit(const RotationX *);
    void visit(const RotationY *);
    void visit(const RotationZ *);
    void visit(const RotationEuler *);

    //! return vector of material presented in the sample
    std::vector<const IMaterial *> getMaterials() const {
        return m_materials;
    }

    //! return true if contains magnetic materials
    bool containsMagneticMaterial() const;

    //! clear state of the visitor
    void clear();

protected:
    void addMaterial(const IMaterial *p_material);
    std::vector<const IMaterial *> m_materials;
};



#endif // SAMPLEMATERIALVISITOR_H
