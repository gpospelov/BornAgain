// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/IClusteredParticles.h
//! @brief     Declares class IClusteredParticles.
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

#include "IFormFactor.h"
#include "ICompositeSample.h"
#include "Exceptions.h"

//! @class IClusteredParticles
//! @ingroup samples_internal
//! @brief An ordered assembly of particles

class BA_CORE_API_ IClusteredParticles : public ICompositeSample
{
public:
    IClusteredParticles() {}
    virtual ~IClusteredParticles() {}

    //! clone method to allow for polymorphic copying
    virtual IClusteredParticles* clone() const  = 0;

    //! Returns a clone with inverted magnetic fields
    virtual IClusteredParticles* cloneInvertB() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor* visitor) const = 0;

    virtual void setAmbientMaterial(const IMaterial& material) = 0;
    virtual const IMaterial* getAmbientMaterial() const = 0;

    //! Creates a total form factor for the mesocrystal with a specific shape and content
    //! The bulk content of the mesocrystal is encapsulated by the IClusteredParticles object itself
    virtual IFormFactor* createTotalFormFactor(
        const IFormFactor&, const IRotation*, kvector_t /*translation*/) const = delete;

    //! Composes transformation with existing one
    virtual void applyRotation(const IRotation&) = delete;
};

#endif // ICLUSTEREDNANOPARTICLES_H
