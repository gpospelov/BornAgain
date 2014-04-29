// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IInterferenceFunctionStrategy.cpp
//! @brief     Implements default behaviour of IInterferenceFunctionStrategy
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IInterferenceFunctionStrategy.h"
#include "MemberFunctionIntegrator.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(
        SimulationParameters sim_params)
: m_sim_params(sim_params)
, m_integrate_bin(false)
{
}

void IInterferenceFunctionStrategy::init(
        const SafePointerVector<FormFactorInfo>& form_factor_infos,
        const SafePointerVector<IInterferenceFunction>& ifs)
{
    m_ff_infos = form_factor_infos;
    m_ifs = ifs;
}

double IInterferenceFunctionStrategy::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    if (m_integrate_bin) {
        return integratedEvaluate(k_i, k_f_bin, alpha_f_bin);
    }
    calculateFormFactorList(k_i, k_f_bin, alpha_f_bin);
    return evaluateForList(k_i, k_f_bin, m_ff00);
}

Eigen::Matrix2d IInterferenceFunctionStrategy::evaluatePol(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin,
        Bin1D phi_f_bin) const
{
    Eigen::Matrix2d result;
    calculateFormFactorLists(k_i, k_f_bin, alpha_f_bin, phi_f_bin);
    result(0,0) = evaluateForList(k_i, k_f_bin, m_ff00);
    result(0,1) = evaluateForList(k_i, k_f_bin, m_ff01);
    result(1,0) = evaluateForList(k_i, k_f_bin, m_ff10);
    result(1,1) = evaluateForList(k_i, k_f_bin, m_ff11);
    return result;
}

complex_t IInterferenceFunctionStrategy::meanFormFactor(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin,
        bool use_position) const
{
    complex_t result;
    for (SafePointerVector<FormFactorInfo>::const_iterator
             it=m_ff_infos.begin();
         it != m_ff_infos.end(); ++it) {
        complex_t ff_value =
            (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_f_bin);
        if (use_position) {
            cvector_t q = getQ(k_i, k_f_bin);
            complex_t phase = q.x()*(*it)->m_pos_x + q.y()*(*it)->m_pos_y;
            ff_value *= std::exp(complex_t(0.0, 1.0)*phase);
        }
        result += ff_value;
    }
    return result;
}

double IInterferenceFunctionStrategy::meanSquaredFormFactor(
    const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    double result=0.0;
    for (SafePointerVector<FormFactorInfo>::const_iterator it =
            m_ff_infos.begin(); it != m_ff_infos.end(); ++it) {
        complex_t ff_value = (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_f_bin);
        result += std::norm(ff_value);
    }
    return result;
}

void IInterferenceFunctionStrategy::calculateFormFactorList(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    clearFormFactorLists();
    SafePointerVector<FormFactorInfo>::const_iterator it =
            m_ff_infos.begin();
    while(it != m_ff_infos.end()) {
        complex_t ff_mat = (*it)->mp_ff->evaluate(k_i, k_f_bin, alpha_f_bin);
        m_ff00.push_back(ff_mat);
        ++it;
    }
}

void IInterferenceFunctionStrategy::calculateFormFactorLists(
        const cvector_t& k_i, const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin,
        Bin1D phi_f_bin) const
{
    clearFormFactorLists();
    SafePointerVector<FormFactorInfo>::const_iterator it =
            m_ff_infos.begin();
    while(it != m_ff_infos.end()) {
        Eigen::Matrix2cd ff_mat = (*it)->mp_ff->evaluatePol(k_i, k_f_bin,
                alpha_f_bin, phi_f_bin);
        m_ff00.push_back((complex_t)ff_mat(0,0));
        m_ff01.push_back((complex_t)ff_mat(0,1));
        m_ff10.push_back((complex_t)ff_mat(1,0));
        m_ff11.push_back((complex_t)ff_mat(1,1));
        ++it;
    }
}

void IInterferenceFunctionStrategy::clearFormFactorLists() const
{
    m_ff00.clear();
    m_ff01.clear();
    m_ff10.clear();
    m_ff11.clear();
}

double IInterferenceFunctionStrategy::integratedEvaluate(const cvector_t &k_i,
    const Bin1DCVector &k_f_bin, Bin1D alpha_f_bin) const
{
    cvector_t k_f_00 = k_f_bin.m_q_lower;
    cvector_t k_f_11 = k_f_bin.m_q_upper;
    complex_t xy_length0 = k_f_00.magxy();
    complex_t xy_length1 = k_f_11.magxy();
    cvector_t k_f_01(k_f_11.x()*xy_length0/xy_length1,
                     k_f_11.y()*xy_length0/xy_length1,
                     k_f_00.z());
    cvector_t k_f_10(k_f_00.x()*xy_length1/xy_length0,
                     k_f_00.y()*xy_length1/xy_length0,
                     k_f_11.z());
    IntegrationParamsAlpha alpha_pars;
    alpha_pars.k_i = k_i;
    alpha_pars.k_f00 = k_f_00;
    alpha_pars.k_f01 = k_f_01;
    alpha_pars.k_f10 = k_f_10;
    alpha_pars.k_f11 = k_f_11;
    alpha_pars.alpha_bin = alpha_f_bin;
    MemberFunctionIntegrator<IInterferenceFunctionStrategy>::mem_function
            p_alpha_function = &IInterferenceFunctionStrategy::integratePhi;
    MemberFunctionIntegrator<IInterferenceFunctionStrategy>
            alpha_integrator(p_alpha_function, this);
    double result = alpha_integrator.integrate(0.0, 1.0, (void*)&alpha_pars);
    return result;
}

double IInterferenceFunctionStrategy::integratePhi(
        double zeta, void *params) const
{
    IntegrationParamsAlpha* pars = static_cast<IntegrationParamsAlpha*>(params);
    IntegrationParamsPhi phi_pars;
    phi_pars.k_i = pars->k_i;
    phi_pars.k_f0 = pars->k_f00 + zeta*(pars->k_f10 - pars->k_f00);
    phi_pars.k_f1 = pars->k_f01 + zeta*(pars->k_f11 - pars->k_f01);
    phi_pars.alpha_bin = pars->alpha_bin;
    MemberFunctionIntegrator<IInterferenceFunctionStrategy>::mem_function
        p_phi_function = &IInterferenceFunctionStrategy::evaluate_with_fixed_kf;
    MemberFunctionIntegrator<IInterferenceFunctionStrategy>
            phi_integrator(p_phi_function, this);
    double result = phi_integrator.integrate(0.0, 1.0, (void*)&phi_pars);
    return result;
}

double IInterferenceFunctionStrategy::evaluate_with_fixed_kf(
        double xi, void* params) const
{
    IntegrationParamsPhi* pars = static_cast<IntegrationParamsPhi*>(params);
    cvector_t k_i = pars->k_i;
    cvector_t k_f = pars->k_f0 + xi*(pars->k_f1 - pars->k_f0);
    Bin1DCVector k_f_bin(k_f, k_f);
    calculateFormFactorList(k_i, k_f_bin, pars->alpha_bin);
    return evaluateForList(k_i, k_f_bin, m_ff00);
}



