// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IClusteredParticles.h
//! @brief     Defines class IClusteredParticles.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICLUSTEREDPARTICLES_H_
#define ICLUSTEREDPARTICLES_H_

#include "IFormFactor.h"
#include "ICompositeSample.h"
#include "ParticleInfo.h"
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
    virtual IClusteredParticles *clone() const  = 0;

    //! Returns a clone with inverted magnetic fields
    virtual IClusteredParticles *cloneInvertB() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const = 0;

    virtual void setAmbientMaterial(const IMaterial *p_ambient_material) = 0;
    virtual const IMaterial* getAmbientMaterial() const = 0;

    //! @brief create a total form factor for the mesocrystal with a specific
    //! shape and content
    //! @param meso_crystal_form_factor  the form factor describing the shape
    //! of the mesocrystal
    //! @param ambient_refractive_index  the refractive index of the
    //! ambient material
    //! The bulk content of the mesocrystal is encapsulated by the
    //! IClusteredParticles object itself
    virtual IFormFactor *createTotalFormFactor(
           const IFormFactor& meso_crystal_form_factor,
           const IMaterial &p_ambient_material,
           complex_t wavevector_scattering_factor) const
    {
        (void)meso_crystal_form_factor;
        (void)p_ambient_material;
        (void)wavevector_scattering_factor;
        throw NotImplementedException(
                "IClusteredParticles::createTotalFormFactor() "
                "-> NotImplementedException");
    }

    //! Composes transformation with existing one
    virtual void applyTransformation(const Geometry::Transform3D& transform)
    {
        (void)transform;
        throw NotImplementedException(
                "IClusteredParticles::applyTransformation() "
                "-> NotImplementedException");
    }

    //! Gets transformation
    virtual const Geometry::Transform3D *getTransform() const
    {
        return 0;
    }

};

#endif /* ICLUSTEREDNANOPARTICLES_H_ */


