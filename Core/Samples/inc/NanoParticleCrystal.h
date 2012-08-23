#ifndef NANOPARTICLECRYSTAL_H_
#define NANOPARTICLECRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleCrystal.h
//! @brief  Definition of NanoParticleCrystal class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "IClusteredNanoParticles.h"
#include "NanoParticle.h"
#include "Lattice.h"

//- -------------------------------------------------------------------
//! @class NanoParticleCrystal
//! @brief Definition of a crystal structure with a form factor as a basis
//- -------------------------------------------------------------------
class NanoParticleCrystal : public IClusteredNanoParticles
{
public:
     //! @brief constructor
     //! @param basis_form_factor  the form factor of the basis which is repeated in the lattice structure
     //! @param lattice  the crystal lattice, described by its basis vectors
     NanoParticleCrystal(const NanoParticle &nano_particle, const Lattice &lattice);
    ~NanoParticleCrystal();

    virtual NanoParticleCrystal *clone() const;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index)
    {
        mp_nano_particle->setAmbientRefractiveIndex(refractive_index);
    }

    virtual IFormFactor *createTotalFormFactor(const IFormFactor &meso_crystal_form_factor
            , complex_t ambient_refractive_index) const;

    Lattice getLattice() const { return m_lattice; }
    NanoParticle *createNanoParticle() const { return mp_nano_particle->clone(); }

    const NanoParticle *getNanoParticle() const { return mp_nano_particle; }

private:
    Lattice m_lattice;
    NanoParticle *mp_nano_particle;
};


#endif /* NANOPARTICLECRYSTAL_H_ */
