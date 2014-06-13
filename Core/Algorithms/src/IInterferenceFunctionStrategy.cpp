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
#include "MemberFunctionMCIntegrator.h"

IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(
        SimulationParameters sim_params)
: m_sim_params(sim_params)
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
    if (m_sim_params.m_mc_integration && m_sim_params.m_mc_points > 0) {
        return MCIntegratedEvaluate(k_i, k_f_bin, alpha_f_bin);
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

double IInterferenceFunctionStrategy::MCIntegratedEvaluate(const cvector_t &k_i,
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
    IntegrationParamsAlpha mc_int_pars;
    mc_int_pars.k_i = k_i;
    mc_int_pars.k_f00 = k_f_00;
    mc_int_pars.k_f01 = k_f_01;
    mc_int_pars.k_f10 = k_f_10;
    mc_int_pars.k_f11 = k_f_11;
    mc_int_pars.alpha_bin = alpha_f_bin;
    MemberFunctionMCIntegrator<IInterferenceFunctionStrategy>::mem_function
        p_function = &IInterferenceFunctionStrategy::evaluate_for_fixed_kf;
    MemberFunctionMCIntegrator<IInterferenceFunctionStrategy>
        mc_integrator(p_function, this, 2);
    double min_array[] = { 0.0, 0.0 };
    double max_array[] = { 1.0, 1.0 };
    double result = mc_integrator.integrate(min_array, max_array,
                         (void*)&mc_int_pars, m_sim_params.m_mc_points);
    return result;
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_kf(double *angles,
        size_t dim, void *params) const
{
    (void)dim;
    double par0 = angles[0];
    double par1 = angles[1];

    IntegrationParamsAlpha* pars = static_cast<IntegrationParamsAlpha*>(params);
    cvector_t k_i = pars->k_i;
    cvector_t k_f0 = pars->k_f00 + par0*(pars->k_f10 - pars->k_f00);
    cvector_t k_f1 = pars->k_f01 + par0*(pars->k_f11 - pars->k_f01);
    cvector_t k_f = k_f0 + par1*(k_f1 - k_f0);

    Bin1DCVector k_f_bin(k_f, k_f);
    calculateFormFactorList(k_i, k_f_bin, pars->alpha_bin);
    return evaluateForList(k_i, k_f_bin, m_ff00);
}
