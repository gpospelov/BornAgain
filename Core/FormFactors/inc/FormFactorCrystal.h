// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorCrystal.h
//! @brief     Defines class FormFactorCrystal.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCRYSTAL_H_
#define FORMFACTORCRYSTAL_H_

#include "IFormFactorBorn.h"
#include "Crystal.h"

//! Form factor for mesocrystals with a bulk crystal structure of particles

class BA_CORE_API_ FormFactorCrystal : public IFormFactorBorn
{
 public:
    FormFactorCrystal(
        const Crystal& p_crystal, const IFormFactor& meso_crystal_form_factor,
        const IMaterial *p_material);
    virtual ~FormFactorCrystal();

    virtual FormFactorCrystal *clone() const;

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual void setAmbientMaterial(const IMaterial *p_material);

    virtual complex_t evaluate(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin,
        double alpha_i, double alpha_f) const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

    virtual double getVolume() const;

 private:
    void calculateLargestReciprocalDistance();

    Lattice m_lattice;
    Particle *mp_particle;
    IFormFactor *mp_basis_form_factor;
    IFormFactor *mp_meso_form_factor;
    const IMaterial *mp_ambient_material;
    double m_max_rec_length;
};

#endif /* FORMFACTORCRYSTAL_H_ */


