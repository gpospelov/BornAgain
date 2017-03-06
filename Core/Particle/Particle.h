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
#include "IMaterial.h"
#include "FormFactorDecoratorMaterial.h"
#include "FormFactorDecoratorRotation.h"

//! A particle with a form factor and refractive index.
//! @ingroup samples

class BA_CORE_API_ Particle : public IParticle
{
public:
    Particle();
    Particle(const IMaterial& p_material);
    Particle(const IMaterial& p_material, const IFormFactor& form_factor);
    Particle(const IMaterial& p_material, const IFormFactor& form_factor,
             const IRotation& rotation);

    Particle* clone() const override;

    //! Returns a clone with inverted magnetic fields
    Particle* cloneInvertB() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    IFormFactor* createSlicedFormFactor(ZLimits limits) const override;

    IFormFactor* createTransformedFormFactor(
        const IRotation* p_rotation, kvector_t translation) const override;

    void setMaterial(const IMaterial& material);
    const IMaterial* getMaterial() const override { return mP_material.get(); }

    complex_t getRefractiveIndex() const;

    void setFormFactor(const IFormFactor& form_factor);
    const IFormFactor* getFormFactor() const { return mP_form_factor.get(); }

    std::vector<const INode*> getChildren() const override;

protected:
    std::unique_ptr<IMaterial> mP_material;
    std::unique_ptr<IFormFactor> mP_form_factor;
private:
    void initialize();
};

#endif // PARTICLE_H
