// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/Particle.h
//! @brief     Defines class Particle.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLE_H
#define PARTICLE_H

#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "FormFactorDecoratorRefractiveIndex.h"
#include "HomogeneousMaterial.h"

class DiffuseParticleInfo;
class ParticleInfo;

//! A particle with a form factor and refractive index

class BA_CORE_API_ Particle : public ICompositeSample
{
 public:
    Particle();
    Particle(const IMaterial* material, IFormFactor* p_form_factor = 0);
    Particle(const IMaterial* material, const IFormFactor& form_factor);
    virtual ~Particle();
    virtual Particle *clone() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    //! Sets the refractive index of the ambient material (which influences its scattering power)
    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        m_ambient_refractive_index = refractive_index;
    }

    virtual IFormFactor* createFormFactor() const;

    //! Sets the form factor of the particle (not including scattering factor from refractive index)
    virtual void setSimpleFormFactor(IFormFactor* p_form_factor)
    {
        if (!p_form_factor) return;

        if (p_form_factor != mp_form_factor) {
            deregisterChild(mp_form_factor);
            delete mp_form_factor;
            mp_form_factor = p_form_factor;
            registerChild(mp_form_factor);
        }
    }

    //! Sets _material_ and _thickness_.
    virtual void setMaterial(const IMaterial* material) { m_material = material; }

    //! Returns layer's material.
    virtual const IMaterial* getMaterial() const { return m_material; }


    //! Returns refractive index of the particle
    virtual complex_t getRefractiveIndex() const;

    //! Returns formfactor of the particle (not including scattering factor from refractive index)
    virtual const IFormFactor *getSimpleFormFactor() const { return mp_form_factor;}

    //! Creates list of contained particles for diffuse calculations
    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(const ParticleInfo& parent_info) const {
        (void)parent_info;
        return 0;
    }

    virtual bool hasDistributedFormFactor() const;

    virtual std::vector<ParticleInfo *> createDistributedParticles(size_t samples_per_particle, double factor) const;

 protected:
    const IMaterial* m_material;
    complex_t m_ambient_refractive_index;
    IFormFactor* mp_form_factor;
    //!< pointer to the form factor
};

BA_CORE_API_ inline IFormFactor* Particle::createFormFactor() const
{
    if(!mp_form_factor) return 0;
    FormFactorDecoratorRefractiveIndex *p_ff = new FormFactorDecoratorRefractiveIndex(
            mp_form_factor->clone(), getRefractiveIndex());
    p_ff->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_ff;
}


BA_CORE_API_ inline complex_t Particle::getRefractiveIndex() const
{
    const HomogeneousMaterial *material = dynamic_cast<const HomogeneousMaterial *>(m_material);
    return (material ? material->getRefractiveIndex() : complex_t(0,0));
}

BA_CORE_API_ inline bool Particle::hasDistributedFormFactor() const
{
    return ( !mp_form_factor ? false : mp_form_factor->isDistributedFormFactor() );
}


#endif // PARTICLE_H


