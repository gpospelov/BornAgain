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
#include "Materials.h"

TestPolarizedDWBATerms::TestPolarizedDWBATerms()
: mp_matrix_ff(0)
, mp_scalar_ff(0)
, mp_specular_info(0)
, m_alpha_i(0.15)
, m_alpha_f(0.1)
{
    mp_multilayer = new MultiLayer;

    HomogeneousMaterial air_material("Air", 0., 0.);
    HomogeneousMaterial substrate_material("Substrate", 0.2, 0.02);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);

    mp_multilayer->addLayer(air_layer);
    mp_multilayer->addLayer(substrate_layer);

    initWavevectors();
    HomogeneousMaterial particle_material("particle", complex_t(1.0, 0.0));
    HomogeneousMaterial ambient_material("ambient", complex_t(0.0, 0.0));

    FormFactorDecoratorMaterial *p_material_ff =
            new FormFactorDecoratorMaterial(new FormFactorCylinder(1.0, 1.0));
    p_material_ff->setMaterial(&particle_material);
    p_material_ff->setAmbientMaterial(&ambient_material);
    mp_matrix_ff = new FormFactorDWBAPol(p_material_ff);
    mp_scalar_ff = new FormFactorDWBA(p_material_ff->clone());
    mp_specular_info = new LayerSpecularInfo();
    initSpecularInfo();
    mp_matrix_ff->setSpecularInfo(*mp_specular_info);
    mp_scalar_ff->setSpecularInfo(*mp_specular_info);
}

void TestPolarizedDWBATerms::execute()
{
    Bin1D alpha_f_bin = { m_alpha_f, m_alpha_f };
    Bin1D zero_bin = { 0.0, 0.0 };
    mp_scalar_ff->calculateTerms(m_ki, m_kf_bin, alpha_f_bin);
    mp_matrix_ff->calculateTerms(m_ki, m_kf_bin, alpha_f_bin, zero_bin);

    std::cout << mp_scalar_ff->m_term_SR << std::endl;

    std::cout << mp_matrix_ff->m_M11_SR << std::endl;
    std::cout << mp_matrix_ff->m_M12_SR << std::endl;
    std::cout << mp_matrix_ff->m_M21_SR << std::endl;
    std::cout << mp_matrix_ff->m_M22_SR << std::endl;
}

void TestPolarizedDWBATerms::initWavevectors()
{
    m_ki.setLambdaAlphaPhi(0.21, -m_alpha_i, 0.0);

    Bin1D alpha_bin = { m_alpha_f, m_alpha_f };
    Bin1D phi_bin = { 0.0, 0.0 };
    m_kf_bin = Bin1DCVector(0.21, alpha_bin, phi_bin);
}

void TestPolarizedDWBATerms::initSpecularInfo()
{
    ScalarSpecularInfoMap *p_coeff_map =
            new ScalarSpecularInfoMap(mp_multilayer, 0, 1.0);
    mp_specular_info->addOutCoefficients(p_coeff_map);

    ScalarRTCoefficients rt_coeffs;

    rt_coeffs.lambda = complex_t(0.2, 0.003);
    rt_coeffs.kz = -m_ki.z();
    rt_coeffs.t_r << complex_t(-0.18, 0.001), complex_t(0.7, 0.001);
    mp_specular_info->addInCoefficients(new ScalarRTCoefficients(rt_coeffs));
}
