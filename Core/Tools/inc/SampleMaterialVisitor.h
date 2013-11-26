// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/SampleMaterialVisitor.h
//! @brief     Defines class SampleMaterialVisitor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEMATERIALVISITOR_H_
#define SAMPLEMATERIALVISITOR_H_

#include "ISampleVisitor.h"
#include "IMaterial.h"

//! SampleMaterialVisitor retrieves a list of the used materials in a sample
class SampleMaterialVisitor : public ISampleVisitor
{
public:
    SampleMaterialVisitor();
    virtual ~SampleMaterialVisitor();

    void visit(const ISample *sample);
    void visit(const MultiLayer *sample);
    void visit(const Layer *sample);
    void visit(const LayerInterface *sample);
    void visit(const ParticleDecoration *sample);
    void visit(const ParticleInfo *sample);
    void visit(const Particle *sample);
    void visit(const ParticleCoreShell *sample);
    void visit(const MesoCrystal *sample);
    void visit(const Crystal *sample);
    void visit(const LatticeBasis *sample);
    void visit(const IFormFactor *sample);

    void visit(const FormFactorFullSphere *sample);
    void visit(const FormFactorPyramid *sample);
    void visit(const FormFactorCylinder *sample);
    void visit(const FormFactorPrism3 *sample);

    void visit(const IInterferenceFunction *sample);
    void visit(const InterferenceFunction1DParaCrystal  *);
    void visit(const InterferenceFunction2DParaCrystal  *);
    void visit(const InterferenceFunction2DLattice  *);

    void visit(const LayerRoughness  *);

    std::vector<const IMaterial *> getMaterials() const {
        return m_materials;
    }

protected:
    void addMaterial(const IMaterial *p_material);
    std::vector<const IMaterial *> m_materials;
};



#endif /* SAMPLEMATERIALVISITOR_H_ */
