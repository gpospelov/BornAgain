// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorPol.h
//! @brief     Defines class FormFactorPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPOL_H_
#define FORMFACTORPOL_H_

#include "IFormFactorDecorator.h"
#include "SpecularMagnetic.h"
#include "LayerSpecularInfo.h"

#include <Eigen/Core>

//! Evaluates a polarized form factor (which is a 2x2 matrix)

class FormFactorPol : public IFormFactorDecorator
{
public:
    FormFactorPol(IFormFactor *p_formfactor)
        : IFormFactorDecorator(p_formfactor)
        , mp_specular_info(0), mp_material(0), mp_ambient_material(0) {}
    virtual ~FormFactorPol();

    virtual FormFactorPol *clone() const;

    // Forwards to the evaluate function of the embedded form factor
    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const {
        return mp_form_factor->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
    }

    //! Calculates and returns a polarized form factor calculation in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
            double alpha_i, double alpha_f, double phi_f) const;

    //! Sets magnetic reflection/transmission info for polarized DWBA
    void setRTInfo(const LayerSpecularInfo& layer_specular_info);

    //! Sets the material of the scatterer
    void setMaterial(const IMaterial *p_material) {
        mp_material = p_material;
    }

    //! Sets the material of the surrounding structure
    virtual void setAmbientMaterial(const IMaterial *p_material) {
        mp_ambient_material = p_material;
    }
protected:
    const ILayerRTCoefficients *getOutCoeffs(double alpha_f,
            double phi_f) const;
    LayerSpecularInfo *mp_specular_info;
    const IMaterial *mp_material;
    const IMaterial *mp_ambient_material;
};

inline const ILayerRTCoefficients *FormFactorPol::getOutCoeffs(
        double alpha_f, double phi_f) const
{
    return mp_specular_info->getOutCoefficients(alpha_f, phi_f);
}

#endif /* FORMFACTORPOL_H_ */
