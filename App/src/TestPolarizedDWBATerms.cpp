// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestPolarizedDWBATerms.cpp
//! @brief     Implements class TestPolarizedDWBATerms.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
#include "Exceptions.h"

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

    FormFactorDecoratorMaterial material_ff(FormFactorCylinder(1.0, 1.0));
    material_ff.setMaterial(particle_material);
    material_ff.setAmbientMaterial(ambient_material);
    mp_matrix_ff = new FormFactorDWBAPol(material_ff);
    mp_scalar_ff = new FormFactorDWBA(material_ff);
    mp_specular_info = new LayerSpecularInfo();
    initSpecularInfo();
}

void TestPolarizedDWBATerms::execute()
{
    throw NotImplementedException("TestPolarizedDWBATerms::execute()");

//    Bin1D alpha_f_bin(m_alpha_f, m_alpha_f);
//    ScalarRTCoefficients in_coeffs;
//    in_coeffs.lambda = complex_t(0.2, 0.003);
//    in_coeffs.kz = -m_ki.z();
//    in_coeffs.t_r << complex_t(-0.18, 0.001), complex_t(0.7, 0.001);
//    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
//            mp_specular_info->getOutCoefficients(
//                    alpha_f_bin.getMidPoint(), 0.0, 1.0) );
//    mp_scalar_ff->setSpecularInfo(&in_coeffs, P_out_coeffs.get());
//    mp_matrix_ff->setSpecularInfo(&in_coeffs, P_out_coeffs.get());
//    Bin1D zero_bin;
//    mp_scalar_ff->calculateTerms(m_ki, m_kf_bin, alpha_f_bin);
//    mp_matrix_ff->calculateTerms(m_ki, m_kf_bin, alpha_f_bin, zero_bin);

//    std::cout << mp_scalar_ff->m_term_SR << std::endl;

//    std::cout << mp_matrix_ff->m_M11_SR << std::endl;
//    std::cout << mp_matrix_ff->m_M12_SR << std::endl;
//    std::cout << mp_matrix_ff->m_M21_SR << std::endl;
//    std::cout << mp_matrix_ff->m_M22_SR << std::endl;
}

void TestPolarizedDWBATerms::initWavevectors()
{
    m_ki.setLambdaAlphaPhi(0.21, -m_alpha_i, 0.0);

    Bin1D alpha_bin( m_alpha_f, m_alpha_f );
    Bin1D phi_bin;
    m_kf_bin = Bin1DCVector(0.21, alpha_bin, phi_bin);
}

void TestPolarizedDWBATerms::initSpecularInfo()
{
    ScalarSpecularInfoMap *p_coeff_map =
            new ScalarSpecularInfoMap(mp_multilayer, 0);
    mp_specular_info->addRTCoefficients(p_coeff_map);
}
