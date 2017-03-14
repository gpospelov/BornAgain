// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLE_H
#define PARTICLE_H

#include "IParticle.h"
#include "HomogeneousMaterial.h"
#include "FormFactorDecoratorMaterial.h"
#include "FormFactorDecoratorRotation.h"

//! A particle with a form factor and refractive index.
//! @ingroup samples

class BA_CORE_API_ Particle : public IParticle
{
public:
    Particle();
    Particle(HomogeneousMaterial material);
    Particle(HomogeneousMaterial material, const IFormFactor& form_factor);
    Particle(HomogeneousMaterial material, const IFormFactor& form_factor,
             const IRotation& rotation);

    Particle* clone() const override final;

    //! Returns a clone with inverted magnetic fields
    Particle* cloneInvertB() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    IFormFactor* createSlicedFormFactor(ZLimits limits) const override final;

    void setMaterial(HomogeneousMaterial material);
    const HomogeneousMaterial* material() const override final { return &m_material; }

    complex_t refractiveIndex() const;

    void setFormFactor(const IFormFactor& form_factor);
    const IFormFactor* formFactor() const { return mP_form_factor.get(); }

    std::vector<const INode*> getChildren() const override final;

protected:
    HomogeneousMaterial m_material;
    std::unique_ptr<IFormFactor> mP_form_factor;
private:
    void initialize();
};

#endif // PARTICLE_H
