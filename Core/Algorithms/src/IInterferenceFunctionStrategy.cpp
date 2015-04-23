// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IInterferenceFunctionStrategy.h"
#include "MemberFunctionMCMiserIntegrator.h"

#include <boost/scoped_ptr.hpp>

#include <ScalarRTCoefficients.h>

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(SimulationParameters sim_params)
    : m_sim_params(sim_params)
{
}

void IInterferenceFunctionStrategy::init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
                                         const SafePointerVector<IInterferenceFunction> &ifs)
{
    m_ff_infos = form_factor_infos;
    m_ifs = ifs;
}

void IInterferenceFunctionStrategy::setSpecularInfo(const LayerSpecularInfo &specular_info)
{
    if (mP_specular_info.get() != &specular_info) {
        mP_specular_info.reset(specular_info.clone());
    }
}

double IInterferenceFunctionStrategy::evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
                                               Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    if (m_sim_params.m_mc_integration && m_sim_params.m_mc_points > 1
        && (alpha_f_bin.getBinSize() != 0.0 || phi_f_bin.getBinSize() != 0.0)) {
        return MCIntegratedEvaluate(k_i, alpha_f_bin, phi_f_bin);
    }
    calculateFormFactorList(k_i, k_f_bin, alpha_f_bin);
    return evaluateForList(k_i, k_f_bin, m_ff);
}

double IInterferenceFunctionStrategy::evaluate(const cvector_t &k_i,
                                               const Eigen::Matrix2cd &beam_density,
                                               const Bin1DCVector &k_f_bin,
                                               const Eigen::Matrix2cd &detector_operator,
                                               Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    if (m_sim_params.m_mc_integration && m_sim_params.m_mc_points > 0) {
        return MCIntegratedEvaluatePol(k_i, beam_density, detector_operator, alpha_f_bin, phi_f_bin);
    }
    double result;
    calculateFormFactorLists(k_i, k_f_bin, alpha_f_bin, phi_f_bin);
    result = evaluateForMatrixList(k_i, beam_density, k_f_bin, detector_operator, m_ff_pol);
    return result;
}

void IInterferenceFunctionStrategy::calculateFormFactorList(const cvector_t &k_i,
                                                            const Bin1DCVector &k_f_bin,
                                                            Bin1D alpha_f_bin) const
{
    clearFormFactorLists();
    const ILayerRTCoefficients *p_in_coeffs = mP_specular_info->getInCoefficients();
    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(alpha_f_bin.getMidPoint(), 0.0));
    SafePointerVector<FormFactorInfo>::const_iterator it = m_ff_infos.begin();
    while (it != m_ff_infos.end()) {
        (*it)->mp_ff->setSpecularInfo(p_in_coeffs, P_out_coeffs.get());
        complex_t ff_mat = (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_f_bin);
        m_ff.push_back(ff_mat);
        ++it;
    }
}

void IInterferenceFunctionStrategy::calculateFormFactorLists(const cvector_t &k_i,
                                                             const Bin1DCVector &k_f_bin,
                                                             Bin1D alpha_f_bin,
                                                             Bin1D phi_f_bin) const
{
    clearFormFactorLists();
    const ILayerRTCoefficients *p_in_coeffs = mP_specular_info->getInCoefficients();
    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(alpha_f_bin.getMidPoint(), phi_f_bin.getMidPoint()));
    SafePointerVector<FormFactorInfo>::const_iterator it = m_ff_infos.begin();
    while (it != m_ff_infos.end()) {
        (*it)->mp_ff->setSpecularInfo(p_in_coeffs, P_out_coeffs.get());
        Eigen::Matrix2cd ff_mat = (*it)->mp_ff->evaluatePol(k_i, k_f_bin, alpha_f_bin, phi_f_bin);
        m_ff_pol.push_back(ff_mat);
        ++it;
    }
}

void IInterferenceFunctionStrategy::clearFormFactorLists() const
{
    m_ff.clear();
    m_ff_pol.clear();
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluate(const cvector_t &k_i, Bin1D alpha_f_bin,
                                                           Bin1D phi_f_bin) const
{
    IntegrationParamsAlpha mc_int_pars = getIntegrationParams(k_i, alpha_f_bin, phi_f_bin);
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy>::mem_function p_function
        = &IInterferenceFunctionStrategy::evaluate_for_fixed_angles;
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy> mc_integrator(p_function, this,
                                                                                 2);
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    double result = mc_integrator.integrate(min_array, max_array, (void *)&mc_int_pars,
                                            m_sim_params.m_mc_points);
    double integration_constant;
    if (alpha_f_bin.getBinSize() == 0.0) {
        integration_constant = 1.0 / std::cos(alpha_f_bin.m_lower);
    } else {
        integration_constant = alpha_f_bin.getBinSize()
                               / (std::sin(alpha_f_bin.m_upper) - std::sin(alpha_f_bin.m_lower));
    }
    return result * std::abs(integration_constant);
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluatePol(
    const cvector_t &k_i, const Eigen::Matrix2cd &beam_density,
    const Eigen::Matrix2cd &detector_operator, Bin1D alpha_f_bin, Bin1D phi_f_bin) const
{
    double result;
    IntegrationParamsAlpha mc_int_pars = getIntegrationParams(k_i, alpha_f_bin, phi_f_bin);
    mc_int_pars.beam_density = beam_density;
    mc_int_pars.detector_operator = detector_operator;
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy>::mem_function p_function
        = &IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol;
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy> mc_integrator(p_function, this,
                                                                                 2);
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};

    result = mc_integrator.integrate(min_array, max_array, (void *)&mc_int_pars,
                                     m_sim_params.m_mc_points);
    return result;
}

IInterferenceFunctionStrategy::IntegrationParamsAlpha
IInterferenceFunctionStrategy::getIntegrationParams(const cvector_t &k_i, Bin1D alpha_f_bin,
                                                    Bin1D phi_f_bin) const
{
    kvector_t real_ki(k_i.x().real(), k_i.y().real(), k_i.z().real());

    IntegrationParamsAlpha result;
    result.k_i = k_i;
    result.wavelength = Units::PI2 / real_ki.mag();
    result.alpha_bin = alpha_f_bin;
    result.phi_bin = phi_f_bin;
    return result;
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(double *fractions, size_t dim,
                                                                void *params) const
{
    (void)dim;
    double par0 = fractions[0];
    double par1 = fractions[1];

    IntegrationParamsAlpha *pars = static_cast<IntegrationParamsAlpha *>(params);
    cvector_t k_i = pars->k_i;
    cvector_t k_f;
    double alpha = pars->alpha_bin.m_lower
                   + par0 * (pars->alpha_bin.m_upper - pars->alpha_bin.m_lower);
    double phi = pars->phi_bin.m_lower + par1 * (pars->phi_bin.m_upper - pars->phi_bin.m_lower);
    k_f.setLambdaAlphaPhi(pars->wavelength, alpha, phi);
    boost::scoped_ptr<const ILayerRTCoefficients> out_coeff(
        mP_specular_info->getOutCoefficients(alpha, phi));
    k_f.setZ(out_coeff->getScalarKz());

    Bin1DCVector k_f_bin(k_f, k_f);
    Bin1D alpha_bin(alpha, alpha);
    calculateFormFactorList(k_i, k_f_bin, alpha_bin);
    return std::cos(alpha) * evaluateForList(k_i, k_f_bin, m_ff);
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol(double *fractions, size_t dim,
                                                                    void *params) const
{
    (void)dim;
    double par0 = fractions[0];
    double par1 = fractions[1];

    IntegrationParamsAlpha *pars = static_cast<IntegrationParamsAlpha *>(params);
    cvector_t k_i = pars->k_i;
    cvector_t k_f;
    double alpha = pars->alpha_bin.m_lower
                   + par0 * (pars->alpha_bin.m_upper - pars->alpha_bin.m_lower);
    double phi = pars->phi_bin.m_lower + par1 * (pars->phi_bin.m_upper - pars->phi_bin.m_lower);
    k_f.setLambdaAlphaPhi(pars->wavelength, alpha, phi);
    boost::scoped_ptr<const ILayerRTCoefficients> out_coeff(
        mP_specular_info->getOutCoefficients(alpha, phi));
    k_f.setZ(out_coeff->getScalarKz());

    Bin1DCVector k_f_bin(k_f, k_f);
    Bin1D alpha_bin(alpha, alpha);
    Bin1D phi_bin(phi, phi);
    calculateFormFactorLists(k_i, k_f_bin, alpha_bin, phi_bin);

    double result = 0.0;
    result
        = evaluateForMatrixList(k_i, pars->beam_density, k_f_bin, pars->detector_operator, m_ff_pol);
    return std::cos(alpha) * result;
}
