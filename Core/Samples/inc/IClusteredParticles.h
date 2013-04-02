// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/IClusteredParticles.h
//! @brief     Defines class IClusteredParticles.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICLUSTEREDPARTICLES_H_
#define ICLUSTEREDPARTICLES_H_

#include "IFormFactor.h"
#include "ICompositeSample.h"
#include "ParticleInfo.h"
#include "Exceptions.h"
#include "DiffuseParticleInfo.h"

//! An ordered assembly of particles

class IClusteredParticles : public ICompositeSample
{
 public:
    IClusteredParticles() {}
    virtual ~IClusteredParticles() {}
    //! clone method to allow for polymorphic copying
    virtual IClusteredParticles *clone() const { throw NotImplementedException("IClusteredParticles::clone() -> Error! Not implemented exception"); }

    virtual void setAmbientRefractiveIndex(complex_t refractive_index)=0;

    //! @brief create a total form factor for the mesocrystal with a specific shape and content
    //! @param meso_crystal_form_factor  the form factor describing the shape of the mesocrystal
    //! @param ambient_refractive_index  the refractive index of the ambient material
    //! The bulk content of the mesocrystal is encapsulated by the IClusteredParticles object itself
//    virtual IFormFactor *createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
//            complex_t ambient_refractive_index) const=0;

//    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(const ParticleInfo& parent_info) const=0;


    virtual IFormFactor *createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
            complex_t ambient_refractive_index) const
    {
        (void)meso_crystal_form_factor;
        (void)ambient_refractive_index;
        throw NotImplementedException("IClusteredParticles::createTotalFormFactor() -> NotImplementedException");
    }

    virtual std::vector<DiffuseParticleInfo *> *createDiffuseParticleInfo(const ParticleInfo& parent_info) const
    {
        (void)parent_info;
        throw NotImplementedException("IClusteredParticles::createDiffuseParticleInfo() -> NotImplementedException");
    }

};

#endif /* ICLUSTEREDNANOPARTICLES_H_ */


