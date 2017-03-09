// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/MesoCrystal.h
//! @brief     Defines class MesoCrystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MESOCRYSTAL_H
#define MESOCRYSTAL_H

#include "IParticle.h"

class IClusteredParticles;
class IMaterial;

//! A particle with an internal structure of smaller particles.
//! @ingroup samples

class BA_CORE_API_ MesoCrystal : public IParticle
{
public:
    MesoCrystal(const IClusteredParticles& particle_structure, const IFormFactor& form_factor);

    ~MesoCrystal();
    MesoCrystal* clone() const override final;

    //! Returns a clone with inverted magnetic fields
    MesoCrystal* cloneInvertB() const override final;

    void accept(INodeVisitor* visitor) const override final;

    IFormFactor* createSlicedFormFactor(ZLimits limits) const override final;

    //! @brief get the internal structure, which is in principle unbounded in
    //! space (e.g. an infinite crystal)
    const IClusteredParticles* getClusteredParticles() const { return mp_particle_structure.get(); }

    std::vector<const INode*> getChildren() const override final;

private:
    MesoCrystal(IClusteredParticles* p_particle_structure, IFormFactor* p_form_factor);
    void initialize();

    std::unique_ptr<IClusteredParticles> mp_particle_structure; //!< Crystal  structure
    std::unique_ptr<IFormFactor> mp_meso_form_factor; //!< Outer shape of this mesocrystal
};

#endif // MESOCRYSTAL_H
