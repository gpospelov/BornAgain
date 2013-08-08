// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDWBAPol.h
//! @brief     Defines class FormFactorDWBAPol.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDWBAPOL_H_
#define FORMFACTORDWBAPOL_H_

#include "IFormFactorDecorator.h"

#include <Eigen/Core>

class MagneticCoefficientsMap;

//! Evaluates a coherent sum of the 16 matrix DWBA terms in a polarized form factor

class FormFactorDWBAPol : public IFormFactorDecorator
{
public:
    FormFactorDWBAPol(IFormFactor *p_formfactor);
    virtual ~FormFactorDWBAPol();

    virtual FormFactorDWBAPol *clone() const;

    // Forwards to the evaluate function of the embedded form factor
    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f) const {
        (void)k_i;
        (void)k_f_bin;
        (void)alpha_i;
        (void)alpha_f;
        return mp_form_factor->evaluate(k_i, k_f_bin, alpha_i, alpha_f);
    }

    //! Calculates and returns a polarized form factor in DWBA
    virtual Eigen::Matrix2cd evaluatePol(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, double alpha_i, double alpha_f,
            double phi_f) const;

    //! Sets magnetic reflection/transmission info for polarized DWBA
    void setRTInfo(const MagneticCoefficientsMap& magnetic_coeff_map);

    //! Sets the material of the scatterer
    void setMaterial(const IMaterial *p_material) {
        mp_material = p_material;
    }

    //! Sets the material of the surrounding structure
    virtual void setAmbientMaterial(const IMaterial *p_material) {
        mp_ambient_material = p_material;
    }
protected:
    const SpecularMagnetic::LayerMatrixCoeff& getOutCoeffs(double alpha_f,
            double phi_f) const;
    void calculateTerms(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            double alpha_i, double alpha_f, double phi_f) const;

    Eigen::Matrix2cd getScatteringPotential(const kvector_t& k) const;

    MagneticCoefficientsMap *mp_magnetic_coeffs;
    const IMaterial *mp_material;
    const IMaterial *mp_ambient_material;
    //! The following matrices each contain the four polarization conditions
    //! (p->p, p->m, m->p, m->m)
    //! The first two indices indicate a scattering from the 1/2 eigenstate into
    //! the 1/2 eigenstate, while the capital indices indicate a reflection
    //! before and/or after the scattering event (first index is in-state,
    //! second is out-state; this also applies to the internal matrix indices)
    mutable Eigen::Matrix2cd m_M11_S;
    mutable Eigen::Matrix2cd m_M11_RS;
    mutable Eigen::Matrix2cd m_M11_SR;
    mutable Eigen::Matrix2cd m_M11_RSR;
    mutable Eigen::Matrix2cd m_M12_S;
    mutable Eigen::Matrix2cd m_M12_RS;
    mutable Eigen::Matrix2cd m_M12_SR;
    mutable Eigen::Matrix2cd m_M12_RSR;
    mutable Eigen::Matrix2cd m_M21_S;
    mutable Eigen::Matrix2cd m_M21_RS;
    mutable Eigen::Matrix2cd m_M21_SR;
    mutable Eigen::Matrix2cd m_M21_RSR;
    mutable Eigen::Matrix2cd m_M22_S;
    mutable Eigen::Matrix2cd m_M22_RS;
    mutable Eigen::Matrix2cd m_M22_SR;
    mutable Eigen::Matrix2cd m_M22_RSR;
};

inline const SpecularMagnetic::LayerMatrixCoeff& FormFactorDWBAPol::getOutCoeffs(
        double alpha_f, double phi_f) const
{
    MagneticCoefficientsMap::container_phi_t &phi_coeffs =
            (*mp_magnetic_coeffs)[alpha_f];
    return phi_coeffs[phi_f];
}

#endif /* FORMFACTORDWBAPOL_H_ */
