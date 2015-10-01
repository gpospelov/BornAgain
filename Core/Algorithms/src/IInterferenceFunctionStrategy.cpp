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

double IInterferenceFunctionStrategy::evaluate(const SimulationElement& sim_element) const
{
    double lambda = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(lambda, alpha_i, phi_i);
    Bin1D alpha_f_bin(sim_element.getAlphaMin(), sim_element.getAlphaMax());
    Bin1D phi_f_bin(sim_element.getPhiMin(), sim_element.getPhiMax());
    Bin1DCVector k_f_bin(lambda, alpha_f_bin, phi_f_bin);
    if (m_sim_params.m_mc_integration && m_sim_params.m_mc_points > 1
        && (alpha_f_bin.getBinSize() != 0.0 || phi_f_bin.getBinSize() != 0.0)) {
        return MCIntegratedEvaluate(sim_element);
    }
    calculateFormFactorList(sim_element);
    return evaluateForList(sim_element, m_ff);
}

double IInterferenceFunctionStrategy::evaluatePol(const SimulationElement& sim_element) const
{
    if (m_sim_params.m_mc_integration && m_sim_params.m_mc_points > 0) {
        return MCIntegratedEvaluatePol(sim_element);
    }
    double result;
    calculateFormFactorLists(sim_element);
    result = evaluateForMatrixList(sim_element, m_ff_pol);
    return result;
}

void IInterferenceFunctionStrategy::calculateFormFactorList(
        const SimulationElement& sim_element) const
{
    clearFormFactorLists();

    double wavelength = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(wavelength, alpha_i, phi_i);
    Bin1D alpha_f_bin(sim_element.getAlphaMin(), sim_element.getAlphaMax());
    Bin1D phi_f_bin(sim_element.getPhiMin(), sim_element.getPhiMax());
    Bin1DCVector k_f_bin(wavelength, alpha_f_bin, phi_f_bin);

    boost::scoped_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(alpha_i, 0.0, wavelength));
    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(alpha_f_bin.getMidPoint(), 0.0, wavelength));
    SafePointerVector<FormFactorInfo>::const_iterator it = m_ff_infos.begin();
    while (it != m_ff_infos.end()) {
        (*it)->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        complex_t ff_mat = (*it)->mp_ff->evaluate(k_i, k_f_bin);
        m_ff.push_back(ff_mat);
        ++it;
    }
}

void IInterferenceFunctionStrategy::calculateFormFactorLists(
        const SimulationElement &sim_element) const
{
    clearFormFactorLists();

    double wavelength = sim_element.getWavelength();
    double alpha_i = sim_element.getAlphaI();
    double phi_i = sim_element.getPhiI();
    cvector_t k_i;
    k_i.setLambdaAlphaPhi(wavelength, alpha_i, phi_i);
    Bin1D alpha_f_bin(sim_element.getAlphaMin(), sim_element.getAlphaMax());
    Bin1D phi_f_bin(sim_element.getPhiMin(), sim_element.getPhiMax());
    Bin1DCVector k_f_bin(wavelength, alpha_f_bin, phi_f_bin);

    boost::scoped_ptr<const ILayerRTCoefficients> P_in_coeffs(
        mP_specular_info->getInCoefficients(alpha_i, phi_i, wavelength));
    boost::scoped_ptr<const ILayerRTCoefficients> P_out_coeffs(
        mP_specular_info->getOutCoefficients(alpha_f_bin.getMidPoint(), phi_f_bin.getMidPoint(),
                                             wavelength));
    SafePointerVector<FormFactorInfo>::const_iterator it = m_ff_infos.begin();
    while (it != m_ff_infos.end()) {
        (*it)->mp_ff->setSpecularInfo(P_in_coeffs.get(), P_out_coeffs.get());
        Eigen::Matrix2cd ff_mat = (*it)->mp_ff->evaluatePol(k_i, k_f_bin);
        m_ff_pol.push_back(ff_mat);
        ++it;
    }
}

void IInterferenceFunctionStrategy::clearFormFactorLists() const
{
    m_ff.clear();
    m_ff_pol.clear();
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluate(const SimulationElement& sim_element) const
{
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy>::mem_function p_function
        = &IInterferenceFunctionStrategy::evaluate_for_fixed_angles;
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy> mc_integrator(p_function, this,
                                                                                 2);
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mc_integrator.integrate(min_array, max_array, (void *)&sim_element,
                                            m_sim_params.m_mc_points);
}

double IInterferenceFunctionStrategy::MCIntegratedEvaluatePol(
        const SimulationElement& sim_element) const
{
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy>::mem_function p_function
        = &IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol;
    MemberFunctionMCMiserIntegrator<IInterferenceFunctionStrategy>
            mc_integrator(p_function, this, 2);
    double min_array[] = {0.0, 0.0};
    double max_array[] = {1.0, 1.0};
    return mc_integrator.integrate(min_array, max_array, (void *)&sim_element,
                                            m_sim_params.m_mc_points);
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles(double *fractions, size_t dim,
                                                                void *params) const
{
    (void)dim;
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement *pars = static_cast<SimulationElement *>(params);
    double alpha = pars->getAlphaMin() + par0 * (pars->getAlphaMax() - pars->getAlphaMin());
    double phi = pars->getPhiMin() + par1 * (pars->getPhiMax() - pars->getPhiMin());

    SimulationElement sim_element(pars->getWavelength(), pars->getAlphaI(), pars->getPhiI(),
                                  alpha, alpha, phi, phi);
    sim_element.setPolarization(pars->getPolarization());
    sim_element.setAnalyzerOperator(pars->getAnalyzerOperator());
    calculateFormFactorList(sim_element);
    return pars->getIntegrationFactor(par0, par1) * evaluateForList(sim_element, m_ff);
}

double IInterferenceFunctionStrategy::evaluate_for_fixed_angles_pol(double *fractions, size_t dim,
                                                                    void *params) const
{
    (void)dim;
    double par0 = fractions[0];
    double par1 = fractions[1];

    SimulationElement *pars = static_cast<SimulationElement *>(params);
    double alpha = pars->getAlphaMin() + par0 * (pars->getAlphaMax() - pars->getAlphaMin());
    double phi = pars->getPhiMin() + par1 * (pars->getPhiMax() - pars->getPhiMin());

    SimulationElement sim_element(pars->getWavelength(), pars->getAlphaI(), pars->getPhiI(),
                                  alpha, alpha, phi, phi);
    sim_element.setPolarization(pars->getPolarization());
    sim_element.setAnalyzerOperator(pars->getAnalyzerOperator());
    calculateFormFactorLists(sim_element);

    double result = evaluateForMatrixList(sim_element, m_ff_pol);
    return pars->getIntegrationFactor(par0, par1) * result;
}
