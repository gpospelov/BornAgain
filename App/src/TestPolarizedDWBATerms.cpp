// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPolarizedDWBATerms.cpp
//! @brief     Implements class TestPolarizedDWBATerms.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestPolarizedDWBATerms.h"

#include "FormFactorDWBAPol.h"
#include "FormFactorDecoratorMaterial.h"
#include "FormFactorDWBA.h"
#include "FormFactorCylinder.h"
#include "LayerSpecularInfo.h"
#include "ScalarSpecularInfoMap.h"
#include "ScalarRTCoefficients.h"
#include "MaterialManager.h"

TestPolarizedDWBATerms::TestPolarizedDWBATerms()
: mp_matrix_ff(0)
, mp_scalar_ff(0)
, mp_specular_info(0)
, m_alpha_i(0.15)
, m_alpha_f(0.1)
{
    initWavevectors();
    const IMaterial *p_particle_material =
            MaterialManager::getHomogeneousMaterial(
            "particle", complex_t(1.0, 0.0));
    const IMaterial *p_ambient_material =
            MaterialManager::getHomogeneousMaterial(
            "ambient", complex_t(0.0, 0.0));
    FormFactorDecoratorMaterial *p_material_ff =
            new FormFactorDecoratorMaterial(new FormFactorCylinder(1.0, 1.0));
    p_material_ff->setMaterial(p_particle_material);
    p_material_ff->setAmbientMaterial(p_ambient_material);
    mp_matrix_ff = new FormFactorDWBAPol(p_material_ff);
    mp_scalar_ff = new FormFactorDWBA(p_material_ff->clone());
    mp_specular_info = new LayerSpecularInfo();
    initSpecularInfo();
    mp_matrix_ff->setSpecularInfo(*mp_specular_info);
    mp_scalar_ff->setSpecularInfo(*mp_specular_info);
}

void TestPolarizedDWBATerms::execute()
{
    mp_scalar_ff->calculateTerms(m_ki, m_kf_bin, m_alpha_i, m_alpha_f);
    mp_matrix_ff->calculateTerms(m_ki, m_kf_bin, m_kf_bin, m_alpha_i, m_alpha_f,
            0.1);

    std::cout << mp_scalar_ff->m_term_SR << std::endl;

    std::cout << mp_matrix_ff->m_M11_SR << std::endl;
    std::cout << mp_matrix_ff->m_M12_SR << std::endl;
    std::cout << mp_matrix_ff->m_M21_SR << std::endl;
    std::cout << mp_matrix_ff->m_M22_SR << std::endl;
}

void TestPolarizedDWBATerms::initWavevectors()
{
    m_ki.setLambdaAlphaPhi(0.21, -m_alpha_i, 0.0);

    Bin1D alpha_bin = { 0.99, 1.01 };
    Bin1D phi_bin = {0.99, 1.01 };
    m_kf_bin = Bin1DCVector(0.21, alpha_bin, phi_bin);
}

void TestPolarizedDWBATerms::initSpecularInfo()
{
    ScalarSpecularInfoMap *p_coeff_map = new ScalarSpecularInfoMap;
    mp_specular_info->addOutCoefficients(p_coeff_map);

    ScalarRTCoefficients rt_coeffs;

    rt_coeffs.lambda = complex_t(0.1, 0.001);
    rt_coeffs.kz = 30.0*rt_coeffs.lambda;
    rt_coeffs.phi_psi << complex_t(-0.2, 0.001), complex_t(0.9, 0.001);
    p_coeff_map->addCoefficients(rt_coeffs, m_alpha_f, 0.1);

    rt_coeffs.lambda = complex_t(0.2, 0.003);
    rt_coeffs.kz = -m_ki.z();
    rt_coeffs.phi_psi << complex_t(-0.18, 0.001), complex_t(0.7, 0.001);
    mp_specular_info->addInCoefficients(new ScalarRTCoefficients(rt_coeffs));
}
