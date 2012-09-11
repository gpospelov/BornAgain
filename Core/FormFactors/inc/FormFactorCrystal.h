#ifndef FORMFACTORCRYSTAL_H_
#define FORMFACTORCRYSTAL_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorCrystal.h
//! @brief  Definition of CrystalFormFactor
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "IFormFactor.h"
#include "Crystal.h"
#include "Types.h"

//- -------------------------------------------------------------------
//! @class FormFactorCrystal
//! @brief Definition of a form factor for mesocrystals with a bulk crystal structure of particles
//- -------------------------------------------------------------------
class FormFactorCrystal : public IFormFactorBorn
{
public:
    FormFactorCrystal(const Crystal *p_crystal,
            const IFormFactor &meso_crystal_form_factor, complex_t ambient_refractive_index);
    virtual ~FormFactorCrystal();

    virtual FormFactorCrystal *clone() const;

    virtual void setAmbientRefractiveIndex(complex_t refractive_index);

protected:
    virtual complex_t evaluate_for_q(cvector_t q) const;
private:
    void calculateLargestReciprocalDistance();
    Lattice m_lattice;
    Particle *mp_particle;
    IFormFactor *mp_basis_form_factor;
    IFormFactor *mp_meso_form_factor;
    complex_t m_ambient_refractive_index;
    double m_max_rec_length;
};


#endif /* FORMFACTORCRYSTAL_H_ */