#ifndef NANOPARTICLECRYSTALFORMFACTOR_H_
#define NANOPARTICLECRYSTALFORMFACTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   NanoParticleCrystalFormFactor.h
//! @brief  Definition of NanoParticleCrystalFormFactor
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "IFormFactor.h"
#include "NanoParticleCrystal.h"
#include "Types.h"

//- -------------------------------------------------------------------
//! @class NanoParticleCrystalFormFactor
//! @brief Definition of a form factor for mesocrystals with a bulk crystal structure of nano particles
//- -------------------------------------------------------------------
class NanoParticleCrystalFormFactor : public IBornFormFactor
{
public:
    NanoParticleCrystalFormFactor(const NanoParticleCrystal *p_crystal,
            const IFormFactor &meso_crystal_form_factor, complex_t ambient_refractive_index);
    virtual ~NanoParticleCrystalFormFactor();

    virtual NanoParticleCrystalFormFactor *clone() const;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

protected:
    virtual complex_t evaluate_for_q(cvector_t q) const;
private:
    void calculateLargestReciprocalDistance();
//    void initializeDiffuseNanoparticleFormfactors();
    Lattice m_lattice;
    NanoParticle *mp_nano_particle;
    IFormFactor *mp_basis_form_factor;
    IFormFactor *mp_meso_form_factor;
    complex_t m_ambient_refractive_index;
    double m_max_rec_length;
//    std::vector<IFormFactor *> m_diffuse_nanoparticle_ffs;
};


#endif /* NANOPARTICLECRYSTALFORMFACTOR_H_ */
