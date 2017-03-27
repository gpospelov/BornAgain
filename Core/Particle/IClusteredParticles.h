// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IClusteredParticles.h
//! @brief     Defines class IClusteredParticles.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICLUSTEREDPARTICLES_H
#define ICLUSTEREDPARTICLES_H

#include "ISample.h"
#include "SlicedParticle.h"
#include "Vectors3D.h"

class IFormFactor;
class IRotation;

//! An ordered assembly of particles. Currently, the only child class is Crystal.
//! @ingroup samples_internal

class BA_CORE_API_ IClusteredParticles : public ISample
{
public:
    IClusteredParticles* clone() const override=0;

    void accept(INodeVisitor* visitor) const  override=0;

    //! Creates a total form factor for the mesocrystal with a specific shape and content
    //! The bulk content of the mesocrystal is encapsulated by the IClusteredParticles object itself
    virtual IFormFactor* createTotalFormFactor(
        const IFormFactor&, const IRotation*, const kvector_t& /*translation*/) const =0;

    //! Creates region information with volumetric densities instead of absolute volume
    //! These densities need to be multiplied by the total mesocrystal volume
    virtual std::vector<HomogeneousRegion> homogeneousRegions() const =0;

    //! Composes transformation with existing one
    virtual void applyRotation(const IRotation&) =delete;
};

#endif // ICLUSTEREDPARTICLES_H
