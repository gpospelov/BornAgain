// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorDecoratorMaterial.cpp
//! @brief     Defines class .
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorDecoratorMaterial.h"

FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(
        IFormFactor* p_form_factor, complex_t wavevector_scattering_factor)
: FormFactorDecoratorFactor(p_form_factor, 1.0)
, m_wavevector_scattering_factor(wavevector_scattering_factor)
, mP_material(0)
, mP_ambient_material(0)
{
    setName("FormFactorDecoratorMaterial");
}

FormFactorDecoratorMaterial::~FormFactorDecoratorMaterial()
{
}

FormFactorDecoratorMaterial *FormFactorDecoratorMaterial::clone() const
{
    FormFactorDecoratorMaterial *result =
            new FormFactorDecoratorMaterial(mp_form_factor->clone(),
                    m_wavevector_scattering_factor);
    result->setMaterial(mP_material.get());
    result->setAmbientMaterial(mP_ambient_material.get());
    result->setName(getName());
    return result;
}

void FormFactorDecoratorMaterial::setMaterial(const IMaterial* p_material)
{
    if (p_material) {
        mP_material.reset(p_material->clone());
    }
    m_factor = getRefractiveIndexFactor();
}

void FormFactorDecoratorMaterial::setAmbientMaterial(
        const IMaterial *p_material)
{
    if (p_material) {
        mP_ambient_material.reset(p_material->clone());
    }
    m_factor = getRefractiveIndexFactor();
}

complex_t FormFactorDecoratorMaterial::getAmbientRefractiveIndex() const
{
    if (mP_ambient_material.get()) {
        return mP_ambient_material->getRefractiveIndex();
    }
    return 1.0;
}

Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    (void)phi_f_bin;
    // the conjugated linear part of time reversal operator T
    // (T=UK with K complex conjugate operator and U is linear)
    Eigen::Matrix2cd time_reverse_conj = Eigen::Matrix2cd::Zero();
    time_reverse_conj(0,1) = 1.0;
    time_reverse_conj(1,0) = -1.0;
    // the interaction and time reversal taken together:
    double k_mag2 = 4.0 * M_PI * m_wavevector_scattering_factor.real();
    Eigen::Matrix2cd V_eff = m_wavevector_scattering_factor * time_reverse_conj
            * (mP_material->getScatteringMatrix(k_mag2) -
               mP_ambient_material->getScatteringMatrix(k_mag2));
    return mp_form_factor->evaluate(k_i, k_f_bin, alpha_f_bin) * V_eff;
}

complex_t FormFactorDecoratorMaterial::getRefractiveIndexFactor() const
{
    if (mP_material.get() && mP_ambient_material.get()) {
        complex_t particle_index = mP_material->getRefractiveIndex();
        complex_t ambient_index = mP_ambient_material->getRefractiveIndex();
        return m_wavevector_scattering_factor *
                (particle_index*particle_index - ambient_index*ambient_index);
    }
    else return m_wavevector_scattering_factor;
}

