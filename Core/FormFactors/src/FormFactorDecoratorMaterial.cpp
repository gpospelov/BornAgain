// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorDecoratorMaterial.cpp
//! @brief     Implements class FormFactorDecoratorMaterial.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorMaterial.h"

FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial()
{
}

FormFactorDecoratorMaterial* FormFactorDecoratorMaterial::clone() const
{
    FormFactorDecoratorMaterial *p_result = new FormFactorDecoratorMaterial(
            mp_formfactor->clone(), m_wavevector_scattering_factor);
    p_result->setName(getName());
    p_result->setMaterial(mp_material);
    p_result->setAmbientMaterial(mp_ambient_material);
    return p_result;
}

Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f1_bin, const Bin1DCVector& k_f2_bin,
        double alpha_i, double alpha_f, double phi_f) const
{
    (void)k_f2_bin;
    (void)phi_f;
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0,1) = 1.0;
    time_reverse_conj(1,0) = -1.0;
    // the interaction and time reversal taken together:
    double k_mag2 = std::abs(k_i.magxy2())/std::cos(alpha_i)/std::cos(alpha_i);
    Eigen::Matrix2cd V_eff = m_wavevector_scattering_factor * time_reverse_conj
            * (mp_material->getScatteringMatrix(k_mag2) -
               mp_ambient_material->getScatteringMatrix(k_mag2));
    return mp_formfactor->evaluate(k_i, k_f1_bin, alpha_i, alpha_f) * V_eff;
}
