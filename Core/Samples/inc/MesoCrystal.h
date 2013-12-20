// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/MesoCrystal.h
//! @brief     Defines class MesoCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MESOCRYSTAL_H_
#define MESOCRYSTAL_H_

#include "IClusteredParticles.h"
#include "IFormFactor.h"
#include "Particle.h"

//! @class MesoCrystal
//! @ingroup samples
//! @brief A particle with an internal structure of smaller particles

class BA_CORE_API_ MesoCrystal : public Particle
{
public:
    MesoCrystal(IClusteredParticles *p_particle_structure,
            IFormFactor *p_form_factor);
    MesoCrystal(const IClusteredParticles& particle_structure,
            IFormFactor& form_factor);

    virtual ~MesoCrystal();
    virtual MesoCrystal *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual MesoCrystal *cloneInvertB() const;

    //! Calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual void setAmbientMaterial(const IMaterial *p_material);

    virtual IFormFactor* createFormFactor(
            complex_t wavevector_scattering_factor) const;

    virtual void setSimpleFormFactor(IFormFactor* p_form_factor);

    virtual const IFormFactor *getSimpleFormFactor() const {
        return mp_meso_form_factor;
    }

    //! @brief get the internal structure, which is in principle unbounded in
    //! space (eg.  an infinite crystal)
    const IClusteredParticles *getClusteredParticles() const {
        return mp_particle_structure;
    }

    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(
            const ParticleInfo& parent_info) const;

protected:
    //! Propagates a transformation to child particles
    virtual void applyTransformationToSubParticles(
            const Geometry::Transform3D& transform);

private:
    IClusteredParticles *mp_particle_structure;
    IFormFactor *mp_meso_form_factor;
};

#endif /* MESOCRYSTAL_H_ */


