// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactors/FormFactorDWBAPol.cpp
//! @brief     Defines class FormFactorDWBAPol.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BornAgainNamespace.h"
#include "ILayerRTCoefficients.h"
#include "FormFactorDWBAPol.h"

FormFactorDWBAPol::FormFactorDWBAPol(const IFormFactor &form_factor)
: mp_form_factor(form_factor.clone())
, mp_in_coeffs(0)
, mp_out_coeffs(0)
{
    setName(BornAgain::FormFactorPolarizedDWBAType);
}

FormFactorDWBAPol::~FormFactorDWBAPol()
{
}

FormFactorDWBAPol* FormFactorDWBAPol::clone() const
{
    FormFactorDWBAPol *p_result = new FormFactorDWBAPol(*mp_form_factor);
    p_result->setSpecularInfo(mp_in_coeffs, mp_out_coeffs);
    return p_result;
}

complex_t FormFactorDWBAPol::evaluate(const WavevectorInfo&) const
{
    throw Exceptions::NotImplementedException("FormFactorDWBAPol::evaluate: "
            "should never be called for matrix interactions");
}

Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const WavevectorInfo& wavevectors) const
{
    calculateTerms(wavevectors);
    Eigen::Matrix2cd result =
            m_M11_S + m_M11_RS + m_M11_SR + m_M11_RSR +
            m_M12_S + m_M12_RS + m_M12_SR + m_M12_RSR +
            m_M21_S + m_M21_RS + m_M21_SR + m_M21_RSR +
            m_M22_S + m_M22_RS + m_M22_SR + m_M22_RSR;
    return result;
}

double FormFactorDWBAPol::getVolume() const
{
    if (mp_form_factor) {
        return mp_form_factor->getVolume();
    }
    return 0.0;
}

double FormFactorDWBAPol::getRadius() const
{
    if (mp_form_factor) {
        return mp_form_factor->getRadius();
    }
    return 0.0;
}

void FormFactorDWBAPol::setSpecularInfo(const ILayerRTCoefficients* p_in_coeffs,
                                        const ILayerRTCoefficients* p_out_coeffs)
{
    mp_in_coeffs = p_in_coeffs;
    mp_out_coeffs = p_out_coeffs;
}

void FormFactorDWBAPol::calculateTerms(const WavevectorInfo& wavevectors) const
{
    double wavelength = wavevectors.getWavelength();
    // the required wavevectors inside the layer for
    // different eigenmodes and in- and outgoing wavevector;
    complex_t kix = wavevectors.getKi().x();
    complex_t kiy = wavevectors.getKi().y();
    cvector_t ki_1R(kix, kiy, mp_in_coeffs->getKz()(0));
    cvector_t ki_1T(kix, kiy, -mp_in_coeffs->getKz()(0));
    cvector_t ki_2R(kix, kiy, mp_in_coeffs->getKz()(1));
    cvector_t ki_2T(kix, kiy, -mp_in_coeffs->getKz()(1));

    cvector_t kf_1R = wavevectors.getKf();
    kf_1R.setZ(-(complex_t)mp_out_coeffs->getKz()(0));
    cvector_t kf_1T = kf_1R;
    kf_1T.setZ((complex_t)mp_out_coeffs->getKz()(0));
    cvector_t kf_2R = kf_1R;
    kf_2R.setZ(-(complex_t)mp_out_coeffs->getKz()(1));
    cvector_t kf_2T = kf_1R;
    kf_2T.setZ((complex_t)mp_out_coeffs->getKz()(1));
    // now each of the 16 matrix terms of the polarized DWBA is calculated:
    // NOTE: when the underlying reflection/transmission coefficients are
    // scalar, the eigenmodes have identical eigenvalues and spin polarization
    // is used as a basis; in this case however the matrices get mixed:
    //     real m_M11 = calculated m_M12
    //     real m_M12 = calculated m_M11
    //     real m_M21 = calculated m_M22
    //     real m_M22 = calculated m_M21
    // since both eigenvalues are identical, this does not influence the result.
    Eigen::Matrix2cd ff_BA;

    // eigenmode 1 -> eigenmode 1: direct scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1T, kf_1T, wavelength));
    m_M11_S(0,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M11_S(0,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M11_S(1,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    m_M11_S(1,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 1: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1R, kf_1T, wavelength));
    m_M11_RS(0,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M11_RS(0,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M11_RS(1,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->R1min());
    m_M11_RS(1,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->R1min());
    // eigenmode 1 -> eigenmode 1: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1T, kf_1R, wavelength));
    m_M11_SR(0,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M11_SR(0,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M11_SR(1,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    m_M11_SR(1,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 1: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1R, kf_1R, wavelength));
    m_M11_RSR(0,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M11_RSR(0,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M11_RSR(1,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->R1min());
    m_M11_RSR(1,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->R1min());

    // eigenmode 1 -> eigenmode 2: direct scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1T, kf_2T, wavelength));
    m_M12_S(0,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M12_S(0,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M12_S(1,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    m_M12_S(1,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 2: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1R, kf_2T, wavelength));
    m_M12_RS(0,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M12_RS(0,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M12_RS(1,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->R1min());
    m_M12_RS(1,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->R1min());
    // eigenmode 1 -> eigenmode 2: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1T, kf_2R, wavelength));
    m_M12_SR(0,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M12_SR(0,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->T1plus());
    m_M12_SR(1,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    m_M12_SR(1,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->T1min());
    // eigenmode 1 -> eigenmode 2: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_1R, kf_2R, wavelength));
    m_M12_RSR(0,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M12_RSR(0,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->R1plus());
    m_M12_RSR(1,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->R1min());
    m_M12_RSR(1,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->R1min());

    // eigenmode 2 -> eigenmode 1: direct scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2T, kf_1T, wavelength));
    m_M21_S(0,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M21_S(0,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M21_S(1,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    m_M21_S(1,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 1: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2R, kf_1T, wavelength));
    m_M21_RS(0,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M21_RS(0,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M21_RS(1,0) = - mp_out_coeffs->T1min().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
    m_M21_RS(1,1) =  mp_out_coeffs->T1plus().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
    // eigenmode 2 -> eigenmode 1: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2T, kf_1R, wavelength));
    m_M21_SR(0,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M21_SR(0,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M21_SR(1,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    m_M21_SR(1,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 1: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2R, kf_1R, wavelength));
    m_M21_RSR(0,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M21_RSR(0,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M21_RSR(1,0) = - mp_out_coeffs->R1min().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
    m_M21_RSR(1,1) =  mp_out_coeffs->R1plus().conjugate().dot(ff_BA * mp_in_coeffs->R2min());

    // eigenmode 2 -> eigenmode 2: direct scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2T, kf_2T, wavelength));
    m_M22_S(0,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M22_S(0,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M22_S(1,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    m_M22_S(1,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 2: reflection and then scattering
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2R, kf_2T, wavelength));
    m_M22_RS(0,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M22_RS(0,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M22_RS(1,0) = - mp_out_coeffs->T2min().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
    m_M22_RS(1,1) =  mp_out_coeffs->T2plus().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
    // eigenmode 2 -> eigenmode 2: scattering and then reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2T, kf_2R, wavelength));
    m_M22_SR(0,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M22_SR(0,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->T2plus());
    m_M22_SR(1,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    m_M22_SR(1,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->T2min());
    // eigenmode 2 -> eigenmode 2: reflection, scattering and again reflection
    ff_BA = mp_form_factor->evaluatePol(WavevectorInfo(ki_2R, kf_2R, wavelength));
    m_M22_RSR(0,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M22_RSR(0,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->R2plus());
    m_M22_RSR(1,0) = - mp_out_coeffs->R2min().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
    m_M22_RSR(1,1) =  mp_out_coeffs->R2plus().conjugate().dot(ff_BA * mp_in_coeffs->R2min());
}
