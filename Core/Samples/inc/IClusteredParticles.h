#ifndef ICLUSTEREDPARTICLES_H_
#define ICLUSTEREDPARTICLES_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IClusteredParticles.h
//! @brief  Definition of IClusteredParticles interface
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "IFormFactor.h"
#include "ICompositeSample.h"
#include "ParticleInfo.h"
#include "Transform3D.h"
#include "Exceptions.h"

//- -------------------------------------------------------------------
//! @class IClusteredParticles
//! @brief Definition of an interface, representing an ordered assembly of particles
//- -------------------------------------------------------------------
class IClusteredParticles : public ICompositeSample
{
public:
    virtual ~IClusteredParticles() {}
    //! clone method to allow for polymorphic copying
    virtual IClusteredParticles *clone() const=0;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index)=0;

    //! @brief create a total form factor for the mesocrystal with a specific shape and content
    //! @param meso_crystal_form_factor  the form factor describing the shape of the mesocrystal
    //! @param ambient_refractive_index  the refractive index of the ambient material
    //! The bulk content of the mesocrystal is encapsulated by the IClusteredParticles object itself
    virtual IFormFactor *createTotalFormFactor(const IFormFactor &meso_crystal_form_factor,
            complex_t ambient_refractive_index) const=0;

//    virtual std::vector<DiffuseNanoParticleInfo *> *createDiffuseNanoParticleInfo(double depth, double weight,
//                const Geometry::Transform3D &transform, double meso_volume) const=0;

    virtual std::vector<DiffuseNanoParticleInfo *> *createDiffuseNanoParticleInfo(double depth, double weight,
                const Geometry::Transform3D &transform, double meso_volume) {
        (void)depth;
        (void)weight;
        (void)transform;
        (void)meso_volume;
        throw NotImplementedException("IClusteredNanoParticles::createDiffuseNanoParticleInfo()");
    }

};


#endif /* ICLUSTEREDNANOPARTICLES_H_ */
