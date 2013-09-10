// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorMaterial.h
//! @brief     Defines class FormFactorDecoratorMaterial.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORMATERIAL_H_
#define FORMFACTORDECORATORMATERIAL_H_

#include "FormFactorPol.h"
#include "HomogeneousMagneticMaterial.h"

//! Evaluates a polarized form factor (which is a 2x2 matrix)

class BA_CORE_API_ FormFactorDecoratorMaterial : public FormFactorPol
{
public:
    FormFactorDecoratorMaterial(IFormFactor *p_formfactor,
            complex_t wavevector_scattering_factor=1.0)
        : mp_formfactor(p_formfactor)
        , mp_material(0), mp_ambient_material(0)
        , m_wavevector_scattering_factor(wavevector_scattering_factor) {}
    virtual ~FormFactorDecoratorMaterial();

    virtual FormFactorDecoratorMaterial *clone() const;

#ifndef GCCXML_SKIP_THIS
    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, double alpha_f, double phi_f) const;
#endif
    //! Sets the material of the scatterer
    void setMaterial(const IMaterial *p_material) {
        mp_material = p_material;
    }

    //! Sets the material of the surrounding structure
    virtual void setAmbientMaterial(const IMaterial *p_material) {
        mp_ambient_material = p_material;
    }
protected:
    IFormFactor *mp_formfactor;
    const IMaterial *mp_material;
    const IMaterial *mp_ambient_material;
    complex_t m_wavevector_scattering_factor;
};

#endif /* FORMFACTORDECORATORMATERIAL_H_ */
